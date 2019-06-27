# Library file for working with Matrices

Features available in Matrix Library:
1. Multiple ways to create matrix (empty, with default value, with std::vector, with another Matrix).
2. Allow assignment of one matrix into another one.
3. Matrix multiplication between two matrices that returns the result of multiplicaiton.
4. Matrix mulitplication between tow matrices and store result in one of the original matrix.
5. Transpose of matrix can be obtained.
6. Use of templates allow creation of matrix using different data types.
7. std::out_of_range exceptions are thrown when wrong index is accessed.
8. Custom matrix_error exceptions are thrown when improper data-types or sizes of matrices are multiplied.