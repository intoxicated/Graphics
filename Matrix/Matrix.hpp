/**
 * Matrix template 
 *
 * Author: Wooyoung Chung
 *
 * Last Modified: 1/24/14
 *
 */

#ifndef __cs_matrix_hpp__
#define __cs_matrix_hpp__


#define TOLERANCE   0.0001

#include <cmath>
#include <initializer_list>
#include <math.h>
#include <stdexcept>

using namespace std;


// Prototype of the Matrix class 
// (so that it can be used in the friend prototypes)
template <int R, int C> class Matrix;


// Prototypes of friend functions 
template <int RC>
double cof(const Matrix<RC,RC>& a, int i, int j);

double det(double a);

template <int RC>
double det(const Matrix<RC,RC>& a);

template<int R, int C>
double dot(const Matrix<R,C>& a, const Matrix<R,C>& b);

template <int RC>
Matrix<RC,RC> identity();   

template <int RC>
double matrix_minor(const Matrix<RC,RC>& a, int i, int j);

template <int RLR, int CL, int CR>
Matrix<RLR,CL+CR> operator|(const Matrix<RLR,CL>& a, const Matrix<RLR,CR>& b);   

template <int R, int C>
Matrix<R,C> operator+(const Matrix<R,C>& a, const Matrix<R,C>& b);

template <int R, int C>
Matrix<R,C> operator-(const Matrix<R,C>& a, const Matrix<R,C>& b);

template <int RL, int CLRR, int CR>
Matrix<RL,CR> operator*(const Matrix<RL,CLRR>& a, const Matrix<CLRR,CR>& b);

template <int R, int C>
Matrix<R,C> operator*(double k, const Matrix<R,C>& a);

template <int R, int C>
Matrix<R,C> operator*(const Matrix<R,C>& a, double k);

template <int R, int C>
bool operator==(const Matrix<R,C>& a, const Matrix<R,C>& b);

template <int R, int C>
bool operator!=(const Matrix<R,C>& a, const Matrix<R,C>& b);

double submatrix(const Matrix<2,2>& a, int i, int j);

template <int R, int C>
Matrix<R-1,C-1> submatrix(const Matrix<R,C>& a, int i, int j);

template <int R, int C>
Matrix<C,R> trans(const Matrix<R,C>& a);



// Class declaration
//
// Note: All friend functions are one-to-one with the class. For example,
// there is a cof<3,3> that corresponds to Matrix<3,3>, ...
//
// The parameters RALL and CALL correspond to the number of rows and
// columns, respectively, in all of the methods/functions that
// have sizes in common
template <int RALL, int CALL>
class Matrix
{
  protected:
   double**            values;   
   int                 columns, rows;
   

   void allocateMemory(int rows, int columns);
   void deallocateMemory();
   void setValues(double value);
   void setValues(const Matrix& other);   
   void setValues(const double* values);   
   void setValues(double** values);
   

  public:
    /**
     * Default Constructor for RALL x CALL Matrix objects
     */
    Matrix<RALL,CALL>();

    /**
     * Copy Constructor for RALL x CALL Matrix objects
     */
    Matrix<RALL,CALL>(const Matrix<RALL,CALL>& original);
    
    /**
     * Destructor for RALL x CALL Matrix objects
     */
    ~Matrix<RALL,CALL>();
    
    /**
     * Calculate the cofactor of an RC x RC matrix (i.e., the signed
     * determinate of the matrix with row i and column j removed)
     *
     * @param a   The matrix
     * @param i   The index of the row to exclude
     * @param j   The index of the column to exclude
     * @throws    out_of_range if i or j are out of bounds
     * @return    The cofactor
     */
    template <int RC>
    friend double cof(const Matrix<RC,RC>& a, int i, int j);

    /**
     * Calculate the determinant of a scalar (which is useful when
     * calculating the determinant of a matrix using cofactors)
     *
     * Note: This is a function template so that it is 1:1 with the class
     * (which avoid problems of duplicate definitions when linking)
     *
     * @param a   The value of the scalar
     * @return    The determinant of a (which is just a)
     */
    template <int R, int C>
    friend double det(double a);
    
    /**
     * Calculate the determinant of an RC x RC matrix
     *
     * @param a   The matrix
     * @throws    length_error if the Matrix is smaller than 2x2
     * @return    The value of the determinant
     */
    template <int RC>
    friend double det(const Matrix<RC,RC>& a);
    
