
#include "context.h"

#define ER_MATRIX ge_ctx->er_.bitmap_matrix_
#define ES_MATRIX ge_ctx->es_.bitmap_matrix_

void ge_base(Context *ge_ctx) {
  for (int i = 0; i < ER_MATRIX.num_rows_; i++) {
    int first_bit = -1;
    while ((first_bit = ER_MATRIX.first_bit_of_row(i)) != -1) {
      auto iter = ge_ctx->index_.find(first_bit);
      if (iter == ge_ctx->index_.end()) { // upgrade as Elimination Substitution
        ge_ctx->index_[first_bit] = ES_MATRIX.bitmap_.size();
        ES_MATRIX.bitmap_.emplace_back(ER_MATRIX.bitmap_[i]);
        break;
      }
      auto es = iter->second;
      for (int j = 0; j < ER_MATRIX.bitmap_col_size(); j++) {
        ER_MATRIX.bitmap_[i][j] =
            ER_MATRIX.bitmap_[i][j] ^ ES_MATRIX.bitmap_[es][j];
      }
    }
  }
}