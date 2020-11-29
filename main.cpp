#include <iostream>
#include "Matrix.cpp"

using namespace std;

int main() {
    Matrix m1 = Matrix(6, 3), m2 = Matrix(6, 3);
    cout << m1;
    m1.set(2, 2 ,2);
    bool e = m1 == Matrix(2, 4);
    if (e) {
        cout << e ;
    }
    return 0;
}
