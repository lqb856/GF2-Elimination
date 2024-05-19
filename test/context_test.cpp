#include "context.c"
#include "context.h"
#include "data_loader.cpp"
#include "ge_base.cpp"
#include "ge_simd.cpp"
#include "ge_omp.cpp"
#include "ge_pthread.cpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <chrono>
#include <string>
#include <strings.h>
#include <sys/types.h>
#include <vector>

std::vector<std::vector<std::string>> data_sets = {
    std::vector<std::string>{
        "/home/lqb/c/GF2-Elimination/dataset/测试样例1 "
        "矩阵列数130，非零消元子22，被消元行8/消元子.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例1 "
        "矩阵列数130，非零消元子22，被消元行8/被消元行.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例1 "
        "矩阵列数130，非零消元子22，被消元行8/消元结果.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例1 "
        "矩阵列数130，非零消元子22，被消元行8/消元结果1.txt"},
    std::vector<std::string>{
        "/home/lqb/c/GF2-Elimination/dataset/测试样例2 "
        "矩阵列数254，非零消元子106，被消元行53/消元子.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例2 "
        "矩阵列数254，非零消元子106，被消元行53/被消元行.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例2 "
        "矩阵列数254，非零消元子106，被消元行53/消元结果.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例2 "
        "矩阵列数254，非零消元子106，被消元行53/消元结果1.txt"},
    std::vector<std::string>{
        "/home/lqb/c/GF2-Elimination/dataset/测试样例3 "
        "矩阵列数562，非零消元子170，被消元行53/消元子.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例3 "
        "矩阵列数562，非零消元子170，被消元行53/被消元行.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例3 "
        "矩阵列数562，非零消元子170，被消元行53/消元结果.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例3 "
        "矩阵列数562，非零消元子170，被消元行53/消元结果1.txt"},
    std::vector<std::string>{
        "/home/lqb/c/GF2-Elimination/dataset/测试样例4 "
        "矩阵列数1011，非零消元子539，被消元行263/消元子.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例4 "
        "矩阵列数1011，非零消元子539，被消元行263/被消元行.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例4 "
        "矩阵列数1011，非零消元子539，被消元行263/消元结果.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例4 "
        "矩阵列数1011，非零消元子539，被消元行263/消元结果1.txt"},
    std::vector<std::string>{
        "/home/lqb/c/GF2-Elimination/dataset/测试样例5 "
        "矩阵列数2362，非零消元子1226，被消元行453/消元子.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例5 "
        "矩阵列数2362，非零消元子1226，被消元行453/被消元行.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例5 "
        "矩阵列数2362，非零消元子1226，被消元行453/消元结果.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例5 "
        "矩阵列数2362，非零消元子1226，被消元行453/消元结果1.txt"},
    std::vector<std::string>{
        "/home/lqb/c/GF2-Elimination/dataset/测试样例6 "
        "矩阵列数3799，非零消元子2759，被消元行1953/消元子.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例6 "
        "矩阵列数3799，非零消元子2759，被消元行1953/被消元行.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例6 "
        "矩阵列数3799，非零消元子2759，被消元行1953/消元结果.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例6 "
        "矩阵列数3799，非零消元子2759，被消元行1953/消元结果1.txt"},
    std::vector<std::string>{
        "/home/lqb/c/GF2-Elimination/dataset/测试样例7 "
        "矩阵列数8399，非零消元子6375，被消元行4535/消元子.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例7 "
        "矩阵列数8399，非零消元子6375，被消元行4535/被消元行.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例7 "
        "矩阵列数8399，非零消元子6375，被消元行4535/消元结果.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例7 "
        "矩阵列数8399，非零消元子6375，被消元行4535/消元结果1.txt"},
    std::vector<std::string>{
        "/home/lqb/c/GF2-Elimination/dataset/测试样例8 "
        "矩阵列数23045，非零消元子18748，被消元行14325/消元子.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例8 "
        "矩阵列数23045，非零消元子18748，被消元行14325/被消元行.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例8 "
        "矩阵列数23045，非零消元子18748，被消元行14325/消元结果.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例8 "
        "矩阵列数23045，非零消元子18748，被消元行14325/消元结果1.txt"},
    std::vector<std::string>{
        "/home/lqb/c/GF2-Elimination/dataset/测试样例9 "
        "矩阵列数37960，非零消元子29304，被消元行14921/消元子.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例9 "
        "矩阵列数37960，非零消元子29304，被消元行14921/被消元行.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例9 "
        "矩阵列数37960，非零消元子29304，被消元行14921/消元结果.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例9 "
        "矩阵列数37960，非零消元子29304，被消元行14921/消元结果1.txt"},
    std::vector<std::string>{
        "/home/lqb/c/GF2-Elimination/dataset/测试样例10 "
        "矩阵列数43577，非零消元子39477，被消元行54274/消元子.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例10 "
        "矩阵列数43577，非零消元子39477，被消元行54274/被消元行.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例10 "
        "矩阵列数43577，非零消元子39477，被消元行54274/消元结果.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例10 "
        "矩阵列数43577，非零消元子39477，被消元行54274/消元结果1.txt"},
    std::vector<std::string>{
        "/home/lqb/c/GF2-Elimination/dataset/测试样例11 "
        "矩阵列数85401，非零消元子5724，被消元行756/消元子.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例11 "
        "矩阵列数85401，非零消元子5724，被消元行756/被消元行.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例11 "
        "矩阵列数85401，非零消元子5724，被消元行756/消元结果.txt",
        "/home/lqb/c/GF2-Elimination/dataset/测试样例11 "
        "矩阵列数85401，非零消元子5724，被消元行756/消元结果1.txt"},
};

