// Matrix imlementation C++
//
//

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <exception>
#include <assert.h>

class MatrixException
{
private:
    const std::string errMessage;
    // const char *errMessage;

public:
    MatrixException(const char *msg) : errMessage(msg) {}
    ~MatrixException() {}
    virtual const char *what() const throw()
    {
        return errMessage.c_str();
    }
};

template <class T>
class Matrix
{

private:
    // Used to store number of rows in matrix
    unsigned m_NumRows;

    // Used to store number of columns in matrix
    unsigned m_NumCols;

    // Used to store all the values of matrix
    std::vector<std::vector<T>> m_Matrix;

    std::string err_msg;

public:
    // Constructor
    Matrix()
    {
    }

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
    Matrix(unsigned __numRows, unsigned __numCols, T __initialVal = static_cast<T>(0))
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
        // try
        // {
        for (unsigned i = 0; i < m_NumRows; i++)
        {
            // if (__otherMatrix[i].size() != m_NumCols)
            // {
            //     // std::string msg
            //     // throw std::out_of_range("All row sizes should be same");
            //     // throw MatrixException("Not a proper matrix. All columns should be of equal size.");
            // }
            for (unsigned j = 0; j < m_NumCols; j++)
            {
                m_Matrix[i][j] = __otherMatrix[i][j];
            }
        }
        // }
        // catch (std::exception &e)
        // catch (const MatrixException &m)
        // catch (const std::out_of_range &e)
        // {
        //     std::cout << "[ERROR] " << e.what() << '\n';
        // }
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
                m_Matrix[i][j] = __otherMatrix.getVal(i, j);
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

