#ifndef MATRIXPROJECT_MATRIX_H
#define MATRIXPROJECT_MATRIX_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
class Matrix{
private:
    T **matrix = NULL;
    string name;
    int sizeHorizontal;
    int sizeVertical;

public:
    Matrix();
    Matrix(int vertical, int horizontal, string nameOfMatrix = "");
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;
    Matrix(string path);

    ~Matrix();

    void fillMatrixWith(T val);
    void fillMatrixDef();
    void printMatrix();
    T scalarProduct(Matrix &other);

    void delMatrix();

    bool setAsIdentityMatrix();

    Matrix<T> createHorizontalVector(int verticalOffSet);
    Matrix<T> createVerticalVector(int horizontalOffSet);

    bool set(int vertical, int horizontal, T val);
    T get(int vertical, int horizontal);



    Matrix<T> transpose();


    Matrix<T> operator+(Matrix &other);
    Matrix<T> operator-(Matrix &other);
    Matrix<T> operator=(Matrix &other);
    Matrix<T> operator=(Matrix &&other) noexcept;
    template<typename E>
    Matrix<T> operator*(E arg);

    Matrix<T> operator*(Matrix &other);

    int countLines(string path);

    int countWidth(string path, int linesNr);
};


template<typename T>
Matrix<T>::Matrix() {
    sizeVertical = 0;
    sizeHorizontal = 0;
    name = "defaultConstructor";
}

template<typename T>
Matrix<T>::Matrix(int vertical, int horizontal, string nameOfMatrix) {
    if (vertical < 1)
        vertical = 1;
    if (horizontal < 1)
        horizontal = 1;

    name = nameOfMatrix;
    sizeVertical = vertical;
    sizeHorizontal = horizontal;

    matrix = new T*[sizeVertical];

    for (int i = 0; i < sizeVertical; ++i){
        matrix[i] = new T[sizeHorizontal];
        for (int j = 0; j < sizeHorizontal; ++j) {
            matrix[i][j] = T();
        }
    }

}

template<typename T>
Matrix<T>::Matrix(const Matrix &other) {
    if (other.matrix == NULL){
        cout << endl << "Empty matrix in: " << other.name;
        return;
    }

    name = other.name;
    sizeHorizontal = other.sizeHorizontal;
    sizeVertical = other.sizeVertical;

    matrix = new T*[sizeVertical];
    for (int i = 0; i < sizeVertical; i++)
        matrix[i] = new T[sizeHorizontal];

    for (int i = 0; i < sizeVertical; ++i)
        for (int j = 0; j < sizeHorizontal; ++j)
            matrix[i][j] =  other.matrix[i][j];


}

template<typename T>
Matrix<T>::Matrix(Matrix &&other) noexcept {
    sizeHorizontal = other.sizeHorizontal;
    sizeVertical = other.sizeVertical;

    matrix = other.matrix;
    other.matrix = NULL;

    other.sizeVertical = 0;
    other.sizeHorizontal = 0;
}

template<typename T>
Matrix<T>::Matrix(string path){
    ifstream file;

    file.open(path);

    sizeVertical = countLines(path);
    sizeHorizontal = countWidth(path, sizeVertical);
    name = path;


    matrix = new T*[sizeVertical];
    for (int i = 0; i < sizeVertical; i++)
        matrix[i] = new T[sizeHorizontal];


    for (int i = 0; i < sizeVertical; i++) {
        for (int j = 0; j < sizeHorizontal; j++)
            file >> matrix[i][j];
    }
}

template<typename T>
Matrix<T>::~Matrix() {
    if (matrix == NULL)
        return;

    for (int i = 0; i < sizeVertical; ++i)
        delete[] matrix[i];
    delete[] matrix;

    matrix = NULL;
}

template<typename T>
void Matrix<T>::fillMatrixWith(T val) {

    for (int i = 0; i < sizeVertical; ++i)
        for (int j = 0; j < sizeHorizontal; ++j)
            matrix[i][j] = val;

}

template<typename T>
void Matrix<T>::fillMatrixDef() {
    fillMatrixWith(static_cast<T>(T()));
}

