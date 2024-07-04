#pragma once

#include <algorithm>
#include <stdexcept>
#include <type_traits>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 public:
  Matrix() : elements_(N, std::vector<T>(M)){};

  Matrix(std::vector<std::vector<T>>& other) : elements_(other){};

  Matrix(T elem) : elements_(N, std::vector<T>(M, elem)){};

  Matrix(const Matrix& other) = default;

  Matrix& operator=(const Matrix& other) = default;

  Matrix& operator+=(const Matrix& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        elements_[i][j] += other(i, j);
      }
    }
    return *this;
  }

  Matrix operator+(const Matrix& other) const {
    Matrix result(*this);
    result += other;
    return result;
  }

  Matrix& operator-=(const Matrix& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        elements_[i][j] -= other(i, j);
      }
    }
    return *this;
  }

  Matrix operator-(const Matrix& other) const {
    Matrix result(*this);
    result -= other;
    return result;
  }

  Matrix& operator*=(const T& number) {
    for (auto& row : elements_) {
      for (auto& element : row) {
        element *= number;
      }
    }
    return *this;
  }

  Matrix operator*(const T& number) const {
    Matrix result(*this);
    result *= number;
    return result;
  }

  template <size_t K>
  Matrix<N, K, T> operator*(const Matrix<M, K, T>& other) const {
    Matrix<N, K, T> product;
    for (size_t i = 0; i < N; ++i) {
      for (size_t l_idx = 0; l_idx < K; ++l_idx) {
        for (size_t j = 0; j < M; ++j) {
          product(i, l_idx) += elements_[i][j] * other(j, l_idx);
        }
      }
    }
    return product;
  }

  Matrix<M, N, T> Transposed() const {
    Matrix<M, N, T> transposed_matrix;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        transposed_matrix(j, i) = elements_[i][j];
      }
    }
    return transposed_matrix;
  }

  T Trace() const { return FindTrace(*this); }

  T& operator()(size_t i_idx, size_t j_idx) {
    if (i_idx >= N || j_idx >= M) {
      throw std::out_of_range("Index out of range");
    }
    return elements_[i_idx][j_idx];
  }

  const T& operator()(size_t i_idx, size_t j_idx) const {
    if (i_idx >= N || j_idx >= M) {
      throw std::out_of_range("Index out of range");
    }
    return elements_[i_idx][j_idx];
  }

  bool operator==(Matrix& other) const noexcept {
    return elements_ == other.elements_;
  }

 private:
  std::vector<std::vector<T>> elements_;
};

template <size_t N, typename T = int64_t>
T FindTrace(const Matrix<N, N, T>& matrix) {
  T trace = T();
  for (size_t i = 0; i < N; ++i) {
    trace += matrix(i, i);
  }
  return trace;
}