    /**
     * Calculate the dot product (more commonly known as the scalar product)
     * of two R x C matrices
     *
     *
     * @param a  The left Matrix
     * @param b  The right Matrix
     * @return   The scalar product
     */
    template<int R, int C>
    friend double dot(const Matrix<R,C>& a, const Matrix<R,C>& b);
    
    /**
     * Get a particular element of this RALL x CALL Matrix.
     *
     * @param r   The row index
     * @param c   The column index
     * @throws    out_of_range if r or c are out of bounds
     * @return    The value of the element
     */
    double get(int r, int c) const;
    
    /**
     * Get a particular element of this RALL x CALL Matrix if it contains
     * a single row or single column
     *
     * @param i   The index
     * @throws    out_of_range if i is out of bounds
     * @throws    length_error if this is neither a single row nor single column
     * @return    The value of the element
     */
    double get(int i) const;
    
    /**
     * Get a RALL x 1 column of this RALL x CALL Matrix
     *
     * @param c   The index of the column (0-based)
     * @return    The column
     */
    Matrix<RALL,1> getColumn(int c) const;   
    
    /**
     * Get the number of columns in this RALL x CALL Matrix
     *
     * @return  The number of columns (i.e., CALL)
     */
    int getColumns() const;
    
    /**
     * Get the number of rows in this RALL x CALL Matrix
     *
     * @return  The number of rows (i.e., RALL)
     */
    int getRows() const;
    
    /**
     * Create and return an RC x RC identity matrix
     *
     * Note: This function must return by value because the result Matrix
     * is a local variable.
     *
     * @return        An identity Matrix
     */
    template <int RC>
    friend Matrix<RC,RC> identity();   
    
    /**
     * Calculate the minor of an RC x RC Matrix (i.e., the determinant of
     * the submatrix formed by deleting a row and column)
     *
     * @param a   The matrix
     * @param i   The index of the row to exclude
     * @param j   The index of the column to exclude
     * @return    The minor
     */
    template <int RC>
    friend double matrix_minor(const Matrix<RC,RC>& a, int i, int j);
  
    /**
     * Access an element of this RALL x CALL Matrix using the 
     * function-call operator.
     *
     * @param r   The row index
     * @param c   The column index
     * @throws    out_of_range if r or c are out of bounds
     * @return    The value of the element
     */
    double& operator()(int r, int c);
    
    /**
     * Access a particular element of this RALL x CALL Matrix using
     * the function call operator if it contains a single row or
     * single column
     *
     * @param i   The index
     * @throws    out_of_range if i is out of bounds
     * @throws    length_error if this is neither a single row nor single column
     * @return    The the element
     */
    double& operator()(int i);
    
    /**
     * Assign an initializer_list to this RALL x CALL Matrix
     *
     * @param m   The initializer_list containing the values
     * @return    The Matrix referred to by this
     */
    Matrix<RALL,CALL>& operator=(std::initializer_list<double> values);
    
    /**
     * Assign another RALL x CALL Matrix to this RALL x CALL Matrix
     *
     * @param other   The Matrix to copy
     * @return        The Matrix referred to by this
     */
    Matrix<RALL,CALL>& operator=(const Matrix<RALL,CALL>& other);
    
    /**
     * Concatenate the columns of the RLR x CL Matrix a and the 
     * columns of the RLR x CR Matrix b to create a
     * RLR x CL+CR Matrix
     *
     * @param a   The left Matrix
     * @param b   The right Matrix
     * @return    a concatenated with b
     */
    template <int RLR, int CL, int CR>
    friend Matrix<RLR,CL+CR> operator|(const Matrix<RLR,CL>& a, 
                                       const Matrix<RLR,CR>& b);   
    
    /**
     * Add the R x C Matrix a and the R x C Matrix b
     *
     * @param a   The left Matrix
     * @param b   The right Matrix
     * @return    a+b
     */
    template <int R, int C>
    friend Matrix<R,C> operator+(const Matrix<R,C>& a, const Matrix<R,C>& b);
    
    /**
     * Subtract the R x C Matrix b from the R x C matrix a (component by
     * component)
     *
     * @param a   The left Matrix
     * @param b   The right Matrix
     * @return    a-b
     */
    template <int R, int C>
    friend Matrix<R,C> operator-(const Matrix<R,C>& a, const Matrix<R,C>& b);
    
