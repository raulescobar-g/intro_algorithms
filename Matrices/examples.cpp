// examples.cpp
#include <iostream>
#include <iomanip>
#include <cassert>
#include "./matrix.h"

using std::cout, std::endl;

// length of n in characters
std::size_t get_width(int n) {
  if (n < 0) {
    return 1 + get_width(-n);
  }
  if (n < 10) {
    return 1;
  }
  return 1 + get_width(n/10);
}

// pretty print a Matrix
std::ostream& operator << (std::ostream& os, Matrix const& matrix) {
  std::size_t rows = matrix.rows;
  std::size_t cols = matrix.cols;

  // handle the empty matrix
  if (rows == 0 || cols == 0) {
    os << std::endl << "  []" << std::endl;
    return os;
  }

  // compute column widths
  std::size_t* width = new std::size_t[cols]{0};
  for (std::size_t col = 0; col < cols; ++col) {
    for (std::size_t row = 0; row < rows; ++row) {
      std::size_t digits = get_width(matrix[row][col]);
      if (digits > width[col]) {
        width[col] = digits;
      }
    }
  }

  // pretty print with right-aligned columns
  os << std::endl;
  for (std::size_t row = 0; row < rows; ++row) {
    os << "  |";
    for (std::size_t col = 0; col < cols; ++col) {
      os << " " << std::setw(width[col]) << matrix[row][col];
    }
    os << " |" << std::endl;
  }

  delete[] width;

  return os;
}

void example1() {
  cout << "A = [1 2 ; 3 4]" << endl;
  Matrix A = {{1, 2}, {3, 4}};
  cout << A << endl;
  assert(A.rows == 2);
  assert(A.cols == 2);

  cout << "B = [5 6 ; 7 8 ; 9 10]" << endl;
  Matrix B = {{5, 6}, {7, 8}, {9, 10}};
  cout << B << endl;
  assert(B.rows == 3);
  assert(B.cols == 2);

  cout << "C = vertcat(A, B)" << endl;
  Matrix& C = vertcat(A, B);
  cout << C << endl;
  assert(A.rows == 5);
  assert(A.cols == 2);
  assert(B.rows == 3);
  assert(B.cols == 2);
  assert(C.rows == 5);
  assert(C.cols == 2);

  cout << "A" << endl;
  cout << A << endl;

  cout << "B" << endl;
  cout << B << endl;
}

void example2() {
  cout << "A = [1 2 3 4]" << endl;
  Matrix A = {{1, 2, 3, 4}};
  cout << A << endl;
  assert(A.rows == 1);
  assert(A.cols == 4);

  cout << "vertcat(A, A)" << endl;
  cout << vertcat(A, A) << endl;
  assert(A.rows == 2);
  assert(A.cols == 4);

  cout << "vertcat(A, A)" << endl;
  cout << vertcat(A, A) << endl;
  assert(A.rows == 4);
  assert(A.cols == 4);
}

void example3() {
  cout << "A = [1]" << endl;
  Matrix A = {{1}};
  cout << A << endl;
  assert(A.rows == 1);
  assert(A.cols == 1);

  cout << "vertcat(vertcat(A, A), vertcat(A, A))" << endl;
  cout << vertcat(vertcat(A, A), vertcat(A, A)) << endl;
  assert(A.rows == 8);
  assert(A.cols == 1);

  A[0][0] = 999;
  cout << "A(1,1) = 999" << endl;
  cout << A << endl;
  assert(A[0][0] == 999);
  assert(A[1][0] == 1);
  
  A[4][0] = 1234;
  cout << "A(5,1) = 1234" << endl;
  cout << A << endl;
  assert(A[0][0] == 999);
  assert(A[3][0] == 1);
  assert(A[4][0] == 1234);
  assert(A[5][0] == 1);
}

void example4() {
    cout << "A = [1 2 3 ; 4 5 6]" << endl;
    Matrix A = {{1, 2, 3}, {4, 5, 6}};
    cout << A << endl;

    cout << "B = [1 2 ; 3 4 ; 5 6]" << endl;
    Matrix B = {{1, 2}, {3, 4}, {5, 6}};
    cout << B << endl;

    try {
        cout << "vertcat(A, B)";
        vertcat(A, B);
        assert(false);
    } catch (const std::exception& err) {
        cout << "Error: " << err.what() << endl;
        assert(A.rows == 2);
    }

    cout << endl<< "A" << endl;
    cout << A << endl;
}

int main() {
  example1();
  example2();
  example3();
  example4();
}