#include "context.h"
#include "type.h"

#define ER_MATRIX ge_ctx->er_.bitmap_matrix_
#define ES_MATRIX ge_ctx->es_.bitmap_matrix_

void ge_avx512(Context *ge_ctx, [[maybe_unused]] int num_thread = 0 /*unused*/,
               [[maybe_unused]] int num_lock = 0 /*unused*/) {
  for (int i = 0; i < ER_MATRIX.num_rows_; i++) {
    int first_bit = -1;
    while ((first_bit = ER_MATRIX.first_bit_of_row(i)) != -1) {
      auto iter = ge_ctx->index_[first_bit];
      if (iter == nullptr) { // upgrade as Elimination Substitution
        ge_ctx->index_[first_bit] = ER_MATRIX.bitmap_[i].get();
        break;
      }
      int j = 0;
      for (; j + AVX_512_CHUNK_SIZE < ER_MATRIX.bitmap_col_size_;
           j += AVX_512_CHUNK_SIZE) {
        __m512i er = _mm512_loadu_si512((void *)&ER_MATRIX.bitmap_[i][j]);
        __m512i es = _mm512_loadu_si512((void *)&iter[j]);
        __m512i vx = _mm512_xor_si512(er, es);
        _mm512_storeu_si512((void *)&ER_MATRIX.bitmap_[i][j], vx);
      }
      for (; j < ER_MATRIX.bitmap_col_size_; j++) {
        ER_MATRIX.bitmap_[i][j] = ER_MATRIX.bitmap_[i][j] ^ iter[j];
      }
    }
  }
}

void ge_avx256(Context *ge_ctx, [[maybe_unused]] int num_thread = 0 /*unused*/,
               [[maybe_unused]] int num_lock = 0 /*unused*/) {
  for (int i = 0; i < ER_MATRIX.num_rows_; i++) {
    int first_bit = -1;
    while ((first_bit = ER_MATRIX.first_bit_of_row(i)) != -1) {
      auto iter = ge_ctx->index_[first_bit];
      if (iter == nullptr) { // upgrade as Elimination Substitution
        ge_ctx->index_[first_bit] = ER_MATRIX.bitmap_[i].get();
        break;
      }
      int j = 0;
      for (; j + AVX_256_CHUNK_SIZE < ER_MATRIX.bitmap_col_size_;
           j += AVX_256_CHUNK_SIZE) {
        __m256i er = _mm256_loadu_si256((__m256i *)&ER_MATRIX.bitmap_[i][j]);
        __m256i es = _mm256_loadu_si256((__m256i *)&iter[j]);
        __m256i vx = _mm256_xor_si256(er, es);
        _mm256_storeu_si256((__m256i *)&ER_MATRIX.bitmap_[i][j], vx);
      }
      for (; j < ER_MATRIX.bitmap_col_size_; j++) {
        ER_MATRIX.bitmap_[i][j] = ER_MATRIX.bitmap_[i][j] ^ iter[j];
      }
    }
  }
}

void ge_sse128(Context *ge_ctx, [[maybe_unused]] int num_thread = 0 /*unused*/,
               [[maybe_unused]] int num_lock = 0 /*unused*/) {
  for (int i = 0; i < ER_MATRIX.num_rows_; i++) {
    int first_bit = -1;
    while ((first_bit = ER_MATRIX.first_bit_of_row(i)) != -1) {
      auto iter = ge_ctx->index_[first_bit];
      if (iter == nullptr) { // upgrade as Elimination Substitution
        ge_ctx->index_[first_bit] = ER_MATRIX.bitmap_[i].get();
        break;
      }
      int j = 0;
      for (; j + SSE_128_CHUNK_SIZE < ER_MATRIX.bitmap_col_size_;
           j += SSE_128_CHUNK_SIZE) {
        __m128i er = _mm_loadu_si128((__m128i *)&ER_MATRIX.bitmap_[i][j]);
        __m128i es = _mm_loadu_si128((__m128i *)&iter[j]);
        __m128i vx = _mm_xor_si128(er, es);
        _mm_storeu_si128((__m128i *)&ER_MATRIX.bitmap_[i][j], vx);
      }
      for (; j < ER_MATRIX.bitmap_col_size_; j++) {
        ER_MATRIX.bitmap_[i][j] = ER_MATRIX.bitmap_[i][j] ^ iter[j];
      }
    }
  }
}