    /**
     * Multiply the RL x CLRR Matrix a and the CLRR x CR Matrix b
     * to create a RL CR Matrix
     *
     * @param a   The left Matrix
     * @param b   The left Matrix
     * @return    The resulting Matrix
     */
    template <int RL, int CLRR, int CR>
    friend Matrix<RL,CR> operator*(const Matrix<RL,CLRR>& a, 
                                   const Matrix<CLRR,CR>& b);
    
    /**
     * Multiply a scalar and an R x C Matrix
     *
     * @param k   The scalar
     * @param a   The Matrix
     * @return    The resulting Matrix
     */
    template <int R, int C>
    friend Matrix<R,C> operator*(double k, const Matrix<R,C>& a);
    
    /**
     * Multiply an R x C Matrix and a scalar
     *
     * @param a   The Matrix
     * @param k   The scalar
     * @return    The resulting Matrix
     */
    template <int R, int C>
    friend Matrix<R,C> operator*(const Matrix<R,C>& a, double k);
    
    /**
     * Compare two R x C Matrix objects to see if they have identical 
     * (within a given TOLERANCE) elements
     *
     * @param a   The left matrix
     * @param b   The right matrix
     * @return    true or false
     */
    template <int R, int C>
    friend bool operator==(const Matrix<R,C>& a, const Matrix<R,C>& b);
    
    /**
     * Compare two R x C Matrix objects to see if they have different elements
     * (beyond a given TOLERNCE)
     *
     * @param a   The left matrix
     * @param b   The right matrix
     * @return    true if any elements are different; false otherwise
     */
    template <int R, int C>
    friend bool operator!=(const Matrix<R,C>& a, const Matrix<R,C>& b);
    
    /**
     * Remove a row and column from a 2x2 matrix
     *
     * Note: This is a function template so that it is 1:1 with the class
     * (which avoid problems of duplicate definitions when linking)
     *
     * @param a   The Matrix
     * @param i   The index of the row to exclude
     * @param j   The index of the col to exclude
     * @return    The resulting scalar
     */
    template <int R, int C>
    friend double submatrix(const Matrix<2,2>& a, int i, int j);
    
    /**
     * Remove a row and column from an R x C Matrix
     *
     * @param a   The matrix
     * @param i   The index of the row to exclude
     * @param j   The index of the col to exclude
     * @throws    length_error if the Matrix is smaller than 2x2
     * @throws    out_of_range if i or j are out of bounds
     * @return    The submatrix (i.e., a with row i and column j excluded)
     */
    template <int R, int C>
    friend Matrix<R-1,C-1> submatrix(const Matrix<R,C>& a, int i, int j);
    
    /**
     * Create and return a transposed version of an R x C Matrix
     *
     * @param a   The original Matrix
     * @return    The transpose of a
     */
    template <int R, int C>
    friend Matrix<C,R> trans(const Matrix<R,C>& a);
    
};

   

// Templates


/**
 * Default Constructor
 */
template <int R, int C>
Matrix<R,C>::Matrix()
{
   allocateMemory(R, C);   
   setValues(0.0);
}


/**
 * Copy constructor
 *
 * Note: A copy constructor is critical because without on we can't
 * pass a Matrix by value (which requires that it be possible to 
 * make a copy).
 *
 * @param original  The Matrix to copy
 */
template <int R, int C>
Matrix<R,C>::Matrix(const Matrix<R,C>& original)
{
   allocateMemory(R, C);   
   setValues(original.values);
}



 /**
  * Destructor
  */
template <int R, int C>
Matrix<R,C>::~Matrix()
{
   deallocateMemory();
}


/**
 * Allocate memory for this Matrix
 *
 * @throw length error if either rows or columns is less than 0
 */
template <int R, int C>
void Matrix<R,C>::allocateMemory(int rows, int columns)
{
    // Note: This method does not use R and C so that it can be called
    // by non-templated methods and subclasses
    if(rows <= 0 || columns <= 0)
        throw std::length_error("constructor error");
    this->values  = new double*[rows];
    for (int r=0; r<rows; r++) this->values[r] = new double[columns];
}


/**
 * Calculate the cofactor of an RC x RC matrix (i.e., the signed
 * determinate of the matrix with row i and column j removed)
 *
 * @param a   The matrix
 * @param i   The index of the row to exclude
 * @param j   The index of the column to exclude
 * @throws    out_of_range if i or j are out of bounds
 * @return    The cofactor
 */
