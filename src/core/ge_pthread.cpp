#include "context.h"
#include "type.h"
#include <cmath>
#include <mutex>
#include <pthread.h>
#include <random>
#include <shared_mutex>
#include <iostream>

#define ER_MATRIX ge_ctx->er_.bitmap_matrix_
#define ES_MATRIX ge_ctx->es_.bitmap_matrix_
std::mutex mutex; // for debug


// back-off
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(50, 150);

typedef struct {
    Context *ge_ctx;
    std::shared_mutex* mutexes;
    int num_thread;
    int thread_id;
    int num_lock;
    bool use_simd;
} ThreadArgs;

void *ge_pthread_core(void *args) {
  auto thread_args = static_cast<ThreadArgs*>(args);
  auto ge_ctx = thread_args->ge_ctx;
  auto num_thread = thread_args->num_thread;
  auto thread_id = thread_args->thread_id;
  auto num_lock = thread_args->num_lock;
  auto use_simd = thread_args->use_simd;
  auto rw_lock = thread_args->mutexes;
  int row_per_thread = std::ceil(static_cast<double>(ER_MATRIX.num_rows_) / static_cast<double>(num_thread));
  int range_start = thread_id * row_per_thread;
  int range_end = (thread_id + 1) * row_per_thread;
  if (range_start >= ER_MATRIX.num_rows_) return nullptr;
  if (range_end >= ER_MATRIX.num_rows_) range_end = ER_MATRIX.num_rows_;

  // mutex.lock();
  // std::cout << "thread " << thread_id << " range " << range_start << " - " << range_end << std::endl;
  // mutex.unlock();
 
  for (int i = range_start; i < range_end; i++) {
    int first_bit = -1;
    while ((first_bit = ER_MATRIX.first_bit_of_row(i)) != -1) {
      rw_lock[first_bit % num_lock].lock_shared();
      auto iter = ge_ctx->index_[first_bit];
      if (iter == nullptr) { // upgrade as Elimination Substitution
        rw_lock[first_bit % num_lock].unlock_shared();
        rw_lock[first_bit % num_lock].lock();
        if (ge_ctx->index_[first_bit] != nullptr) {
          rw_lock[first_bit % num_lock].unlock();
          continue;
        }
        ge_ctx->index_[first_bit] = ER_MATRIX.bitmap_[i].get();
        rw_lock[first_bit % num_lock].unlock();
        break;
      }
      rw_lock[first_bit % num_lock].unlock_shared();

      // avx512
      if (use_simd) {
        int j = 0;
        for (; j + AVX_512_CHUNK_SIZE < ER_MATRIX.bitmap_col_size_;
            j += AVX_512_CHUNK_SIZE) {
          __m512i er = _mm512_loadu_si512((void *)&ER_MATRIX.bitmap_[i][j]);
          __m512i es =
              _mm512_loadu_si512((void *)&iter[j]);
          __m512i vx = _mm512_xor_si512(er, es);
          _mm512_storeu_si512((void *)&ER_MATRIX.bitmap_[i][j], vx);
        }
        for (; j < ER_MATRIX.bitmap_col_size_; j++) {
          ER_MATRIX.bitmap_[i][j] =
              ER_MATRIX.bitmap_[i][j] ^ iter[j];
        }
      } else {
        for (int j = 0; j < ER_MATRIX.bitmap_col_size_; j++) {
          ER_MATRIX.bitmap_[i][j] =
              ER_MATRIX.bitmap_[i][j] ^ iter[j];
        }
      }
    }
  }
  return nullptr;
}

void ge_pthread(Context *ge_ctx, int num_thread = 32, int num_lock = 32, bool use_simd = true) {
  pthread_t *threads = new pthread_t[num_thread];
  ThreadArgs *args = new ThreadArgs[num_thread];
  std::shared_mutex *mutexes = new std::shared_mutex[num_lock];
  for (int i = 0; i < num_thread; i++) {
    args[i].ge_ctx = ge_ctx;
    args[i].thread_id = i;
    args[i].num_thread = num_thread;
    args[i].mutexes = mutexes;
    args[i].num_lock = num_lock;
    args[i].use_simd = use_simd;
    pthread_create(&threads[i], nullptr, ge_pthread_core, (void*)&args[i]);
  }
  for (int i = 0; i < num_thread; ++i) {
    pthread_join(threads[i], nullptr);
  }
  delete [] threads;
  delete [] args;
  delete [] mutexes;
}