#include "context.h"
#include <cassert>
#include <cmath>
#include <x86intrin.h>

int BitMapMatrix::bitmap_col_size() {
  return int(std::ceil(static_cast<double>(num_cols_) / 64.0));
}

// NOLINTNEXTLINE
int BitMapMatrix::first_bit_of_row(int row_id) {
  assert(row_id < num_rows_);
  for (int i = bitmap_[row_id].size() - 1; i >= 0; i--) {
    if (bitmap_[row_id][i] == 0) {
      continue;
    }
    return (i << 6) + (63 - _lzcnt_u64(bitmap_[row_id][i]));
  }
  return -1;
}

std::map<int, int> BitMapMatrix::first_bit_index() {
  std::map<int, int> res;
  for (int i = 0; i < num_rows_; i++) {
    int first_bit_pos = first_bit_of_row(i);
    res[first_bit_pos] = i;
    // printf("line %d, first bit: %d\n", i, first_bit_pos);
  }
  return res;
}