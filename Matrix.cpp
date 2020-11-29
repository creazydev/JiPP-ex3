#include <iostream>
#include <fstream>
#include <math.h>
#include "Matrix.h"

using namespace std;

//podstawowe funkcjonalnosci
Matrix::Matrix(int n, int m) {
    Matrix::rows = n;
    Matrix::columns = m;
    Matrix::matrixArray = allocateMemoryToMatrixArray(n, m, Matrix::matrixArray);
}

Matrix::Matrix(int squareMatrixSize) : Matrix(squareMatrixSize, squareMatrixSize) {}

Matrix::Matrix(int n, int m, double** &arr) {
    Matrix::rows = n;
    Matrix::columns = m;
    Matrix::matrixArray = arr;
}

Matrix::Matrix(string path) {
    readFromFile(path);
}

//copy constructor
Matrix::Matrix(const Matrix &matrix2) {
    Matrix::rows = matrix2.rows;
    Matrix::columns = matrix2.columns;
    Matrix::matrixArray = matrix2.matrixArray;
}

//destructor
Matrix::~Matrix() {
    for (int i = 0; i < Matrix::getRows(); i++) {
        delete [] Matrix::matrixArray[i];
    }
    delete [] Matrix::matrixArray;
}

double** Matrix::allocateMemoryToMatrixArray(int n, int m, double ** &array) {
    array = new double *[n];
    for (int i = 0; i < n; i++) {
        array[i] = new double[m];
    }
    return array;
}

void Matrix::set(int n, int m, double val) {
    Matrix::matrixArray[n][m] = val;
}

double Matrix::get(int n, int m) {
    return Matrix::matrixArray[n][m];
}

int Matrix::getCols() {
    return Matrix::columns;
}

int Matrix::getRows() {
    return Matrix::rows;
}

void Matrix::print() {
    for (int i = 0; i < Matrix::rows; i++) {
        for (int j = 0; j < Matrix::columns; j++) {
            cout << Matrix::matrixArray[i][j] << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::add(Matrix &matrix2) {
    cout << "Add "<< this << " to " << &matrix2 << endl;

    if (Matrix::rows == matrix2.rows && Matrix::columns == matrix2.columns) {
        double **result;
        result = allocateMemoryToMatrixArray(Matrix::rows, Matrix::columns, result);

        for (int i = 0; i < Matrix::rows; ++i) {
            for (int j = 0; j < Matrix::columns; j++) {
                double value = Matrix::matrixArray[i][j] + matrix2.matrixArray[i][j];
                result[i][j] = value;
            }
        }
        return Matrix(Matrix::rows, Matrix::columns, result);
    } else {
        cout << "Number of rows and cols must be the same!";
        return matrix2;
    }
}

Matrix Matrix::subtract(Matrix &matrix2) {
    cout << "Substract "<< &matrix2 << " from " << this << endl;

    if (Matrix::rows == matrix2.rows && Matrix::columns == matrix2.columns) {
        double **result;
        result = allocateMemoryToMatrixArray(Matrix::rows, Matrix::columns, result);

        for (int i = 0; i < Matrix::rows; ++i) {
            for (int j = 0; j < Matrix::columns; j++) {
                result[i][j] = Matrix::matrixArray[i][j] - matrix2.matrixArray[i][j];
            }
        }
        return Matrix(Matrix::rows, Matrix::columns, result);
    } else {
        cout << "Number of rows and cols must be the same!";
        return matrix2;
    }
}

Matrix Matrix::multiply(Matrix &matrix2) {
    cout << "Multiply "<< &matrix2 << " by " << this << endl;

    if (Matrix::columns == matrix2.rows) {
        double **result;
        result = allocateMemoryToMatrixArray(Matrix::rows, matrix2.columns, result);

        for (int i = 0; i < Matrix::rows; ++i) {
            for (int j = 0; j < matrix2.columns; j++) {
                for (int k = 0; k < Matrix::columns; k++) {
                    result[i][j] += Matrix::matrixArray[i][k] * matrix2.matrixArray[k][j];
                }
            }
        }
        return Matrix(Matrix::rows, matrix2.columns, result);
    } else {
        cout << "Cannot multiply!";
        return matrix2;
    }
}

void Matrix::store(std::string filename, std::string path) {
    ofstream outputFile(path + filename);
    outputFile << Matrix::rows <<" "<< Matrix::columns << endl;

    for (int i = 0; i < Matrix::rows; ++i) {
        for (int j = 0; j < Matrix::columns; j++) {
            outputFile << Matrix::matrixArray[i][j] << " ";
        }
        outputFile << endl;
    }
}

void Matrix::readFromFile(string path) {
    ifstream inputFile(path);
    if (inputFile.is_open()) {
        inputFile >> Matrix::rows;
        inputFile >> Matrix::columns;
        Matrix::matrixArray = allocateMemoryToMatrixArray(Matrix::rows, Matrix::columns, Matrix::matrixArray);

        for (int i = 0; i < Matrix::rows; ++i) {
            for (int j = 0; j < Matrix::columns; j++) {
                inputFile >> Matrix::matrixArray[i][j];
            }
        }
        inputFile.close();
    }
}

//przeciazone metody
Matrix Matrix::operator+(Matrix &matrix2) {
    return add(matrix2);
}

Matrix Matrix::operator-(Matrix &matrix2) {
    return subtract(matrix2);
}

Matrix Matrix::operator*(Matrix &matrix2) {
    return multiply(matrix2);
}

ostream& operator <<(ostream &os, const Matrix &matrix) {
    os << matrix.rows << " " << matrix.columns << endl;
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.columns; j++) {
            os << matrix.matrixArray[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

bool Matrix::operator ==(const Matrix &matrix2) {
    float EPSILON = 0.000001;
    if (Matrix::getRows() != matrix2.rows || Matrix::getCols() != matrix2.columns) {
        return false;
    }

    for (int i = 0; i < Matrix::getRows(); i++) {
        for (int j = 0; j < Matrix::getCols(); j++) {
            if (abs(Matrix::get(i, j) - matrix2.matrixArray[i][j]) > EPSILON) {
                return false;
            }
        }
    }

    return true;
}

list<double> Matrix::operator[](int rowIndex) {
    list<double> rowValues;
    for (int i = 0; i < Matrix::getCols(); ++i) {
        rowValues.push_back(Matrix::get(rowIndex, i));
    }
    return rowValues;
}