std::vector<int> data_set_cols = {130,  254,   562,   1011,  2362, 3799,
                                  8399, 23045, 37960, 43577, 85401};

// 測試函數示例
TEST(TestContext, TestFirstBit) {
  // 斷言示例
  int data_set = 8;
  int thread_num = 16; // for ge_pthread
  int lock_num = 128;
  int num_cols = data_set_cols[data_set];
  std::string es_file = data_sets[data_set][0];
  std::string er_file = data_sets[data_set][1];
  std::string ans_file = data_sets[data_set][2];
  std::string res_file = data_sets[data_set][3];

  Context ctx;
  ctx.er_.bitmap_matrix_ = load_bitmap_matrix(er_file, num_cols);
  ctx.es_.bitmap_matrix_ = load_bitmap_matrix(es_file, num_cols);
  BitMapMatrix ans = load_bitmap_matrix(ans_file, num_cols);
  int index_size = ctx.er_.bitmap_matrix_.num_cols_ + ctx.es_.bitmap_matrix_.num_cols_ + 1;
  ASSERT_EQ(ctx.er_.bitmap_matrix_.num_cols_, num_cols);
  ASSERT_EQ(ctx.es_.bitmap_matrix_.num_cols_, num_cols);
  std::cout << "dataset: " << data_set + 1 << std::endl;
  std::cout << "col size: " << num_cols << std::endl;
  std::cout << "er row size: " << ctx.er_.bitmap_matrix_.num_rows_ << std::endl;
  std::cout << "es row size: " << ctx.es_.bitmap_matrix_.num_rows_ << std::endl;
  std::cout << "index size: " << index_size << std::endl;
  std::cout << "********************************************************" << std::endl;
  
  Context ctx1 = ctx.clone();
  ctx1.index_ = new u_int64_t*[index_size]{};
  ctx1.es_.bitmap_matrix_.first_bit_index(ctx1.index_, index_size);
  auto start = std::chrono::high_resolution_clock::now();
  ge_base(&ctx1);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "ge_base time: " << duration.count() << " milliseconds" << std::endl;
  // save_bitmap_matrix(res_file, ctx1.es_.bitmap_matrix_);
  bool cmp = bitmap_matrix_cmp(ans, ctx1.er_.bitmap_matrix_);
  ASSERT_TRUE(cmp);
  delete [] ctx1.index_;

  Context ctx2 = ctx.clone();
  ctx2.index_ = new u_int64_t*[index_size]{};
  ctx2.es_.bitmap_matrix_.first_bit_index(ctx2.index_, index_size);
  start = std::chrono::high_resolution_clock::now();
  ge_avx256(&ctx2);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "ge_avx256 time: " << duration.count() << " milliseconds" << std::endl;
  // save_bitmap_matrix(res_file, ctx.er_.bitmap_matrix_);
  cmp = bitmap_matrix_cmp(ans, ctx2.er_.bitmap_matrix_);
  ASSERT_TRUE(cmp);
  delete [] ctx2.index_;

  Context ctx3 = ctx.clone();
  ctx3.index_ = new u_int64_t*[index_size]{};
  ctx3.es_.bitmap_matrix_.first_bit_index(ctx3.index_, index_size);
  start = std::chrono::high_resolution_clock::now();
  ge_sse128(&ctx3);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "ge_sse128 time: " << duration.count() << " milliseconds" << std::endl;
  // save_bitmap_matrix(res_file, ctx.er_.bitmap_matrix_);
  cmp = bitmap_matrix_cmp(ans, ctx3.er_.bitmap_matrix_);
  ASSERT_TRUE(cmp);
  delete [] ctx3.index_;

  Context ctx4 = ctx.clone();
  ctx4.index_ = new u_int64_t*[index_size]{};
  ctx4.es_.bitmap_matrix_.first_bit_index(ctx4.index_, index_size);
  start = std::chrono::high_resolution_clock::now();
  ge_avx512(&ctx4);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "ge_avx512 time: " << duration.count() << " milliseconds" << std::endl;
  // save_bitmap_matrix(res_file, ctx.er_.bitmap_matrix_);
  cmp = bitmap_matrix_cmp(ans, ctx4.er_.bitmap_matrix_);
  ASSERT_TRUE(cmp);
  delete [] ctx4.index_;

  Context ctx5 = ctx.clone();
  ctx5.index_ = new u_int64_t*[index_size]{};
  ctx5.es_.bitmap_matrix_.first_bit_index(ctx5.index_, index_size);
  start = std::chrono::high_resolution_clock::now();
  ge_pthread(&ctx5, thread_num, lock_num, false);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "ge_pthread time: " << duration.count() << " milliseconds" << std::endl;
  delete [] ctx5.index_;

  Context ctx6 = ctx.clone();
  ctx6.index_ = new u_int64_t*[index_size]{};
  ctx6.es_.bitmap_matrix_.first_bit_index(ctx6.index_, index_size);
  start = std::chrono::high_resolution_clock::now();
  ge_pthread(&ctx6, thread_num, lock_num, false);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "ge_omp time: " << duration.count() << " milliseconds" << std::endl;
  delete [] ctx6.index_;

  Context ctx7 = ctx.clone();
  ctx7.index_ = new u_int64_t*[index_size]{};
  ctx7.es_.bitmap_matrix_.first_bit_index(ctx7.index_, index_size);
  start = std::chrono::high_resolution_clock::now();
  ge_pthread(&ctx7, thread_num, lock_num);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "ge_pthread_avx time: " << duration.count() << " milliseconds" << std::endl;
  delete [] ctx7.index_;

  Context ctx8 = ctx.clone();
  ctx8.index_ = new u_int64_t*[index_size]{};
  ctx8.es_.bitmap_matrix_.first_bit_index(ctx8.index_, index_size);
  start = std::chrono::high_resolution_clock::now();
  ge_pthread(&ctx8, thread_num, lock_num);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "ge_omp_avx time: " << duration.count() << " milliseconds" << std::endl;
  delete [] ctx8.index_;
}