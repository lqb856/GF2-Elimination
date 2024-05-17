#include "context.c"
#include "context.h"
#include "data_loader.cpp"
#include "ge_base.cpp"
#include <gtest/gtest.h>
#include <string>
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
  int num_cols = data_set_cols[data_set];
  std::string es_file = data_sets[data_set][0];
  std::string er_file = data_sets[data_set][1];
  std::string ans_file = data_sets[data_set][2];
  std::string res_file = data_sets[data_set][3];

  Context ctx;
  ctx.er_.bitmap_matrix_ = load_bitmap_matrix(er_file, num_cols);
  ctx.es_.bitmap_matrix_ = load_bitmap_matrix(es_file, num_cols);
  ASSERT_EQ(ctx.er_.bitmap_matrix_.num_cols_, num_cols);
  ASSERT_EQ(ctx.es_.bitmap_matrix_.num_cols_, num_cols);
  ctx.index_ = ctx.es_.bitmap_matrix_.first_bit_index();

  ge_base(&ctx);
  save_bitmap_matrix(res_file, ctx.er_.bitmap_matrix_);
  BitMapMatrix ans = load_bitmap_matrix(ans_file, num_cols);
  bool cmp = bitmap_matrix_cmp(ans, ctx.er_.bitmap_matrix_);
  ASSERT_TRUE(cmp);
}