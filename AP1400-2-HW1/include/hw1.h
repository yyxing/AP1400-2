#ifndef AP_HW1_H
#define AP_HW1_H
#include <vector>
using std::size_t;
using Matrix = std::vector<std::vector<double>>;
namespace algebra {
//创建一个n x m 所有元素都为零的矩阵
Matrix zeros(size_t n, size_t m);
//创建一个n x m 所有元素都等于 1 的矩阵。
Matrix ones(size_t n, size_t m);
// 以便它创建一个n x m矩阵，其中所有元素都是介于[min,max]之间的随机数。
Matrix random(size_t n, size_t m, double min, double max);
// 输出矩阵
void show(const Matrix& matrix);
// 使其matrix与常量标量相乘c
Matrix multiply(const Matrix& matrix, double c);
// 使其乘以matrix1into matrix2。（这不是逐元素乘法）
Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);
// 它向的每个元素添加常量matrix
Matrix sum(const Matrix& matrix, double c);
// 将 2 个矩阵相加。
Matrix sum(const Matrix& matrix1, const Matrix& matrix2);
// 生成输入的转置矩阵matrix
Matrix transpose(const Matrix& matrix);
// 将矩阵转换成
Matrix minor(const Matrix& matrix, size_t n, size_t m);
// 计算输入matrix的行列式
double determinant(const Matrix& matrix);
// 生成matrix的反函数
Matrix inverse(const Matrix& matrix);
// 将多个矩阵以指定轴拼接
Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis=0);
// 交换两行
Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2);
// 将一行乘以一个常数
Matrix ero_multiply(const Matrix& matrix, size_t r, double c);
// 将一行乘以一个常数并将其添加到另一行。
Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2);
// 上三角矩阵
Matrix upper_triangular(const Matrix& matrix);
};
#endif //AP_HW1_H
