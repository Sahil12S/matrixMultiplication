# Library file for working with Matrices

Features available in Matrix Library:  
1. Multiple ways to create matrix (empty, with default value, with std::vector, with another Matrix).  
2. Allow assignment of one matrix into another one.  
3. Matrix multiplication between two matrices that returns the result of multiplicaiton.  
4. Matrix mulitplication between tow matrices and store result in one of the original matrix.  
5. Multiplication between a matrix and a scalar.  
6. Transpose of matrix can be obtained.  
7. Use of templates allow creation of matrix using different data types.  
8. std::out_of_range exceptions are thrown when wrong index is accessed.  
9. Custom matrix_error exceptions are thrown when improper data-types or sizes of matrices are multiplied.  
10. Allow easy access and modification of matrix element.  
Example:
```cpp
Matrix m(2, 2, 1);
// 1 1
// 1 1

m[1][1] = 3;
m.print();
// 1 1
// 1 3
```