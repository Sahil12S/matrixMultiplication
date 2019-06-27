#include "Matrix.hpp"

#include <iostream>
#include <string>

int main()
{
    // This creates two matrices with default values
    std::cout << "Creating matrix m1 & m2 with default value" << '\n';
    Matrix<double> m1(3, 2, 3);
    m1.print();

    // This creates matrix using std::vector
    std::cout << "Creating matrix m using vector" << '\n';
    std::vector<std::vector<double>> v = {{1, 2, 3, 4}, {2, 3, 3, 4}};
    Matrix<double> m2(v);
    m2.print();

    // This example shows matrix multiplication where answer is stored in another variable
    std::cout << "Matrix multiplication m1 * m2" << '\n';
    Matrix<double> ans = m1 * m2;
    ans.print();

    // It shows multiplication where result is stored in original matrix
    std::cout << "Matrix multiplication with assignment m1 *= m2" << '\n';
    m1 *= m2;
    m1.print();

    // This assigns value of one matrix into another one
    std::cout << "Assigning m2 to m1" << '\n';
    m1 = m2;
    m1.print();

    // This takes transpose of matrix and store result in another matrix
    std::cout << "Taking transpose of m1" << '\n';
    Matrix<double> t = m1.transpose();
    t.print();

    // Creating a char matrix
    std::cout << "Creating character matrices" << '\n';
    Matrix<char> charMatrix(3, 3, 'a');
    charMatrix.print();

    Matrix<char> anotherCharMatrix(3, 2, 'b');
    anotherCharMatrix.print();

    // Checking multiplication of 2 char matrices
    std::cout << "Multiplication of character matrices" << '\n';
    try
    {
        auto r = charMatrix * anotherCharMatrix;
    }
    catch (const matrix_error &e)
    {
        std::cerr << "[ERROR] " << e.what() << '\n';
    }

    // Creating boolean matrix
    Matrix<bool> boolM1(2, 2, false);
    Matrix<bool> boolM2(2, 2, true);
    std::cout << "Multiplication of boolean matrix" << '\n';

    // Checking multiplication of 2 boolean matrices
    try
    {
        boolM1 *= boolM2;
    }
    catch (const matrix_error &e)
    {
        std::cerr << "[ERROR] " << e.what() << '\n';
    }

    return 0;
}