/**
 * Vector template
 *
 * Author: Wooyoung Chung
 *
 * Last Modified: 1/24/14
 *
 */


#ifndef __cs_vector_hpp__
#define __cs_vector_hpp__

#include "Matrix.hpp"

// Prototype of the Vector class
// (so that it can be used in the friend prototypes)
template<int ROWS> class Vector;

// Prototypes of friend functions 
template<int R>
double norm(const Matrix<R,1>& a);

template<int R>
Matrix<R,1> normalized(const Matrix<R,1>& a);

//  Class declaration
//
// Note: All friend functions are one-to-one with the class. For example,
// there is a norm<1> that corresponds to Vector<1>, ...
//
// The parameters ROWS corresponds to the number of rows in all of the
// methods/functions that have sizes in common
template<int ROWS>
class Vector: public Matrix<ROWS,1>
{
  public:
    /**
     * Construct a column vector with ROWS rows
     */
    Vector<ROWS>();

    /**
     * Copy a Vector of size ROWS
     *
     * @param original  The Vector to copy
     */
    Vector<ROWS>(const Vector<ROWS>& original);   

    /**
     * Calculate the Euclidean norm of a Vector of size R
     *
     * @param a   The Vector
     * @return    ||a||
     */
    template<int R>
    friend double norm(const Matrix<R,1>& a);
    
    /**
     * Calculate the normalized version of a Vector of size R
     *
     * @param a   The Vector
     * @return    a / ||a||
     */
    template<int R>
    friend Matrix<R,1> normalized(const Matrix<R,1>& a);
    
    /**
     * Assign an initializer_list to this Vector of size R
     *
     * @param m   The initializer_list containing the values
     * @return    The Vector referred to by this
     */
    Vector<ROWS>& operator=(std::initializer_list<double> m);
    
    /**
     * Assign another Vector of size R to this Vector of size R
     *
     * @param other   The Vector to copy
     * @return        The Vector referred to by this
     */
    Vector<ROWS>& operator=(const Matrix<ROWS,1>& other);
};



// Templates

/**
 *
 * Note: One could avoid the use of get() in norm(), dot(), etc...  if
 * these were methods and not functions (because the methods would
 * have access to the protected variables). However, it is more
 * intuitive for norm(), dot(), etc... to be functions.
 */

#include<iostream>

/**
 * Construct a column vector with R rows
 */
template<int R>
Vector<R>::Vector()
{
   this->allocateMemory(R, 1);
   this->setValues(0.0);
}


/**
 * Copy a Vector of size R
 *
 * @param original  The Vector to copy
 */
template<int R>
Vector<R>::Vector(const Vector<R>& original)
{
   this->allocateMemory(R, 1);   
   this->setValues(original);
}



/**
 * Calculate the Euclidean norm of a Vector of size R
 *
 * @param a   The Vector
 * @return    ||a||
 */
template<int R>
double norm(const Matrix<R,1>& a)
{
    double ret = 0.0;

    for(int i = 0; i < R; ++i)
        ret += pow(a.get(i,0), 2);
    return sqrt(ret);
}


/**
 * Calculate the normalized version of a Vector of size R
 *
 * @param a   The Vector
 * @return    a / ||a||
 */
template<int R>
Matrix<R,1> normalized(const Matrix<R,1>& a)
{
    Matrix<R,1> ret;
    double normval = norm(a);
    for(int i = 0; i < R; ++i)
        ret(i,0) = a.get(i,0) / normval;
    return ret;
}


/**
 * Assign an initializer_list to this Vector of size R
 *
 * @throws    length error if vector size is not match 
 * @param m   The initializer_list containing the values
 * @return    The Vector referred to by this
 */
template<int R>
Vector<R>& Vector<R>::operator=(std::initializer_list<double> m)
{
   if(m.size() != R)
       throw std::length_error("operator=: size is different");

   const double*    values;
   
   values = m.begin();   // Returns a pointer to the first element
   this->setValues(values);
   
   // Note: The result is the object referred to by this (which is returned
   // by reference). So, we must reference this.
   return *this;
}


/**
 * Assign another Vector of size R to this Vector of size R
 *
 * Note: This method is not void so that one can write x = y = z
 * (which first assigns z to y and then assigns the result of that
 * assignment to x). It returns the result by reference because there
 * is no concern that this will not refer to something.
 *
 * @param other   The Vector to copy
 * @return        The Vector referred to by this
 */
template<int R>
Vector<R>& Vector<R>::operator=(const Matrix<R,1>& other)
{
   this->setValues(other);

   // Note: The result is the object referred to by this (which is returned
   // by reference). So, we must reference this.
   return *this;
}

#endif