template <int RC>
double cof(const Matrix<RC,RC>& a, int i, int j)
{
    if(RC-1 < i || RC-1 < j || 0 > i || 0 > j)
        throw std::out_of_range("Out of range");

    double result = 0;

    result = matrix_minor(a, i, j);
    //return (j % 2 == 0) ? 1 : -1;
    return (j % 2 == 0) ? result : -1 * result;
}

/**
 * Deallocate the memory used by this Matrix
 */
template <int R, int C>
void Matrix<R,C>::deallocateMemory()
{
   for (int r=0; r<R; r++) delete[] this->values[r];
   delete[] this->values;
}


/**
 * Calculate the determinant of a scalar (which is useful when
 * calculating the determinant of a matrix using cofactors)
 *
 * Note: This is a function template so that it is 1:1 with the class
 * (which avoid problems of duplicate definitions when linking)
 *
 * @param a   The value of the scalar
 * @return    The determinant of a (which is just a)
 */
template <int R, int C>
double det(double a)
{
   return a;
}


/**
 * Calculate the determinant of an RC x RC matrix
 *
 * Note: This implementation is not efficient since it
 * explicitly creates each of the minors. However, it is easy to understand.
 *
 * @param a   The matrix (which must be square)
 * @throws    length_error if the Matrix is smaller than 2x2
 * @return    The value of the determinant
 */
template <int RC>
double det(const Matrix<RC,RC>& a)
{
    if(RC < 2)
        throw std::length_error("too small size of matrix");

    double result = 0;

    if(RC == 1)
    {
        result = a.values[0][0];
    }
    else if(RC == 2)
    {
        result = a.values[0][0] * a.values[1][1] - a.values[0][1] * a.values[1][0];
    }
    else
    {
        for(int r = 0; r < RC; ++r)
            result +=  cof(a, 0, r) * a.values[0][r];
    }

    //recursively find determinant of minor
    //    result += cof(a, 0, r) * a.values[0][r];
    //}

    return result;
}


/**
 * Calculate the dot product (more commonly known as the scalar product)
 * of two R x C matrices
 *
 * Note: While the steps in this calculation are the same as
 * in matrix multiplication (of a 1xn and nx1 Matrix), the result is
 * a scalar, not a Matrix. Hence, the need for this method.
 *
 * We could return (trans(a)*b).get(0,0) but this would create
 * two matrices needlessly.
 *
 * @param a  The left Matrix
 * @param b  The right Matrix
 * @return   The scalar product
 */
template<int R, int C>
double dot(const Matrix<R,C>& a, const Matrix<R,C>& b)
{
   int r,c;
   double ret = 0;
   for(r = 0; r < R; ++r)
   {
       for(c = 0; c < C; ++c)
       {
           ret += a.values[r][c] * b.values[r][c];
       }
   }

   return ret;
}


/**
 * Get a particular element of this R x C Matrix.
 *
 * @param r   The row index
 * @param c   The column index
 * @throws    out_of_range if r or c are out of bounds
 * @return    The value of the element
 */
template <int R, int C>
double Matrix<R,C>::get(int r, int c) const
{
    if(R-1 < r || C-1 < c || 0 > c || 0 > r)
        throw std::out_of_range("get(int,int): out of range");
    return this->values[r][c];
}


/**
 * Get a particular element of this Matrix if it contains
 * a single row or single column
 *
 * @param i   The index
 * @throws    out_of_range if i is out of bounds
 * @throws    length_error if this is neither a single row nor single column
 * @return    The value of the element
 */
template <int R, int C>
double Matrix<R,C>::get(int i) const
{
    if(R != 1 && C != 1)
        throw std::length_error("get(int): length error, Not a vector");
    if((R == 1 && C-1 < i) || (C == 1 && R-1 < i) || 0 < i)
        throw std::out_of_range("get(int): out of range");

    return (R == 1) ? this->values[0][i] : this->values[i][0];
}

/**
 * Get an R x 1 column of this R x C Matrix
 *
 * Note: This is not an efficient method, and it would be much better
 * to use rows rather than columns (since we are using row-major ordering).
 * However, this is more consistent with the mathematical treatment
 * in most books.
 *
 * @param c   The index of the column (0-based)
 */
