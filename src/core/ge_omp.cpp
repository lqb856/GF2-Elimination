#include "context.h"
#include "type.h"
#include <omp.h>
#include <shared_mutex>

#define ER_MATRIX ge_ctx->er_.bitmap_matrix_
#define ES_MATRIX ge_ctx->es_.bitmap_matrix_

void ge_omp(Context *ge_ctx, int num_thread = 32, int num_lock = 32, bool use_simd = true) {
  omp_set_num_threads(num_thread);
  std::shared_mutex *rw_lock = new std::shared_mutex[num_lock];
#pragma omp parallel for schedule(dynamic)
  for (int i = 0; i < ER_MATRIX.num_rows_; i++) {
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

  delete [] rw_lock;
}