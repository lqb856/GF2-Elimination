#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "context.h"

// 加载稀疏矩阵数据并转换为 CSR 格式
CSRMatrix load_matrix_csr(const std::string &filename, int num_cols) {
  CSRMatrix csr_mat;
  csr_mat.num_rows_ = 0;
  csr_mat.num_cols_ = num_cols;

  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Cannot open file " << filename << std::endl;
    return csr_mat;
  }

  // 逐行读取文件
  std::string line;
  while (std::getline(file, line)) {
    csr_mat.num_rows_++;

    std::vector<int> indices;
    std::istringstream iss(line);
    int index;
    while (iss >> index) {
      indices.push_back(index);
    }

    // 更新行指针、列索引和数值数组
    csr_mat.row_ptr_.push_back(csr_mat.values_.size());
    for (int i = 0; i < num_cols; ++i) {
      if (std::find(indices.begin(), indices.end(), i + 1) != indices.end()) {
        csr_mat.col_index_.push_back(i);
        csr_mat.values_.push_back(1);
      }
    }
  }

  // 最后一个行指针是 values 的大小
  csr_mat.row_ptr_.push_back(csr_mat.values_.size());

  return csr_mat;
}

// 加载数据文件，转换为 bitmap 表示
BitMapMatrix load_bitmap_matrix(const std::string &filename, int num_cols) {
  BitMapMatrix bitmap;
  bitmap.num_rows_ = 0;
  bitmap.num_cols_ = num_cols;

  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Cannot open file " << filename << std::endl;
    return bitmap;
  }

  int num_uint64_per_row = std::ceil(static_cast<double>(num_cols) / 64.0);

  std::string line;
  while (std::getline(file, line)) {
    bitmap.num_rows_++;
    std::vector<uint64_t> row_bitmap(num_uint64_per_row, 0);
    std::istringstream iss(line);
    int index;
    while (iss >> index) {
      int block_idx = index / 64;
      int bit_idx = index % 64;
      row_bitmap[block_idx] |= (1ULL << bit_idx);
    }

    bitmap.bitmap_.push_back(row_bitmap);
  }

  return bitmap;
}

void save_bitmap_matrix(const std::string &filename,
                        const BitMapMatrix &bitmap_matrix) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Cannot open file " << filename << std::endl;
    return;
  }

  // 将位图数据写入文件，从高位开始写入
  for (const auto &row_bitmap : bitmap_matrix.bitmap_) {
    for (int j = bitmap_matrix.num_cols_ - 1; j >= 0; --j) {
      int block_idx = j / 64; // 确定索引在哪个 uint64_t 块中
      int bit_idx = j % 64;   // 确定索引在 uint64_t 中的位置

      // 如果位图数组中该位为1，则写入该列的索引
      if (row_bitmap[block_idx] & (1ULL << bit_idx)) {
        file << j << " "; // 将索引写入文件（从1开始）
      }
    }
    file << std::endl;
  }
}

void print_set_positions(const std::vector<uint64_t> &row_bitmap,
                         size_t num_cols) {
  for (size_t i = 0; i < row_bitmap.size(); ++i) {
    for (size_t j = 0; j < 64 && (i * 64 + j) < num_cols; ++j) {
      if ((row_bitmap[i] >> j) & 1) {
        std::cout << (i * 64 + j) << " ";
      }
    }
  }
  std::cout << std::endl;
}

bool bitmap_matrix_cmp(const BitMapMatrix &matrix1,
                       const BitMapMatrix &matrix2) {
  // 检查行数和列数是否相同
  if (matrix1.num_rows_ != matrix2.num_rows_ ||
      matrix1.num_cols_ != matrix2.num_cols_) {
    return false;
  }

  // 逐行比较位图数组
  for (int i = 0; i < matrix1.num_rows_; ++i) {
    const auto &row_bitmap1 = matrix1.bitmap_[i];
    const auto &row_bitmap2 = matrix2.bitmap_[i];

    // 如果行的位图数组大小不同，则两个矩阵不相同
    if (row_bitmap1.size() != row_bitmap2.size()) {
      return false;
    }

    for (size_t j = 0; j < row_bitmap1.size(); j++) {
      if (matrix1.bitmap_[i][j] != matrix2.bitmap_[i][j]) {
        std::cout << "Difference in row " << i << ", col[" << (j << 6) << "~ "
                  << ((j + 1) << 6) << "]: " << std::endl;
        std::cout << "Matrix 1: " << matrix1.bitmap_[i][j];
        std::cout << "Matrix 2: " << matrix2.bitmap_[i][j];
        std::cout << std::endl;
        return false;
      }
    }
  }
  // 两个矩阵的内容完全相同
  return true;
}
