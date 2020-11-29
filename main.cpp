#include <iostream>
#include "Matrix.cpp"

using namespace std;

int main() {
    Matrix filledMatrix = Matrix(5, 5), m1 = Matrix(5, 5);
    for (int i = 0; i < filledMatrix.getRows(); ++i) {
        for (int j = 0; j < filledMatrix.getCols(); ++j) {
            filledMatrix.set(i, j, 9);
        }
    }

    //operator <<
    cout << "Utworzono dwie macierze:" << endl << m1 << filledMatrix;

    //operator + - *
    cout << m1+filledMatrix;
    cout << m1-filledMatrix;
    cout << filledMatrix*filledMatrix << endl;

    //operator ==
    cout << "Porownanie macierzy" << endl;
    cout << (filledMatrix == filledMatrix) << endl;
    cout << (filledMatrix == m1) << endl << endl;

    //operator []
    cout << "Wiersz 2 z macierzy 9" << endl;
    for(auto const&x: filledMatrix[1]) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
