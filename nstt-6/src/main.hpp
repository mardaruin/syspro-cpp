#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

class SquareMatrix {
private:
  int size;
  double* data;

  void copyHelper(const SquareMatrix& other) {
    size = other.getSize();
    data = new double[size * size];
    for (int i = 0; i < size * size; i++) {
      data[i] = other.data[i];
    }
  }

  void setZeros() {
    for (int i = 0; i < size * size; i++) {
      data[i] = 0.0;
    }
  }

  void free() {
    delete[] data;
    data = nullptr;
    size = 0;
  }

public:
  explicit SquareMatrix(int n):
      size(n), data(new double[n * n]) {
    if (size <= 0) {
      throw std::invalid_argument("Matrix size must be > 0.");
    }
    setZeros();
  }

  explicit SquareMatrix(const std::vector<double>& vect):
      size(vect.size()), data(new double[size * size]) {
    if (size <= 0) {
      throw std::invalid_argument("Matrix size msut be > 0.");
    }
    setZeros();
    for (int i = 0; i < size; i++) {
      (*this)[i][i] = vect[i];
    }
  }

  SquareMatrix(const SquareMatrix& other) {
    copyHelper(other);
  }

  SquareMatrix& operator=(const SquareMatrix& other) {
    if (this != &other) {
      free();
      copyHelper(other);
    }
    return *this;
  }

  SquareMatrix(SquareMatrix&& other):
      size(other.getSize()), data(other.data) {
    other.size = 0;
    other.data = nullptr;
  }

  SquareMatrix& operator=(SquareMatrix&& other) {
    if (this != &other) {
      free();
      size       = other.getSize();
      data       = other.data;
      other.data = nullptr;
      other.size = 0;
    }
    return *this;
  }

  explicit operator double() const {
    double sum = 0;
    for (int i = 0; i < size * size; i++) {
      sum += data[i];
    }
    return sum;
  }

  int getSize() const {
    return size;
  }

  ~SquareMatrix() {
    free();
  }

  class Row {
  private:
    int size;
    double* rowStart;

  public:
    Row(int n, double* ptr):
        size(n),
        rowStart(ptr) {}

    double& operator[](int i) {
      if (i < 0 || i >= size) {
        throw std::out_of_range("Index must be less than matrix size.");
      }
      return rowStart[i];
    }

    const double& operator[](int i) const {
      if (i < 0 || i >= size) {
        throw std::out_of_range("Index must be less than matrix size.");
      }
      return rowStart[i];
    }
  };

  Row operator[](int i) {
    if (i < 0 || i >= size) {
      throw std::out_of_range("Index must be less than matrix size.");
    }
    return Row(size, data + i * size);
  }

  const Row operator[](int i) const {
    if (i < 0 || i >= size) {
      throw std::out_of_range("Index must be less than matrix size.");
    }
    return Row(size, data + i * size);
  }

  SquareMatrix operator+(const SquareMatrix& other) const {
    if (size != other.getSize()) {
      throw std::invalid_argument("Matrix sizes in addition must be equal.");
    }
    SquareMatrix result(size);
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        result[i][j] = (*this)[i][j] + other[i][j];
      }
    }
    return result;
  }

  SquareMatrix& operator+=(const SquareMatrix& other) {
    if (size != other.getSize()) {
      throw std::invalid_argument("Matrix sizes in addition must be equal.");
    }
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        (*this)[i][j] += other[i][j];
      }
    }
    return *this;
  }

  SquareMatrix operator*(const SquareMatrix& other) const {
    if (size != other.getSize()) {
      throw std::invalid_argument("Square Matrix sizes in multiplication must be equal.");
    }
    SquareMatrix result(size);
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        double sum = 0;
        for (int k = 0; k < size; k++) {
          sum += (*this)[i][k] * other[k][j];
        }
        result[i][j] = sum;
      }
    }
    return result;
  }

  SquareMatrix& operator*=(const SquareMatrix& other) {
    if (size != other.getSize()) {
      throw std::invalid_argument("Square Matrix sizes in multiplication must be equal.");
    }
    *this = *this * other;
    return *this;
  }

  SquareMatrix operator*(double scalar) const {
    SquareMatrix result(size);
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        result[i][j] = (*this)[i][j] * scalar;
      }
    }
    return result;
  }

  SquareMatrix& operator*=(double scalar) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        (*this)[i][j] *= scalar;
      }
    }
    return *this;
  }

  bool operator==(const SquareMatrix& other) const {
    if (size != other.getSize()) {
      return false;
    }
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if ((*this)[i][j] != other[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const SquareMatrix& other) const {
    return !(*this == other);
  }
};
