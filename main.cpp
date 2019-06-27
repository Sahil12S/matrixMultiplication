#include "Matrix.hpp"

#include <iostream>
#include <string>

// #include <debug/formatter.h>
int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5};
    // std::cout << vec.at(5) << std::endl;

    std::cout << "Creating matrix m1 & m2 with default value" << '\n';
    Matrix<int> m1(3, 3, 3);
    m1.print();

    Matrix<int> m2(2, 4, 2);
    m2.print();

    std::vector<std::vector<double>> v = {{1, 1}, {1, 1}, {1, 1}};

    std::cout << "Creating matrix m using vector" << '\n';
    Matrix<double> m(v);
    m.print();
    // v.resize(1);

    std::cout << "Matrix multiplication m1 * m2" << '\n';
    Matrix<int> ans = m1 * m2;
    ans.print();

    std::cout << "Matrix multiplication with assignment m1 *= m2" << '\n';
    m1 *= m2;
    m1.print();

    std::cout << "Assigning m2 to m1" << '\n';
    m1 = m2;
    m1.print();

    std::cout << "Taking transpose of m1" << '\n';
    Matrix<int> t = m1.transpose();
    t.print();
    // t.update(10, 10, 3);

    std::cout << "Creating character matrices" << '\n';
    // Matrix<char> charMatrix(3, 3, 'a');
    // charMatrix.print();

    // Matrix<char> anotherCharMatrix(3, 2, 'b');
    // anotherCharMatrix.print();

    std::cout << "Multiplication of character matrices" << '\n';
    // charMatrix *= anotherCharMatrix;

    return 0;
}