#pragma once
#include <cstddef>
#include <map>
#include <memory>
#include <sys/types.h>
#include <vector>

enum class StorageType { CSR = 0, BITMAP = 1 };
const size_t MAX_ROW = 60000;
const size_t MAX_COL = 90000 / 64;

// 定义稀疏矩阵的结构体
struct CSRMatrix {
  int num_rows_;               // 矩阵行数
  int num_cols_;               // 矩阵列数
  std::vector<int> row_ptr_;   // 行指针数组
  std::vector<int> col_index_; // 列索引数组
  std::vector<int> values_;    // 数值数组
};

struct BitMapMatrix {
  int bitmap_col_size() const;
  int first_bit_of_row(int row_id);
  void first_bit_index(u_int64_t** index, int size);

    // 深度拷贝函数
    BitMapMatrix clone() const {
        BitMapMatrix cloned_bitmap_matrix;
        std::vector<std::unique_ptr<u_int64_t[]>> bitmap_cloned;
        for (const auto &row : bitmap_) {
          auto row_bitmap = std::make_unique<u_int64_t[]>(bitmap_col_size_);
          std::fill_n(row_bitmap.get(), bitmap_col_size_, 0); 
          std::copy(row.get(), row.get() + bitmap_col_size_, row_bitmap.get());
          bitmap_cloned.push_back(std::move(row_bitmap));
        }
        cloned_bitmap_matrix.bitmap_ = std::move(bitmap_cloned); // 拷贝向量
        cloned_bitmap_matrix.num_rows_ = num_rows_;
        cloned_bitmap_matrix.num_cols_ = num_cols_;
        cloned_bitmap_matrix.bitmap_col_size_ = bitmap_col_size_;
        return cloned_bitmap_matrix;
    }

  std::vector<std::unique_ptr<u_int64_t[]>> bitmap_;
  int num_rows_, num_cols_;
  int bitmap_col_size_;
};

struct Matrix {
  BitMapMatrix bitmap_matrix_;

    // 深度拷贝函数
    Matrix clone() const {
        Matrix cloned_matrix;
        cloned_matrix.bitmap_matrix_ = bitmap_matrix_.clone(); // 深度拷贝 BitMapMatrix
        return cloned_matrix;
    }
};

struct Context {
  Matrix es_;
  Matrix er_;
  u_int64_t** index_;

    // 深度拷贝函数
    Context clone() const {
        Context cloned_context;
        cloned_context.es_ = es_.clone(); // 深度拷贝 Matrix
        cloned_context.er_ = er_.clone(); // 深度拷贝 Matrix
        cloned_context.index_ = index_; // 拷贝 std::map
        return cloned_context;
    }
};