// matrix_vertcat.cpp
#include <iostream>
#include <stdexcept>
#include "./matrix.h"

using std::cout, std::endl;
using std::invalid_argument;
using std::size_t;

// vertically concatenate B to A (A on top of B)
// throws an invalid_argument exception on mismatched dimensions
// side effects:
//   A is reallocated to be bigger
Matrix& vertcat(Matrix& A, Matrix const& B) {
    //check that size matches
    if (A.cols != B.cols){
        throw invalid_argument("Error: dimension mismatch");
    }
    else {
        //if size matches change the size of A to be the size its suppose to be after vertical concatination
        A.rows += B.rows;
        //create a temporary matric C that holds teh values of A
        Matrix C = new Matrix*[A.rows];
        //copy over values of A into the temporary matrix
        for (size_t i =0; i < A.rows - B.rows;++i){
            for (size_t j = 0; j < A.cols; ++j){
                C[i][j] = A[i][j];
            }
        }
        //delete A
        for (size_t z = 0; z < A.rows-B.rows; ++z){
            delete[] A[z];
            A[z] = nullptr;
        }
        delete[] A[];
        A[] = nullptr

        //create new A with correct dimensions
        Matrix A = new Matrix*[A.rows];
        for (size_t q = 0; q < A.rows; ++q){
            A[q] = new Matrix[A.cols];
        }

        //populate A with values that were copied over into C
        for (size_t h = 0; h < A.rows-B.rows; ++h){
            for (size_t k = 0; k<A.cols;++k){
                A[h][k] = C[h][k];
            }
        }
        //populate A with values from B
        for (size_t h = 0; h < B.rows; ++h){
            for (size_t k = 0; k<B.cols;++k){
                A[h+A.rows][k] = B[h][k];
            }
        }
        //delete C and make it nullptr
        for (size_t z = 0; z < A.rows-B.rows; ++z){
            delete[] C[z];
            C[z] = nullptr;
        }
        delete[] A[];
        C[] = nullptr
    }
    //return A
    return A;
}

//destructor deletes data since its the only memory on heap
Matrix::~Matrix() {
  // TODO(student): destructor
  
    for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j){
            delete this[i][j];
            this[i][j] = nullptr;
        }
    }
    rows = 0;
    cols = 0; 
}