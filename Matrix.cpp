#include "Matrix.hpp"

#include <vector>
#include <iostream>
#include <exception>

template <class T>
Matrix<T>::Matrix()
{
}

template <class T>
Matrix<T>::Matrix(unsigned __numRows, unsigned __numCols, T __initialVal)
{
    m_NumRows = __numRows;
    m_NumCols = __numCols;
    m_Matrix.resize(m_NumRows, std::vector<T>(m_NumCols, __initialVal));
}

template <class T>
Matrix<T>::Matrix(const std::vector<std::vector<T>> &__otherMatrix)
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
    try
    {
        for (unsigned i = 0; i < m_NumRows; i++)
        {
            if (__otherMatrix[i].size() != m_NumCols)
            {
                throw MatrixException("Not a proper matrix. All columns should be of equal size.");
            }
            for (unsigned j = 0; j < m_NumCols; j++)
            {
                m_Matrix[i][j] = __otherMatrix[i][j];
            }
        }
    }
    // catch (std::exception &e)
    catch (const MatrixException &m)
    {
        std::cout << "[ERROR] " << m.what() << '\n';
    }
}

template <class T>
Matrix<T>::Matrix(const Matrix &__otherMatrix)
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

template <class T>
Matrix<T>::~Matrix()
{
}

template <class T>
Matrix<T> Matrix<T>::operator=(const Matrix &__otherMatrix)
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

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix &__otherMatrix)
{
    Matrix res(m_NumRows, __otherMatrix.getColumnSize(), static_cast<T>(0));

    try
    {
        if (m_NumCols != __otherMatrix.getRowSize())
        {
            throw MatrixException("Mutliplication not possible. Check dimensions of matrix.");
        }
        if (std::is_same<T, char>::value || std::is_same<T, std::string>::value)
        {
            throw MatrixException("String or char matrix can't be multiplied");
        }
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
    }
    catch (const MatrixException &m)
    {
        std::cout << "[ERROR] " << m.what9) << '\n';
    }

    return res;
}

template <class T>
Matrix<T> Matrix<T>::operator*=(const Matrix &__otherMatrix)
{
    std::vector<std::vector<T>> temp(
        m_NumRows,
        std::vector<T>(__otherMatrix.getColumnSize(),
                       static_cast<T>(0)));

    try
    {
        if (m_NumCols != __otherMatrix.getRowSize())
        {
            throw MatrixException("Mutliplication not possible. Check dimensions of matrix.");
        }
        if (std::is_same<T, char>::value || std::is_same<T, std::string>::value)
        {
            throw MatrixException("String or char matrix can't be multiplied");
        }
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
    }
    catch (const MatrixException &m)
    {
        std::cout << "[ERROR] " << m.what() << '\n';
        exit(1);
    }

    m_Matrix = temp;
    m_NumCols = __otherMatrix.getColumnSize();

    return *this;
}

template <class T>
Matrix<T> Matrix<T>::transpose()
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

template <class T>
unsigned Matrix<T>::getRowSize() const
{
    return m_NumRows;
}

template <class T>
unsigned Matrix<T>::getColumnSize() const
{
    return m_NumCols;
}

template <class T>
T Matrix<T>::getVal(unsigned __row, unsigned __col) const
{
    try
    {
        if (__row < 0 || __col < 0 || __row >= m_NumRows || __col >= m_NumCols)
        {
            throw MatrixException("Index out of range.");
        }
        return m_Matrix[__row][__col];
    }
    catch (const MatrixException &m)
    {
        std::cout << "[ERROR] " << e.what() << '\n';
    }
}

template <class T>
void Matrix<T>::update(unsigned __row, unsigned __col, T __val)
{
    try
    {
        if (__row < 0 || __col < 0 || __row >= m_NumRows || __col >= m_NumCols)
        {
            throw MatrixException("Index out of range.");
        }
        m_Matrix[__row][__col] = __val;
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "[ERROR] " << e.what() << '\n';
    }
}

template <class T>
void Matrix<T>::print() const
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