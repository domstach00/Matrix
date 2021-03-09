#include <iostream>
#include "Matrix.h"



int main() {
    Matrix<int> matrix1(3,4, "mat1");
    matrix1.fillMatrixWith(2);
    matrix1.printMatrix();

    Matrix<int> matrix2(4,5, "mat2");
    matrix2.fillMatrixWith(3);
    matrix2.printMatrix();

    Matrix<int> mat;
    mat.operator=(matrix1.operator*(matrix2));
    mat.printMatrix();


    Matrix<int> matPath("intMatrix.txt");
    matPath.printMatrix();

    matPath.createVerticalVector(1);
    matPath.createHorizontalVector(1);

    cout << endl << "Produkt skalarny matrix1: " << matrix1.scalarProduct(matrix1);

    return 0;
}
