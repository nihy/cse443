// Copyright (C) 2016 nihy@miamiOH.edu

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "MatrixOps.h"

Matrix blockMultiply(const Matrix& matrix1, const Matrix& matrix2,
const size_t blockSize) {
  int dim1 = static_cast<int>(matrix1.size());
  int dim2 = static_cast<int>(matrix2[0].size());
  int n = static_cast<int>(matrix2.size());
  Matrix ret(dim1, std::vector<Val>(dim2));
  for (int blk_i = 0; blk_i < dim1; blk_i += blockSize) {
    for (int blk_j = 0; blk_j < dim2; blk_j += blockSize) {
      for (int blk_k = 0; blk_k < n; blk_k += blockSize) {
        for (int i = blk_i; 
          i < std::min(static_cast<int>(blk_i + blockSize), dim1); i++) {
          for (int j = blk_j; 
            j < std::min(static_cast<int>(blk_j + blockSize), dim2); j++) {
            for (int k = blk_k; 
              k < std::min(static_cast<int>(blk_k + blockSize), n); k++) {
              ret[i][j] += matrix1[i][k] * matrix2[k][j];
            }
          }
        }
      }
    }
  }
  return ret;
}

Matrix load(const std::string& filePath) {
  std::ifstream ifs(filePath);
  int dim1, dim2;
  ifs >> dim1 >> dim2;
  Matrix ret(dim1, std::vector<Val>(dim2));
  for (int i = 0; i < dim1; i++) {
    for (int j = 0; j < dim2; j++) {
      ifs >> ret[i][j];
    }
  }
  return ret;
}

void write(const std::string& filePath, const Matrix& mat) {
  std::ofstream ofs(filePath);
  ofs<< static_cast<int>(mat.size()) << static_cast<int>(mat[0].size()) << '\n';
  for (int row = 0; (row < static_cast<int>(mat.size())); row++) {
    for (int col = 0; (col < static_cast<int>(mat[0].size())); col++) {
      ofs << mat[row][col] << ' ';
    }
    ofs << std::endl;
  }
}
