// Matrix imlementation C++
//
// Author: Sahil Sharma
//

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <exception>
#include <assert.h>

// Exception class to handle matrix exceptions
class matrix_error : public std::exception
{
private:
    std::string err;

public:
    matrix_error(const std::string &what_arg) : err(what_arg) {}
    virtual const char *what() const throw()
    {
        return err.c_str();
    }
};

template <class T>
class Matrix
{

private:
    // Used to store number of rows in matrix
    size_t m_NumRows;

    // Used to store number of columns in matrix
    size_t m_NumCols;

    // Used to store all the values of matrix
    std::vector<std::vector<T>> m_Matrix;

public:
    /**
     *  @brief  Constructor that creates empty matrix of size __numRows * __numCols
     *  @param __numRows  Number of rows in matrix
     *  @param __numCols  Number of columns in matrix
     *  @param __initialVal  Initial value with which complete matrix is to be initialized
     *          default is 0 of class T
     * 
     *  This constructor takes 3 arguments, __numRows and __numCols are dimensions of matrix
     *  that is to be created and are required. Matrix will be initialized with __initialVal
     *  on creation and with 0 if no value is provided.
     */
    Matrix(size_t __numRows, size_t __numCols, T __initialVal = static_cast<T>(0))
    {
        m_NumRows = __numRows;
        m_NumCols = __numCols;
        m_Matrix.resize(m_NumRows, std::vector<T>(m_NumCols, __initialVal));
    }

    /**
     *  @brief  Constructor that creates empty matrix from given 2D vector
     *  @param __otherMatrix  A 2D vector representing a matrix
     * 
     *  This constructor takes a 2D vector __otherMatrix and creates a matrix
     *  using all the values present in that vector. Vector is checked to have
     *  all rows of equal size and 
     */
    Matrix(const std::vector<std::vector<T>> &__otherMatrix)
    {
        m_NumRows = __otherMatrix.size();

        if (m_NumRows == 0)
        {
            return;
        }
        m_NumCols = __otherMatrix[0].size();
        if (m_NumCols == 0)
        {
            return;
        }
        m_Matrix.resize(m_NumRows, std::vector<T>(m_NumCols));

        for (size_t i = 0; i < m_NumRows; i++)
        {
            for (size_t j = 0; j < m_NumCols; j++)
            {
                m_Matrix[i][j] = __otherMatrix[i][j];
            }
        }
    }

    /**
     *  @brief  Copy constructor to create copy of existing matrix
     *  @param __otherMatrix  Another matrix that is to be copied
     * 
     *  This constructor creates a copy of matrix from another matrix
     */
    Matrix(const Matrix &__otherMatrix)
    {
        m_NumRows = __otherMatrix.getRowSize();
        m_NumCols = __otherMatrix.getColumnSize();

        m_Matrix.resize(m_NumRows, std::vector<T>(m_NumCols, static_cast<T>(0)));
        for (size_t i = 0; i < m_NumRows; i++)
        {
            for (size_t j = 0; j < m_NumCols; j++)
            {
                m_Matrix[i][j] = __otherMatrix[i][j];
            }
        }
    }

    // Destructor
    virtual ~Matrix()
    {
    }

    /**
     *  @brief  Assign values from one matrix to another
     *  @param __otherMatrix  Matrix that is to be copied
     *  @return  Returns result matrix on assigning values from __otherMatrix
     * 
     *  Overloaded assignment operator for assigning one matrix to other.
     *  On performing the operation, current matrix will become same as __otherMatrix.
     */
    virtual Matrix operator=(const Matrix &__otherMatrix)
    {
        if (&__otherMatrix == this)
        {
            return *this;
        }

        m_NumRows = __otherMatrix.getRowSize();
        m_NumCols = __otherMatrix.getColumnSize();
        m_Matrix.resize(m_NumRows, std::vector<T>(m_NumCols, static_cast<T>(0)));

        for (size_t i = 0; i < m_NumRows; i++)
        {
            for (size_t j = 0; j < m_NumCols; j++)
            {
                m_Matrix[i][j] = __otherMatrix[i][j];
            }
        }
        return *this;
    }

    /**
     *  @brief  Useful for modifying element or row of matrix
     *  @param __rowNum  Row number that is to be accessed
     *  @return  Returns reference to std::vector<T> at that index
     *  @throw  std::out_of_range when __rowNum >= m_NumRows
     * 
     *  Overloaded [] operator that allows modification of element or row of matrix
     *  __rowNum is first checked for valid range
     *  and return row of that index as std::vector
     */
    std::vector<T> &operator[](size_t __rowNum)
    {
        if (__rowNum >= m_NumRows)
        {
            std::string err_msg = "Number of rows in matrix: " + std::to_string(m_NumRows) + ". Queried row " + std::to_string(__rowNum);
            throw std::out_of_range(err_msg);
        }
        return m_Matrix[__rowNum];
    }

