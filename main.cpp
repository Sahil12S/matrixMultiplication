#include "Matrix.hpp"

#include <iostream>
#include <string>

int main()
{
    // This creates two matrices with default values
    std::cout << "Creating matrix m1 with default value" << '\n';
    Matrix<double> m1(3, 2, 3);
    m1.print();
    std::cout << '\n';

    // This creates matrix using std::vector
    std::cout << "Creating matrix m2 using vector" << '\n';
    std::vector<std::vector<double>> v = {{1, 2, 3, 4}, {2, 3, 3, 4}};
    Matrix<double> m2(v);
    m2.print();
    std::cout << '\n';

    // This example shows matrix multiplication where answer is stored in another variable
    std::cout << "Matrix multiplication: ans = m1 * m2" << '\n';
    Matrix<double> ans = m1 * m2;
    ans.print();
    std::cout << '\n';

    // Update value at paritcular index
    std::cout << "Access value at index 1, 1" << '\n';
    std::cout << ans[1][1] << '\n';
    std::cout << "Modify value at index 1, 1" << '\n';
    ans[1][1] = 2;
    ans.print();
    std::cout << '\n';

    // It shows multiplication where result is stored in original matrix
    std::cout << "Matrix multiplication with assignment m1 *= m2" << '\n';
    m1 *= m2;
    m1.print();
    std::cout << '\n';

    // Multiply matrix by a constant
    std::cout << "Matrix multiplication with a double value: multByConst = m1 * " << 3.3 << '\n';
    auto multByConst = m1 * 3.3;
    multByConst.print();
    std::cout << '\n';

    std::cout << "Matrix multiplication with a integer value: multByConst *= " << 2 << '\n';
    multByConst *= 2;
    multByConst.print();
    std::cout << '\n';

    // This assigns value of one matrix into another one
    std::cout << "Assigning m2 to m1" << '\n';
    m1 = m2;
    m1.print();
    std::cout << '\n';

    // This takes transpose of matrix and store result in another matrix
    std::cout << "Taking transpose of m1" << '\n';
    Matrix<double> t = m1.transpose();
    t.print();
    std::cout << '\n';

    // Creating a char matrix
    std::cout << "Creating character matrices" << '\n';
    Matrix<char> charMatrix(3, 3, 'a');
    charMatrix.print();
    std::cout << '\n';

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
    std::cout << '\n';

    // Creating boolean matrix
    std::cout << "Creating 2 boolean matrices: boolM1 & boolM2" << '\n';
    Matrix<bool> boolM1(2, 2, false);
    boolM1.print();
    std::cout << '\n';

    Matrix<bool> boolM2(2, 2, true);
    boolM2.print();
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