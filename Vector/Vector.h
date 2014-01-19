/**
 * Vector header
 *
 * Purpose: Vector class allows an application to perform
 *          vector arithmatic in a simple manner.
 *
 * Author: Wooyoung Chung
 *
 * Date: Jan 13th, 2014
 *
 */

#ifndef __CS_ASSN1__Vector__
#define __CS_ASSN1__Vector__

#include <cmath>
#include <initializer_list>
#include <math.h>
#include <stdexcept>

using namespace std;

/**
 * The Vector class is an encapsulation of both n-dimensional
 * points and n-dimensional direction vectors.
 */
class Vector
{
protected:
    char       orientation;
    double*    values;
    int        size;
    
    void allocateMemory();
    void deallocateMemory();
    void setSize(int size, char orientation);
    void setValues(double value);
    void setValues(const double* values);
    
public:
    
    /**
     * Construct a column vector of given size
     *
     * Example of use:
     *
     *   Vector y(3);
     *
     * @param size   The size of the Vector
     */
    Vector(int size);
    
    /**
     * Construct a column or row vector of given size
     *
     * Example of use:
     *
     *   Vector y(3, Vector::ROW);
     *
     * @param size        The size of the Vector
     * @param orientation The orientation (either COLUMN or ROW)
     */
    Vector(int size, char orientation);
    
    /**
     * A copy constructor
     *
     * Note: Without a copy constructor one we can't pass a Vector by
     * value (since when one passes by value a copy is made)
     *
     * @param original  The Vector to copy
     */
    Vector(const Vector& original);
    
    /**
     * Destructor
     */
    ~Vector();
    
    /**
     * Get a particular element of this Vector
     *
     * @param i   The index of the element
     * @return    The value of the element at the given index
     */
    double get(int i) const;
    
    /**
     * Get the orientation of this Vector
     *
     * @return    The orientation (Vector::COLUMN or Vector::ROW)
     */
    char getOrientation() const;
    
    /**
     * Get the size of this Vector
     *
     * @return The number of elements in this Vector
     */
    int getSize() const;
    
    /**
     * Calculate the Euclidean norm of a Vector
     *
	 * @param a   The Vector
	 * @return    ||a||
	 */
	friend double norm(const Vector& a);

	/**
	 * Calculate the normalized version of a Vector
	 *
	 * @param a   The Vector
	 * @return    a / ||a||
	 */
	friend Vector normalized(const Vector& a);

	/**
	 * Access an element of this Vector using the function-call operator.
	 *
	 * Note: This method returns by reference so that this operator
	 * can be used on the left side of the assignment operator. Though this
	 * can be dangerous in general (since the value being referred to
	 * may not always exist), in this case it shouldn't cause any
	 * problems.
	 *
	 * Examples of use:
	 *
	 *     d = y(1);
	 *     y(2) = 5.0;
	 *
	 * @param i   The index of the element
	 * @throws    out_of_range exception if i is out of range
	 * @return    The value of the element at the given index
	 */
	double& operator()(int i);

	/**
	 * Assign an initializer_list to this Vector.
	 *
	 * Examples of use:
	 *
	 *   y = {1,
	 *        2,
	 *        3};
	 *
	 *   x = {4, 5, 6, 7, 8, 9};
	 *
	 * Note: This method is not void so that one can write x = y = {1,2}
	 * (which first assigns {1,2} to y and then assigns the result of
	 * that assignment to x).  It returns the result by reference because
	 * there is no chance that this will not refer to something.
	 *
	 * @param v   The initializer_list containing the values
	 */
	Vector& operator=(std::initializer_list<double> values);

	/**
	 * Assign another Vector to this Vector.
	 *
	 * The two Vectors must have the same size and orientation.
	 *
	 * Note: This method is not void so that one can write x = y = z
	 * (which first assigns z to y and then assigns the result of that
	 * assignment to x). It returns the result by reference because there
	 * is no concern that this will not refer to something.
	 *
	 * @param other   The right-side Vector
	 * @throws        length_error if the sizes or orientations don't match
	 * @return        The Vector referred to by this
	 */
	Vector& operator=(const Vector& other);

	/**
	 * Add the Vector a and the Vector b (component by component)
	 *
	 * Note: This method must return by value because the result Vector
	 * is a local variable.
	 *
	 * @param a  One Vector
	 * @param b  The other Vector
	 * @throws   length_error exception if the sizes or orientations don't match
	 * @return   The Vector a+b
	 */
	friend Vector operator+(const Vector& a, const Vector& b);

	/**
	 * Subtract the Vector b from the Vector a (component by component)
	 *
	 * The two Vectors must have the same size and orientation.
	 *
	 * Note: This method must return by value because the result Vector
	 * is a local variable.
	 *
	 * @param a  One Vector
	 * @param b  The other Vector
	 * @throws   length_error if the sizes or orientations don't match
	 * @return   The Vector a-b
	 */
	friend Vector operator-(const Vector& a, const Vector& b);

	/**
	 * Multiply two Vectors (i.e., find the dot/inner product)
	 *
	 * The two Vectors must have the same size and same orientation
	 *
	 * Note: This method must return by value because the result Vector
	 * is a local variable.
	 *
	 * @param a   The first Vector (a row Vector)
	 * @param b   The second Vector (a column Vector)
	 * @throws    length_error if the sizes or orientations don't match
	 * @return    The resulting scalar
	 */
	friend double operator*(const Vector& a, const Vector& b);


	/**
	 * Multiply a scalar and a Vector
	 *
	 * Note: This method must return by value because the result Vector
	 * is a local variable.
	 *
	 * @param k   The scalar
	 * @param a   The Vector
	 * @return    The resulting Vector
	 */
	friend Vector operator*(double k, const Vector& a);

	/**
	 * Multiply a Vector and a scalar
	 *
	 * Note: This method must return by value because the result Vector
	 * is a local variable.
	 *
	 * @param a   The Vector
	 * @param k   The scalar
	 * @return    The resulting Vector
	 */
	friend Vector operator*(const Vector& a, double k);

	/**
	 * Compare two Vectors to see if they have identical (within a
	 * pre-defined TOLERANCE) elements
	 *
	 * The two Vectors must have the same size and same orientation
	 *
	 * @param a   The first Vector
	 * @param b   The second Vector
	 * @return    true or false
	 */
	friend bool operator==(const Vector& a, const Vector& b);
    
    /**
     * Compare two Vectors to see if they have different (beyond a given
     * TOLERANCE) elements
     *
     * The two Vectors must have the same size and same orientation
     *
     * @param a   The first Vector
     * @param b   The second Vector
     * @return    true or false
     */
    friend bool operator!=(const Vector& a, const Vector& b);
    
    /**
     * Create and return a transposed version of a given Vector
     *
     * Note: This function must return by value because the result Vector
     * is a local variable.
     *
     * @param a   The original Vector
     * @return    The transposed Vector
     */
    friend Vector trans(const Vector& a);
    
    //debug purpose return double array values
    double * get_content() const;
    
    // Public Constants
    const static char        COLUMN = 0;
    const static char        ROW    = 1;
};

double norm(const Vector& a);
Vector normalized(const Vector& a);
Vector operator+(const Vector& a, const Vector& b);
Vector operator-(const Vector& a, const Vector& b);
double operator*(const Vector& a, const Vector& b);
Vector operator*(double k, const Vector& a);
Vector operator*(const Vector& a, double k);
bool   operator==(const Vector& a, const Vector& b);
bool   operator!=(const Vector& a, const Vector& b);
Vector trans(const Vector& a);


#endif /* defined(__CS_ASSN1__Vector__) */