    /**
     *  @brief  Use to acces a row or element of matrix
     *  @param __rowNum  Row number that is to be accessed
     *  @return  Returns std::vector<T> at that index
     *  @throw  std::out_of_range when __rowNum >= m_NumRows
     * 
     *  Overloaded [] operator for acces to matrix row or element.
     *  __rowNum is first checked for valid range
     *  and return row of that index as std::vector
     *  This function doesn't allow modification of any kind
     */
    const std::vector<T> &operator[](size_t __rowNum) const
    {
        if (__rowNum >= m_NumRows)
        {
            std::string err_msg = "Number of rows in matrix: " + std::to_string(m_NumRows) + ". Queried row " + std::to_string(__rowNum);
            throw std::out_of_range(err_msg);
        }
        return m_Matrix[__rowNum];
    }

    /**
     *  @brief  Multiply 2 matrices and return the result
     *  @param __otherMatrix  Second (right) matrix for multiplication
     *  @return  Returns result on multiplication of two matrices
     *  @throw  matrix_error when multiplication is performed on char, string or boolean matrices
     *          and when matrices are not of MxN and NxP sizes
     * 
     *  Overloaded multiplication operator for multiplication of two matrices.
     *  Matrices are first checked if operation can be performed on data_type
     *  and matrix sizes are checked for valid multiplication operation.
     *  On multiplying both matrices it returns the result.
     */
    virtual Matrix operator*(const Matrix &__otherMatrix)
    {
        if (std::is_same<T, char>::value)
        {
            throw matrix_error("Matrix multiplication can't be performed on char matrix");
        }
        if (std::is_same<T, std::string>::value)
        {
            throw matrix_error("Matrix multiplication can't be performed on string matrix");
        }
        if (std::is_same<T, bool>::value)
        {
            throw matrix_error("Matrix multiplication can't be performed on boolean matrix");
        }

        Matrix res(m_NumRows, __otherMatrix.getColumnSize(), static_cast<T>(0));

        if (m_NumCols != __otherMatrix.getRowSize())
        {
            std::string err_msg = "Allowed matrices of size: MxN & NxP. Here: " + std::to_string(m_NumRows) + "x" + std::to_string(m_NumCols) + " & " + std::to_string(__otherMatrix.getRowSize()) + "x" + std::to_string(__otherMatrix.getColumnSize());
            throw std::out_of_range(err_msg);
        }

        for (size_t i = 0; i < m_NumRows; i++)
        {
            for (size_t j = 0; j < __otherMatrix.getColumnSize(); j++)
            {
                for (size_t k = 0; k < m_NumCols; k++)
                {
                    T val = (*this)[i][k] * __otherMatrix[k][j];
                    res[i][j] = res[i][j] + val;
                }
            }
        }

        return res;
    }

    /**
     *  @brief  Multiply a matrix with a constant value and return the result
     *  @param __num  Constant value (can be char, bool or any numeric data type)
     *  @return  Returns result of multiplication
     *  @throw  matrix_error when multiplication is performed on char, string or boolean matrices
     * 
     *  Overloaded multiplication operator for multiplication of a matrix with a constant value.
     *  Matrix & __num are first checked if operation can be performed on the data_type
     *  It multiplies every element of matrix with __num.
     */
    virtual Matrix operator*(const T &__num)
    {
        if (std::is_same<T, char>::value)
        {
            throw matrix_error("Matrix multiplication can't be performed on char matrix");
        }
        if (std::is_same<T, std::string>::value)
        {
            throw matrix_error("Matrix multiplication can't be performed on string matrix");
        }
        if (std::is_same<T, bool>::value)
        {
            throw matrix_error("Matrix multiplication can't be performed on boolean matrix");
        }

        Matrix res(*this);

        for (size_t i = 0; i < m_NumRows; i++)
        {
            for (size_t j = 0; j < m_NumCols; j++)
            {
                T val = (*this)[i][j] * __num;
                res[i][j] = val;
            }
        }

        return res;
    }

