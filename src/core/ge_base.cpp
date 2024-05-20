#include "context.h"
#include <cassert>

#define ER_MATRIX ge_ctx->er_.bitmap_matrix_
#define ES_MATRIX ge_ctx->es_.bitmap_matrix_

/**
 * @brief GF(2) 消元算法
 * @param ge_ctx 消元上下文，包括消元行、消元子的信息
 * @param num_thread 消元线程数，在基本算法里面没有使用
 * @param num_lock 互斥锁数量，在基本算法里面没有使用
 */
void ge_base(Context *ge_ctx, [[maybe_unused]] int num_thread = 0 /*unused*/,
             [[maybe_unused]] int num_lock = 0 /*unused*/) {
  // 依次对每一行进行消元
  for (int i = 0; i < ER_MATRIX.num_rows_; i++) {
    int first_bit = -1;
    // first_bit_of_row 获得当前消元行非 0 首项的位置
    while ((first_bit = ER_MATRIX.first_bit_of_row(i)) != -1) {
      auto iter = ge_ctx->index_[first_bit];
      if (iter == nullptr) { // 不存在对应消元子，当前消元行升级为消元子
        ge_ctx->index_[first_bit] = ER_MATRIX.bitmap_[i].get();
        break;
      }
      // 存在消元行，进行消元
      assert(iter != nullptr);
      for (int j = 0; j < ER_MATRIX.bitmap_col_size_; j++) {
        ER_MATRIX.bitmap_[i][j] = ER_MATRIX.bitmap_[i][j] ^ iter[j];
      }
    }
  }
}