template <int R, int C>
Matrix<R,1> Matrix<R,C>::getColumn(int c) const
{
    if(c > this->columns)
        throw std::out_of_range("GetColumn: out of range\n");

    Matrix<R, 1> retMatrix;
    for(int r = 0; r < R; ++r)
    {
        retMatrix(r,0) = this->values[r][0];
    }
    return retMatrix;
}


/**
 * Get the number of columns in this R x C Matrix
 *
 * @return  The number of columns (i.e., C)
 */
template <int R, int C>
int Matrix<R,C>::getColumns() const
{
   return C;   
}


/**
 * Get the number of rows in this R x C Matrix
 *
 * @return  The number of rows (i.e., R)
 */
template <int R, int C>
int Matrix<R,C>::getRows() const
{
   return R;   
}


/**
 * Create and return an RC x RC identity matrix
 *
 * Note: This function must return by value because the result Matrix
 * is a local variable.
 *
 * @return        An identity Matrix
 */
template <int RC>
Matrix<RC,RC> identity()
{
    Matrix<RC, RC> idn;
    for(int i = 0; i < RC; ++i)
    {
        idn.values[i][i] = 1.0;
    }

    return idn;
}



/**
 * Calculate the minor of an RC x RC Matrix (i.e., the determinant of
 * the submatrix formed by deleting a row and column)
 *
 * @param a   The matrix
 * @param i   The index of the row to exclude
 * @param j   The index of the column to exclude
 * @return    The minor
 */
template <int RC>
double matrix_minor(const Matrix<RC,RC>& a, int i, int j)
{
     return det(submatrix(a, i, j));
}

template <>
double matrix_minor<2>(const Matrix<2,2>& a, int i, int j)
{
    return det<2,2>(submatrix<2,2>(a, i, j));
}

 /**
  * Access an element of this R x C Matrix using the function-call operator.
  *
  * Note: This method returns by reference so that this operator
  * can be used on the left side of the assignment operator. Though this
  * can be dangerous in general (since the value being referred to
  * may not always exist), in this case it shouldn't cause any
  * problems.
  *
  * Examples of use:
  *
  *     d = y(1,1);
  *     y(2,3) = 5.0;
 *
 * @param r   The row index
 * @param c   The column index
 * @throws    out_of_range if r or c are out of bounds
 * @return    The value of the element
  */
template <int R, int C>
double& Matrix<R,C>::operator()(int r, int c)
{
    if(R-1 < r || C-1 < c || 0 > r || 0 > c)
        throw std::out_of_range("operator(): out of range");

    return this->values[r][c];
}


/**
 * Access a particular element of this R x C Matrix using the function
 * call operator if it contains a single row or single column
 *
 * @param i   The index
 * @throws    out_of_range if i is out of bounds
 * @throws    length_error if this is neither a single row nor single column
 * @return    The the element
 */
template <int R, int C>
double& Matrix<R,C>::operator()(int i)
{
    if(R != 1 && C != 1)
        throw std::length_error("operator(): length error");
    if((R == 1 && C-1 < i) || (C == 1 && R-1 < i) || 0 > i)
        throw std::out_of_range("operator(): out of range");

    return R == 1 ? this->values[0][i] : this->values[i][0];
}

/**
 * Assign an initializer_list to this R x C Matrix.
 *
 * Example of use:
 *
 *   y = {1, 2, 3,
 *        4, 5, 6,
 *        7, 8, 9};
 *
 * Note: This method is not void so that one can write x = y = {1, 2}
 * (which first assigns {1, 2} to y and then assigns the result of
 * that assignment to x).  It returns the result by reference because
 * there is no concern that this will not refer to something.
 *
 * @throws    length_error if matrix size is not match with input
 * @param m   The initializer_list containing the values
 * @return    The Matrix referred to by this
 */
template <int R, int C>
Matrix<R,C>& Matrix<R,C>::operator=(std::initializer_list<double> m)
{
    //if length of list is not matched to matrix size
    //will throw exception or static_assert for compile time error
    if(m.size() != R*C)
        throw std::length_error("operator=: size is different");
    
    const double * value = m.begin();
    this->setValues(value);
    
    return *this; 
}

/**
 * Assign another R x C Matrix to this R x C Matrix
 *
 * Note: This method is not void so that one can write x = y = z
 * (which first assigns z to y and then assigns the result of that
 * assignment to x). It returns the result by reference because there
 * is no concern that this will not refer to something.
 *
 * @param other   The Matrix to copy
 * @return        The Matrix referred to by this
 */