    /**
     *  @brief  Multiplies 2 matrices and store answer in original one
     *  @param __otherMatrix  Second (right) matrix for multiplication
     *  @return  Returns original matrix after storing multiplication result in it
     *  @throw  matrix_error when multiplication is performed on char, string or boolean matrices
     *          and when matrices are not of MxN and NxP sizes
     * 
     *  Overloaded assignment multiplication operator for multiplication of two matrices
     *  that store result back in original (first) matrix and returns it as the result.
     *  Matrices are first checked if operation can be performed on data_type
     *  and matrix sizes are checked for valid multiplication operation.
     *  This operation changes the original matrix that is on the left side of operator with
     *  the result of multiplication.
     */
    virtual Matrix operator*=(const Matrix &__otherMatrix)
    {
        if (std::is_same<T, char>::value)
        {
            throw matrix_error("Matrix multiplication can't be performed on char matrix");
        }
        if (std::is_same<T, std::string>::value)
        {
            throw matrix_error("Matrix multiplication can't be performed on string matrix");
        }
        if (std::is_same<T, bool>::value)
        {
            throw matrix_error("Matrix multiplication can't be performed on boolean matrix");
        }

        std::vector<std::vector<T>> temp(
            m_NumRows,
            std::vector<T>(__otherMatrix.getColumnSize(),
                           static_cast<T>(0)));

        if (m_NumCols != __otherMatrix.getRowSize())
        {
            std::string err_msg = "Allowed matrices of size: MxN & NxP. Here: " + std::to_string(m_NumRows) + "x" + std::to_string(m_NumCols) + " & " + std::to_string(__otherMatrix.getRowSize()) + "x" + std::to_string(__otherMatrix.getColumnSize());
            throw matrix_error(err_msg);
        }

        for (size_t i = 0; i < m_NumRows; i++)
        {
            for (size_t k = 0; k < __otherMatrix.getColumnSize(); k++)
            {
                for (size_t j = 0; j < m_NumCols; j++)
                {
                    T val = (*this)[i][j] * __otherMatrix[j][k];
                    temp[i][k] = temp[i][k] + val;
                }
            }
        }

        m_Matrix = temp;
        m_NumCols = __otherMatrix.getColumnSize();

        return *this;
    }

    /**
     *  @brief  Multiply a matrix by a constant value
     *  @param __otherMatrix  Second (right) matrix for multiplication
     *  @return  Returns original matrix after storing multiplication result in it
     *  @throw  matrix_error when multiplication is performed on char, string or boolean matrices
     * 
     *  Overloaded assignment multiplication operator for multiplication of a matrix with a constant value
     *  that store result back in original (first) matrix and returns it as the result.
     *  Matrix & __num are first checked if operation can be performed on data_type
     *  This operation changes the original matrix with the result of multiplication.
     */
    virtual Matrix operator*=(const T &__num)
    {
        if (std::is_same<T, char>::value)
        {
            throw matrix_error("Matrix multiplication can't be performed on char matrix");
        }
        if (std::is_same<T, std::string>::value)
        {
            throw matrix_error("Matrix multiplication can't be performed on string matrix");
        }
        if (std::is_same<T, bool>::value)
        {
            throw matrix_error("Matrix multiplication can't be performed on boolean matrix");
        }

        for (size_t i = 0; i < m_NumRows; i++)
        {
            for (size_t j = 0; j < m_NumCols; j++)
            {
                (*this)[i][j] = (*this)[i][j] * __num;
            }
        }

        return *this;
    }

    /**
     *  @brief  Returns transpose of matrix
     *  @return  Transpose of matrix
     * 
     *  This function returns transpose of current matrix.
     *  Transpose of matrix is obtained after swapping rows and columns of matrix
     */
    Matrix transpose()
    {
        Matrix res(m_NumCols, m_NumRows, static_cast<T>(0));
        for (size_t i = 0; i < m_NumRows; i++)
        {
            for (size_t j = 0; j < m_NumCols; j++)
            {
                // res.update(j, i, m_Matrix[i][j]);
                res[j][i] = (*this)[i][j];
            }
        }
        return res;
    }

    /**
     *  @brief  Returns number of rows in matrix
     *  @return  Number of rows in the matrix
     * 
     *  This function returns the row size of the matrix
     */
    size_t getRowSize() const
    {
        return m_NumRows;
    }

    /**
     *  @brief  Returns number of columns in matrix
     *  @return  Number of columns in the matrix
     * 
     *  This function returns the column size of the matrix
     */
    size_t getColumnSize() const
    {
        return m_NumCols;
    }

    // Prints the matrix
    void print() const
    {
        for (size_t i = 0; i < m_NumRows; i++)
        {
            for (size_t j = 0; j < m_NumCols; j++)
            {
                std::cout << m_Matrix[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
};

#endif // MATRIX_H