#pragma once
#include <map>
#include <sys/types.h>
#include <vector>

enum class StorageType { CSR = 0, BITMAP = 1 };

// 定义稀疏矩阵的结构体
struct CSRMatrix {
  int num_rows_;               // 矩阵行数
  int num_cols_;               // 矩阵列数
  std::vector<int> row_ptr_;   // 行指针数组
  std::vector<int> col_index_; // 列索引数组
  std::vector<int> values_;    // 数值数组
};

struct BitMapMatrix {
  int bitmap_col_size();
  int first_bit_of_row(int row_id);
  std::map<int, int> first_bit_index();

  std::vector<std::vector<u_int64_t>> bitmap_;
  int num_rows_, num_cols_;
};

struct Matrix {
  BitMapMatrix bitmap_matrix_;
};

struct Context {
  Matrix es_;
  Matrix er_;
  std::map<int, int> index_;
};