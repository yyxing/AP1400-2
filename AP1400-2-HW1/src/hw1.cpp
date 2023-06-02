#include "hw1.h"
#include <vector>
#include <stdexcept>
#include <random>
#include <iostream>
#include <iomanip>
static inline void check_empty(std::initializer_list<Matrix> ilm) {
  for (auto it = ilm.begin(); it != ilm.end(); ++it) {
    if (it->empty()) {
      throw std::logic_error("matrix must be non-empty");
    }
  }
}
static inline void check_size(size_t n, size_t m) {
  if (n == 0 || m == 0) {
    throw std::invalid_argument("size must be non-zero");
  }
}

namespace algebra {
Matrix zeros(size_t n, size_t m) {
  check_size(n, m);
  return Matrix{n, std::vector<double>(m, 0)};
}
//创建一个n x m 所有元素都等于 1 的矩阵。
Matrix ones(size_t n, size_t m) {
  check_size(n, m);
  return Matrix{n, std::vector<double>(m, 1)};
}
// 以便它创建一个n x m矩阵，其中所有元素都是介于[min,max]之间的随机数。
Matrix random(size_t n, size_t m, double min, double max) {
  check_size(n, m);
  if (min > max) {
    throw std::logic_error("min value must less than max");
  }
  Matrix matrix = zeros(n, m);
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_real_distribution<double> u(min, max);
  for (auto &v : matrix) {
    for (auto &e : v) {
      e = u(engine);
    }
  }
  return matrix;
}
// 输出矩阵
void show(const Matrix &matrix) {
  check_empty({matrix});
  std::cout << std::showpoint << std::setprecision(3);
  for (auto &v : matrix) {
    for (auto &e : v) {
      std::cout << e << "\t";
    }
    std::cout << std::endl;
  }
  std::cout << std::noshowpoint << std::setprecision(6);
}
// 使其matrix与常量标量相乘c
Matrix multiply(const Matrix &matrix, double c) {
  check_empty({matrix});
  Matrix mat(matrix);
  for (auto &v : mat) {
    for (auto &e : v) {
      e *= c;
    }
  }
  return mat;
}
// 使其乘以matrix1into matrix2。（这不是逐元素乘法）
Matrix multiply(const Matrix &matrix1, const Matrix &matrix2) {
  if (matrix1.empty()) return matrix2;
  if (matrix2.empty()) return matrix1;
  std::size_t n1 = matrix1.size(), m1 = matrix1[0].size(),
      n2 = matrix2.size(), m2 = matrix2[0].size();
  if (m1 != n2) throw std::logic_error("dimensions doesn't match");
  Matrix matrix = zeros(n1, m2);
  for (int i = 0; i < n1; ++i) {
    for (int j = 0; j < m2; ++j) {
      for (int k = 0; k < m1; ++k) {
        matrix[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
  return matrix;
}

// 它向的每个元素添加常量matrix
Matrix sum(const Matrix &matrix, double c) {
  if (matrix.empty()) return matrix;
  Matrix mat(matrix);
  for (auto &v : mat) {
    for (auto &e : v) {
      e += c;
    }
  }
  return mat;
}
// 将 2 个矩阵相加。
Matrix sum(const Matrix &matrix1, const Matrix &matrix2) {
  if (matrix1.empty() && matrix2.empty()) return matrix1;
  check_empty({matrix1, matrix2});
  std::size_t n1 = matrix1.size(), m1 = matrix1[0].size(),
      n2 = matrix2.size(), m2 = matrix2[0].size();
  if (m1 != m2 || n1 != n2) throw std::logic_error("dimensions doesn't match");
  Matrix matrix = zeros(n1, m1);
  for (int i = 0; i < n1; ++i) {
    for (int j = 0; j < m2; ++j) {
      matrix[i][j] += matrix1[i][j] + matrix2[i][j];
    }
  }
  return matrix;
}

}