        for (int i = 0; i < m_NumRows; i++)
        {
            for (int j = 0; j < m_NumCols; j++)
            {
                m_Matrix[i][j] = __otherMatrix.getVal(i, j);
            }
        }
        return *this;
    }

    /**
     *  @brief  Multiply 2 matrices and return the result
     *  @param __otherMatrix  Second (right) matrix for multiplication
     *  @return  Returns result on multiplication of two matrices
     * 
     *  Overloaded multiplication operator for multiplication of two matrices.
     *  On multiplying both matrices it returns the result.
     */
    virtual Matrix operator*(const Matrix &__otherMatrix)
    {
        static_assert(!std::is_same<T, char>::value, "Matrix multiplication can't be performed on char");
        static_assert(!std::is_same<T, std::string>::value, "Matrix multiplication can't be performed on char");

        Matrix res(m_NumRows, __otherMatrix.getColumnSize(), static_cast<T>(0));

        // try
        // {
        if (m_NumCols != __otherMatrix.getRowSize())
        {
            err_msg = "Allowed matrices of size: MxN & NxP. Here: " + std::to_string(m_NumRows) + "x" + std::to_string(m_NumCols) + " & " + std::to_string(__otherMatrix.getRowSize()) + "x" + std::to_string(__otherMatrix.getColumnSize());
            // throw MatrixException("Mutliplication not possible. Check dimensions of matrix.");
            // throw std::out_of_range("Matrix column row doesn't match");
            throw std::out_of_range(err_msg);
        }

        // if (std::is_same<T, char>::value || std::is_same<T, std::string>::value)
        // {
        //     throw MatrixException("String or char matrix can't be multiplied");
        // }

        // Now loop through
        for (unsigned i = 0; i < m_NumRows; i++)
        {
            for (unsigned k = 0; k < __otherMatrix.getColumnSize(); k++)
            {
                for (unsigned j = 0; j < m_NumCols; j++)
                {
                    T val = m_Matrix[i][j] * __otherMatrix.getVal(j, k);
                    res.update(i, k, res.getVal(i, k) + val);
                }
            }
        }
        // }
        // catch (const MatrixException &m)
        // {
        //     std::cout << "[ERROR] " << m.what() << '\n';
        // }

        return res;
    }

    /**
     *  @brief  Multiplies 2 matrices and store answer in original one
     *  @param __otherMatrix  Second (right) matrix for multiplication
     *  @return  Returns original matrix after storing multiplication result in it
     * 
     *  Overloaded assignment multiplication operator for multiplication of two matrices
     *  that store result back in original (first) matrix and returns it as the result.
     *  This changes the original matrix that is on left side of operator with
     *  the result of multiplication.
     */
    virtual Matrix
    operator*=(const Matrix &__otherMatrix)
    {
        static_assert(!std::is_same<T, char>::value, "Matrix multiplication can't be performed on char");
        static_assert(!std::is_same<T, std::string>::value, "Matrix multiplication can't be performed on char");

        std::vector<std::vector<T>> temp(
            m_NumRows,
            std::vector<T>(__otherMatrix.getColumnSize(),
                           static_cast<T>(0)));

        // try
        // {
        if (m_NumCols != __otherMatrix.getRowSize())
        {
            err_msg = "Allowed matrices of size: MxN & NxP. Here: " + std::to_string(m_NumRows) + "x" + std::to_string(m_NumCols) + " & " + std::to_string(__otherMatrix.getRowSize()) + "x" + std::to_string(__otherMatrix.getColumnSize());
            // throw MatrixException("Mutliplication not possible. Check dimensions of matrix.");
            // throw std::out_of_range("Matrix column row doesn't match");
            throw std::out_of_range(err_msg);
        }

        // if (std::is_same<T, std::string>::value || std::is_same<T, char>::value)
        // {
        //     throw "String or char matrix can't be multiplied";
        // }

        // Now loop through
        for (unsigned i = 0; i < m_NumRows; i++)
        {
            for (unsigned k = 0; k < __otherMatrix.getColumnSize(); k++)
            {
                for (unsigned j = 0; j < m_NumCols; j++)
                {
                    T val = m_Matrix[i][j] * __otherMatrix.getVal(j, k);
                    temp[i][k] += +val;
                }
            }
        }
        // }
        // catch (const MatrixException &m)
        // {
        //     std::cout << "[ERROR] " << m.what() << '\n';
        // }

        m_Matrix = temp;
        m_NumCols = __otherMatrix.getColumnSize();

        return *this;
    }

    /**
     *  @brief  Returns transpose of matrix
     *  @return  Transpose of matrix
     * 
     *  This function returns transpose of current matrix.
     *  Transpose of matrix is obtained after swapping rows and columns of matrix
     */
    virtual Matrix transpose()
    {
        Matrix res(m_NumCols, m_NumRows, static_cast<T>(0));
        for (unsigned i = 0; i < m_NumRows; i++)
        {
            for (unsigned j = 0; j < m_NumCols; j++)
            {
                res.update(j, i, m_Matrix[i][j]);
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
    virtual unsigned getRowSize() const
    {
        return m_NumRows;
    }

    /**
     *  @brief  Returns number of columns in matrix
     *  @return  Number of columns in the matrix
     * 
     *  This function returns the column size of the matrix
     */
    virtual unsigned getColumnSize() const
    {
        return m_NumCols;
    }

    /**
     *  @brief  Returns value from matrix at given position
     *  @param __row  Row position in matrix
     *  @param __col  Column position in matrix
     *  @return  Value present in matrix at given position
     *  @throw  std::out_of_range  If __row >= m_NumRows or __col >= m_NumCols
     *      or __row < 0 or __col < 0
     * 
     *  This function takes row and columns position in matrix
     *  and returns value present at that position in matrix
     */
    virtual T getVal(unsigned __row, unsigned __col) const
    {
        // try
        // {
        if (__row >= m_NumRows || __col >= m_NumCols)
        {
            std::string err = "Matrix of size: " + std::to_string(m_NumRows) + "x" + std::to_string(m_NumCols) + ". Queried row & col index " + std::to_string(__row) + "," + std::to_string(__col);
            throw std::out_of_range(err);
        }
        // }
        // catch (const MatrixException &m)
        // {
        //     std::cout << "[ERROR] " << m.what() << '\n';
        // }
        return m_Matrix[__row][__col];
    }

    /**
     *  @brief  Updates value in matrix at given position
     *  @param __row  Row position where value is to be updated
     *  @param __col  Column position where value is to be updated
     *  @param __val  New value for the given position
     *  
     *  This function takes row and columns positions int the matrix
     *  and new value with which existing value is to be replaced.
     */
    virtual void update(unsigned __row, unsigned __col, T __val)
    {
        // try
        // {
        if (__row >= m_NumRows || __col >= m_NumCols)
        {
            // throw MatrixException("Index out of range.");
            err_msg = "Matrix of size: " + std::to_string(m_NumRows) + "x" + std::to_string(m_NumCols) + ". Queried row & col index " + std::to_string(__row) + "," + std::to_string(__col);
            throw std::out_of_range(err_msg);
        }
        m_Matrix[__row][__col] = __val;
        // }
        // catch (const MatrixException &m)
        // {
        //     std::cout << "[ERROR] " << m.what() << '\n';
        // }
    }

    // Prints the matrix
    virtual void print() const
    {
        for (unsigned i = 0; i < m_NumRows; i++)
        {
            for (unsigned j = 0; j < m_NumCols; j++)
            {
                std::cout << m_Matrix[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
};

#endif // MATRIX_H