template<typename T>
void Matrix<T>::printMatrix() {
    if (matrix == NULL){
        cout << endl << "There is no matrix to display";
        return;
    }

    cout << endl << endl << "\tDisplaying the matrix";

    if (name != "") // if the matrix has a name it will be displayed
        cout << " " << name;
    cout << ": " <<endl;

    for (int i = 0; i < sizeVertical; ++i) {
        for (int j = 0; j < sizeHorizontal; ++j)
            cout << matrix[i][j] << "\t";
        cout << endl;
    }

}

template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix &other) {
    if (sizeHorizontal != other.sizeHorizontal || sizeVertical != other.sizeVertical){
        cout << endl << "Matrices have different sizes";
        return NULL;
    }
    if (matrix == NULL)
        return other;
    if (other.matrix == NULL)
        return *this;

    Matrix<T> resMatrix(sizeVertical, sizeHorizontal, "op+ResoultMatrix");
    resMatrix.fillMatrixDef();

    for (int i = 0; i < sizeVertical; ++i) {
        for (int j = 0; j < sizeHorizontal; ++j)
            resMatrix.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
    }

    return resMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix &other) {
    if (sizeHorizontal != other.sizeHorizontal || sizeVertical != other.sizeVertical){
        cout << endl << "Matrices have different sizes";
        return Matrix();
    }
    if (matrix == NULL)
        return other;
    if (other.matrix == NULL)
        return *this;

    Matrix<T> resMatrix(sizeVertical, sizeHorizontal, "op-ResoultMatrix");
    resMatrix.fillMatrixDef();

    for (int i = 0; i < sizeVertical; ++i) {
        for (int j = 0; j < sizeHorizontal; ++j)
            resMatrix.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
    }

    return resMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::operator=( Matrix &&other) noexcept {
    if (this == &other)
        return *this;

    if (matrix != NULL)
        delMatrix();


    matrix = other.matrix;
    sizeHorizontal = other.sizeHorizontal;
    sizeVertical = other.sizeVertical;

    other.matrix = NULL;
    other.sizeHorizontal = 0;
    other.sizeVertical = 0;

    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator=( Matrix &other) {
    if (this == &other)
        return *this;

    delMatrix();

    sizeHorizontal = other.sizeHorizontal;
    sizeVertical = other.sizeVertical;

    matrix = other.matrix;

    return *this;
}

template<typename T>
template<typename E>
Matrix<T> Matrix<T>::operator*(E arg) {
    if (matrix == NULL){
        cout << endl << "The object has no matrix";
        return *this;
    }

    for (int i = 0; i < sizeVertical; ++i) {
        for (int j = 0; j < sizeHorizontal; ++j)
            matrix[i][j] = matrix[i][j] * arg;
    }


    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix &other) {
    if (matrix == NULL){
        cout << endl << "The object has no matrix";
        return other;
    }
    if (other.matrix == NULL){
        cout << endl << "The object has no matrix";
        return *this;
    }
    if (sizeHorizontal != other.sizeVertical){
        cout << endl << "Incorrect matrix dimensions";
        return Matrix();
    }

    int newHorizontal = other.sizeHorizontal;
    int newVertical = sizeVertical;

    T** newMatrix = new T*[newVertical];
    for (int i = 0; i < newVertical; ++i)
        newMatrix[i] = new T[newHorizontal];


    T sum;

    for (int i = 0; i < sizeVertical; ++i) {
        for (int j = 0; j < other.sizeHorizontal; ++j) {

            sum = 0;

            for (int k = 0; k < sizeHorizontal; ++k)
                sum += matrix[i][k] * other.matrix[k][j];

            newMatrix[i][j] = sum;

        }
    }


    Matrix<T> resoult(newVertical, newHorizontal, "op*ResoultMatrix");

    resoult.matrix = newMatrix;

    resoult.printMatrix();

    return resoult;
}

template<typename T>
Matrix<T> Matrix<T>::transpose() {
    if (matrix == NULL){
        cout << endl << "The object has no matrix";
        return *this;
    }

    int newVertical = sizeHorizontal;
    int newHorizontal = sizeVertical;

    T** newMatrix = new T*[newVertical];
    for (int i = 0; i < newVertical; ++i)
        newMatrix[i] = new T[newHorizontal];

    for (int i = 0; i < sizeVertical; ++i) {
        for (int j = 0; j < sizeHorizontal; ++j) {
            newMatrix[j][i] = matrix[i][j];
        }
    }

    delMatrix();

    sizeHorizontal = newHorizontal;
    sizeVertical = newVertical;

    matrix = newMatrix;

    return *this;
}

template<typename T>
void Matrix<T>::delMatrix() {
    if (matrix == NULL)
        return;

    for (int i = 0; i < sizeVertical; ++i)
        delete[] matrix[i];
    delete[] matrix;

    matrix = NULL;
}

template<typename T>
bool Matrix<T>::set(int vertical, int horizontal, T val) {
    if (matrix == NULL){
        cout << endl << "No matrix";
        return false;
    }

    if (vertical >= sizeVertical || horizontal >= sizeHorizontal || horizontal < 0 || vertical < 0) {
        cout << endl << "The indicated field is out of range";
        return false;
    }

    matrix[vertical][horizontal] = val;

    return true;
}

template<typename T>
T Matrix<T>::get(int vertical, int horizontal) {
    if (matrix == NULL){
        cout << endl << "No matrix";
        return T();
    }

    if (vertical >= sizeVertical || horizontal >= sizeHorizontal || horizontal < 0 || vertical < 0){
        cout << endl << "The indicated field is out of range";
        return T();
    }

    return matrix[vertical][horizontal];
}

template<typename T>
int Matrix<T>::countLines(string path) {
    ifstream file;
    file.open(path);

    if (!file.good()){
        cout << endl << "Error loading file in countLines method";
        return 0;
    }

    string temp;
    int count = 0;

    while (getline(file, temp)){
        if (!temp.empty())
            count++;
    }

    file.close();

    return count;
}


template<typename T>
int Matrix<T>::countWidth(string path, int linesNr) {
    ifstream file;
    file.open(path);

    if (!file.good()){
        cout << endl << "Error loading file in countWidth method";
        return 0;
    }

    string temp;
    int count = 0;

    while (file >> temp)
        count++;

    file.close();

    if (count % linesNr != 0){
        cout << endl << "Invalid file, wrong number of matrix values";
        return 0;
    }

    return count/linesNr;
}

template<typename T>
T Matrix<T>::scalarProduct(Matrix &other) {
    if (matrix == NULL || other.matrix == NULL){
        cout << endl << "No matrix";

    }

    if (sizeHorizontal != other.sizeHorizontal || sizeVertical != other.sizeVertical){
        cout << endl << "Matrix sizes do not match";

    }

    T res = 0;

    for (int i = 0; i < sizeVertical; ++i) {
        for (int j = 0; j < sizeHorizontal; ++j) {
            res += matrix[i][j] * other.matrix[i][j];
        }
    }


    return res;
}

template<typename T>
bool Matrix<T>::setAsIdentityMatrix() {
    if (matrix == NULL){
        cout << endl << "No matrix";
        return false;
    }

    if (sizeVertical != sizeHorizontal) {
        cout << endl << "This matrix is not square";
        return false;
    }

    for (int i = 0; i < sizeVertical; ++i) {
        for (int j = 0; j < sizeHorizontal; ++j) {

            if (i == j)
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;
        }
    }

    return true;
}

template<typename T>
Matrix<T> Matrix<T>::createHorizontalVector(int verticalOffSet) {
    if (matrix == NULL) {
        cout << endl << "No matrix";
        return *this;
    }

    if (verticalOffSet >= sizeVertical || verticalOffSet < 0) {
        cout << endl << "The specified row of the matrix is out of range";
        return *this;
    }

    Matrix<T> vec(1, sizeHorizontal, "HorizontalVector");

    for (int i = 0; i < sizeHorizontal; ++i)
        vec.matrix[0][i] = matrix[verticalOffSet][i];

    vec.printMatrix();

    return vec;
}

template<typename T>
Matrix<T> Matrix<T>::createVerticalVector(int horizontalOffSet) {
    if (matrix == NULL) {
        cout << endl << "No matrix";
        return *this;
    }

    if (horizontalOffSet >= sizeHorizontal || horizontalOffSet < 0) {
        cout << endl << "The indicated matrix column is out of range";
        return *this;
    }

    Matrix<T> vec(sizeVertical, 1, "VerticalVector");

    for (int i = 0; i < sizeVertical; ++i){
        vec.matrix[i][0] = matrix[i][horizontalOffSet];
    }

    vec.printMatrix();

    return vec;
}


#endif //MATRIXPROJECT_MATRIX_H