template <int R, int C>
Matrix<R,C>& Matrix<R,C>::operator=(const Matrix<R,C>& other)
{
    this->setValues(other);
    return *this;
}


/**
 * Concatenate the columns of the RLR x CL Matrix a and the 
 * columns of the RLR x CR Matrix b to create a
 * RLR x CL+CR Matrix
 *
 * Note: This method must return by value because the result Matrix
 * is a local variable.
 *
 * @param a   The left Matrix
 * @param b   The right Matrix
 * @return    a concatenated with b
 */
template <int RLR, int CL, int CR>
Matrix<RLR,CL+CR> operator|(const Matrix<RLR,CL>& a, 
                            const Matrix<RLR,CR>& b)
{
    Matrix<RLR, CL+CR> retMatrix;
    int acol = 0, bcol = 0;
    for(int i = 0; i < RLR; ++i)
    {
        for(int j = 0; j < CL+CR; ++j){
            if(j < CL) retMatrix.values[i][j] = a.values[i][acol++];
            else retMatrix.values[i][j] = b.values[i][bcol++];
        }
        acol = bcol = 0;
    }

    return retMatrix;
}




/**
 * Add the R x C Matrix a and the R x C Matrix b
 *
 * Note: This method must return by value because the result Matrix
 * is a local variable.
 *
 * @param a   The left Matrix
 * @param b   The right Matrix
 * @return    a+b
 */
template <int R, int C>
Matrix<R,C> operator+(const Matrix<R,C>& a, const Matrix<R,C>& b)
{
    Matrix<R,C> result;

    int r,c;
    for(r = 0; r < R; ++r)
    {
        for(c = 0; c < C; ++c)
            result.values[r][c] = a.values[r][c] + b.values[r][c];
    }

    return result;
}


/**
 * Subtract the R x C Matrix b from the R x C matrix a (component by
 * component)
 *
 * Note: This method must return by value because the result Matrix
 * is a local variable.
 *
 * @param a   The left Matrix
 * @param b   The right Matrix
 * @return    a-b
 */
template <int R, int C>
Matrix<R,C> operator-(const Matrix<R,C>& a, const Matrix<R,C>& b)
{
    Matrix<R,C> result;

    for(int r = 0; r < R; ++r)
    {
        for(int c = 0; c < C; ++c)
            result.values[r][c] = a.values[r][c] - b.values[r][c];
    }

    return result;
}

/**
 * Multiply the RL x CLRR Matrix a and the CLRR x CR Matrix b
 * to create a RL CR Matrix
 *
 * Note: This method must return by value because the result Matrix
 * is a local variable.
 *
 * @param a   The left Matrix
 * @param b   The right Matrix
 * @return    The resulting Matrix
 */
template <int RL, int CLRR, int CR>
Matrix<RL,CR> operator*(const Matrix<RL,CLRR>& a, const Matrix<CLRR,CR>& b)
{
    Matrix<RL,CR> result;
    
    double dotResult = 0.0;
    //take row of a and multiply with col of b
    for(int r = 0; r < RL; ++r)
    {
        for(int c = 0; c < CR; ++c)
        {
            for(int index = 0; index < CLRR; ++index)
                dotResult += a.values[r][index] * b.values[index][c];
            result.values[r][c] = dotResult;
            dotResult = 0.0; //reset product result for next position
        }
    }
    return result;
}


/**
 * Multiply a scalar and an R x C Matrix
 *
 * Note: This method must return by value because the result Matrix
 * is a local variable.
 *
 * @param k   The scalar
 * @param a   The Matrix
 * @return    The resulting Matrix
 */
template <int R, int C>
Matrix<R,C> operator*(double k, const Matrix<R,C>& a)
{
    Matrix<R,C> result;

    for(int r = 0; r < R; ++r)
    {
        for(int c = 0; c < C; ++c)
            result.values[r][c] = k * a.values[r][c];
    }

    return result;
}


/**
 * Multiply an R x C Matrix and a scalar
 *
 * Note: This method must return by value because the result Matrix
 * is a local variable.
 *
 * @param a   The Matrix
 * @param k   The scalar
 * @return    The resulting Matrix
 */
template <int R, int C>
Matrix<R,C> operator*(const Matrix<R,C>& a, double k)
{
   return k*a; // Use the other version
}


