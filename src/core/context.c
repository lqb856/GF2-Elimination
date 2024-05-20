#include "context.h"
#include <cassert>
#include <cmath>
#include <x86intrin.h>

int BitMapMatrix::bitmap_col_size() const { return bitmap_col_size_; }

// NOLINTNEXTLINE
int BitMapMatrix::first_bit_of_row(int row_id) {
  assert(row_id < num_rows_);
  for (int i = bitmap_col_size_ - 1; i >= 0; i--) {
    if (bitmap_[row_id][i] == 0) {
      continue;
    }
    return (i << 6) + (63 - _lzcnt_u64(bitmap_[row_id][i]));
  }
  return -1;
}

void BitMapMatrix::first_bit_index(u_int64_t **index, int size) {
  assert(size > num_rows_);
  // for (int i = 0; i < size; i++) {
  //   index[i] = nullptr;
  // }
  for (int i = 0; i < num_rows_; i++) {
    int first_bit_pos = first_bit_of_row(i);
    index[first_bit_pos] = bitmap_[i].get();
    // printf("line %d, first bit: %d\n", i, first_bit_pos);
  }
}