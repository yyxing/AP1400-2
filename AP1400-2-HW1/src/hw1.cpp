#include "hw1.h"
#include <vector>
#include <stdexcept>
#include <random>
#include <iostream>
#include <iomanip>
static inline void check_empty(std::initializer_list<Matrix> ilm) {
  for (const auto &it : ilm) {
    if (it.empty()) {
      throw std::logic_error("matrix must be non-empty");
    }
  }
}
static inline void check_size(size_t n, size_t m) {
  if (n == 0 || m == 0) {
    throw std::invalid_argument("size must be non-zero");
  }
}

static inline void check_square(const Matrix &mat) {
  if (mat.size() != mat[0].size()) {
    throw std::logic_error("matrix must be square");
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
Matrix transpose(const Matrix &matrix) {
  size_t n1, m1;
  n1 = matrix.size();
  if (n1 == 0) return matrix;
  m1 = matrix[0].size();
  Matrix mat = zeros(m1, n1);
  for (int i = 0; i < n1; ++i) {
    for (int j = 0; j < m1; ++j) {
      mat[j][i] = matrix[i][j];
    }
  }
  return mat;
}
// 将矩阵转换成
Matrix minor(const Matrix &matrix, size_t n, size_t m) {
  check_empty({matrix});
  size_t n1 = matrix.size(), m1 = matrix[0].size();
  Matrix mat = zeros(n1 - 1, m1 - 1);
  for (int i = 0; i < n1 - 1; ++i) {
    for (int j = 0; j < m1 - 1; ++j) {
      int ii = i < n ? i : i + 1;
      int jj = j < m ? j : j + 1;
      mat[i][j] = matrix[ii][jj];
    }
  }
  return mat;
}

double det2(const Matrix &matrix) {
  return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}
double det3(const Matrix &matrix) {
  return matrix[0][0] * matrix[1][1] * matrix[2][2] +
      matrix[0][1] * matrix[1][2] * matrix[2][0] +
      matrix[0][2] * matrix[1][0] * matrix[2][1] -
      matrix[0][2] * matrix[1][1] * matrix[2][0] -
      matrix[0][0] * matrix[1][2] * matrix[2][1] -
      matrix[0][1] * matrix[1][0] * matrix[2][2];
}

// 计算输入matrix的行列式
double determinant(const Matrix &matrix) {
  if (matrix.empty()) return 1;
  check_square(matrix);
  size_t n = matrix.size();
  if (n == 1) return matrix[0][0];
  if (n == 2) return det2(matrix);
  if (n == 3) return det3(matrix);
  double res = 0;
  for (int i = 0; i < n; ++i) {
    int sign = (i & 1) ? -1 : 1;
    Matrix minor = algebra::minor(matrix, 0, i);
    res += matrix[0][i] * sign * determinant(minor);
  }
  return res;
}
// 求伴随矩阵
Matrix adjoint(const Matrix &matrix) {
  int n1 = matrix.size();
  Matrix mat = zeros(n1, n1);
  for (int i = 0; i < n1; ++i) {
    for (int j = 0; j < n1; ++j) {
      int sign = ((i + j) & 1) ? -1 : 1;
      Matrix minor = algebra::minor(matrix, i, j);
      mat[i][j] = sign * determinant(minor);
    }
  }
  return transpose(mat);
}
// 生成matrix的反函数
Matrix inverse(const Matrix &matrix) {
  if (matrix.empty()) return matrix;
  check_square(matrix);
  double det = determinant(matrix);
  if (det == 0) {
    throw std::logic_error("singular matrices have no inverse");
  }
  double determinant = 1.0 / algebra::determinant(matrix);
  return multiply(adjoint(matrix), determinant);
}
// 将多个矩阵以指定轴拼接
Matrix concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis) {
  check_empty({matrix1, matrix2});
  int n1 = matrix1.size();
  int m1 = matrix1[0].size();
  int n2 = matrix2.size();
  int m2 = matrix2[0].size();
  if (axis == 0 && m1 != m2) throw std::logic_error("column number doesn't match while axis = 0");
  if (axis == 1 && n1 != n2) throw std::logic_error("row number doesn't match while axis = 1");
  if (axis == 0) {
    Matrix mat = zeros(n1 + n2, m1);
    for (int i = 0; i < mat.size(); ++i) {
      for (int j = 0; j < mat[0].size(); ++j) {
        mat[i][j] = (i < n1) ? matrix1[i][j] : matrix2[i - n1][j];
      }
    }
    return mat;
  } else {
    Matrix mat = zeros(n1, m1 + m2);
    for (int i = 0; i < mat.size(); ++i) {
      for (int j = 0; j < mat[0].size(); ++j) {
        mat[i][j] = (j < m1) ? matrix1[i][j] : matrix2[i][j - m1];
      }
    }
    return mat;
  }
}
}

