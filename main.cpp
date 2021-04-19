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

int matrixExample(){
    Matrix<int> matrix1(3,4, "matrix_1");
    matrix1.fillMatrixWith(2);
    matrix1.printMatrix();

    Matrix<int> matrix2(4,5, "matrix_2");
    matrix2.fillMatrixWith(3);
    matrix2.printMatrix();

    Matrix<int> mat;
    mat.operator=(matrix1.operator*(matrix2));
    mat.printMatrix();

    cout << endl << "Scalar product matrix1: " << matrix1.scalarProduct(matrix1);

    return 0;
}

int main(int argc, char *argv[]) {

    if (argc == 1) {
        // Examples
        matrixExample();
        matrixFromFileExample();
    }
    else {
        // Create matrix with user arguments
        if (argc >= 3 && stoi(argv[1]) != 0 && stoi(argv[2])){
            Matrix<int> matrix(stoi(argv[2]),stoi(argv[1]), "matrix");

            if (argc >= 4)
                matrix.fillMatrixWith(stoi(argv[3]));
            else
                matrix.fillMatrixDef();

            matrix.printMatrix();
        }
    }

    return 0;
}
