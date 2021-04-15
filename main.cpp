#include <iostream>
#include "Matrix.h"


int matrixFromFileExample(){
    string path = "intMatrix.txt";

    Matrix<int> matPath(path);
    matPath.printMatrix();

    matPath.createVerticalVector(1);
    matPath.createHorizontalVector(1);

    return 0;
}


int main() {
    Matrix<int> matrix1(3,4, "matrix_1");
    matrix1.fillMatrixWith(2);
    matrix1.printMatrix();

    Matrix<int> matrix2(4,5, "matrix_2");
    matrix2.fillMatrixWith(3);
    matrix2.printMatrix();

    Matrix<int> mat;
    mat.operator=(matrix1.operator*(matrix2));
    mat.printMatrix();

    cout << endl << "Produkt skalarny matrix1: " << matrix1.scalarProduct(matrix1);

    matrixFromFileExample();

    return 0;
}