/**
 * Compare two R x C Matrix objects to see if they have identical 
 * (within a given TOLERANCE) elements
 *
 * @param a   The left matrix
 * @param b   The right matrix
 * @return    true or false
 */
template <int R, int C>
bool operator==(const Matrix<R,C>& a, const Matrix<R,C>& b)
{
    for(int r = 0; r < R; ++r)
    {
        for(int c = 0; c < C; ++c)
        {
            if(abs(a.values[r][c] - b.values[r][c]) > TOLERANCE)
                return false;
        }
    }
    return true;
}

/**
 * Compare two R x C Matrix objects to see if they have different elements
 * (beyond a given TOLERNCE)
 *
 * @param a   The left matrix
 * @param b   The right matrix
 * @return    true if any elements are different; false otherwise
 */
template <int R, int C>
bool operator!=(const Matrix<R,C>& a, const Matrix<R,C>& b)
{
   return !(a == b);
}


/**
 * Set the value of all elements in this Matrix to the given value
 *
 * @param value  The value to assign to every element
 */
template <int R, int C>
void Matrix<R,C>::setValues(double value)
{
   for (int r=0; r<R; r++)
   {
      for (int c=0; c<C; c++)
      {
         this->values[r][c] = value;
      }
   }
}

/**
 * Set the value of all elements in this Matrix to the value
 * of the corresponding elements in another Matrix
 *
 * @param other   The other Matrix
 */
template <int R, int C>
void Matrix<R,C>::setValues(const Matrix<R,C>& other)
{
   // Don't self-assign! (Note: this is a reference; other is an object)
   if (this != &other) setValues(other.values);
}


/**
 * Set the value of each element in this Matrix to the value of the
 * corresponding element in a row-major array
 *
 * @param values  A pointer to the row-major array
 */
template <int R, int C>
void Matrix<R,C>::setValues(const double* values)
{
   for (int r=0; r<R; r++)
   {
      for (int c=0; c<C; c++)
      {
         this->values[r][c] = values[r*C + c];
      }
   }
}
   
/**
 * Set the value of each element in this Matrix to the value of the
 * corresponding element in a "two-dimensional" array
 *
 * @param values  A pointer to the "two-dimensional" array
 */
template <int R, int C>
void Matrix<R,C>::setValues(double** values)
{
    for(int r = 0; r < R; r++)
    {
        for(int c = 0; c < C; c++)
        {
            this->values[r][c] = values[r][c];
        }
    }
}

/**
 * Remove a row and column from a 2x2 matrix
 *
 * Note: This is a function template so that it is 1:1 with the class
 * (which avoid problems of duplicate definitions when linking)
 *
 * @param a   The Matrix
 * @param i   The index of the row to exclude
 * @param j   The index of the col to exclude
 * @return    The resulting scalar
 */
template <int R, int C>
double submatrix(const Matrix<2,2>& a, int i, int j)
{
   int col, row;
   if (i == 0) row = 1;
   else        row = 0;
   
   if (j == 0) col = 1;
   else        col = 0;   

   return a.values[row][col];   
}

/**
 * Remove a row and column from an R x C Matrix
 *
 * @param a   The matrix
 * @param i   The index of the row to exclude
 * @param j   The index of the col to exclude
 * @throws    length_error if the Matrix is smaller than 2x2
 * @throws    out_of_range if i or j are out of bounds
 * @return    The submatrix (i.e., a with row i and column j excluded)
 */
template <int R, int C>
Matrix<R-1,C-1> submatrix(const Matrix<R,C>& a, int i, int j)
{  
    Matrix<R-1,C-1> result;
  
    int sr = 0, sc = 0;
    for(int r = 0; r < R; ++r)
    {
        for(int c = 0; c < C; ++c){
            if(r!=i && c!=j) {
                result.values[sr][sc++] = a.values[r][c];
            }
        }
        if(sc == C-1) 
            sr++;
        sc = 0;
    }
    
    return result;
}

 /**
 * Create and return a transposed version of an R x C Matrix
 *
 * Note: This function must return by value because the result Matrix
 * is a local variable.
 *
 * @param a   The original Matrix
 * @return    The transpose of a
 */
template <int R, int C>
Matrix<C,R> trans(const Matrix<R,C>& a)
{
    Matrix<C,R> result;

    for(int c = 0; c < C; ++c)
    {
        for(int r = 0; r < R; ++r)
        {
            result.values[c][r] = a.values[r][c];
        }
    }

    return result;
}


#endif
