#ifndef edu_jmu_cs_Geometry_hpp
#define edu_jmu_cs_Geometry_hpp



#include <cmath>
#include "../pa5/Matrix.hpp"
#include "../pa5/Vector.hpp"

/**
 * A utility class (actually template) that can perform various
 * calculations required by 2-D and 3-D rasterizers.
 *
 * Note: Since we don't need to transform 2D points, they are in
 * Cartesian (rather than homogeneous) coordinates and stored in a
 * Matrix<2,1> (i.e., a 2-element column vector which is the same as a
 * Vector<2>). This also makes it a little easier to calculate the
 * area and determine whether a point is inside of a triangle.
 */



// Note: area(), inside(), and toImplicit() are templated so that they are
// one-to-one with Matrix

template <int N>
double area(const Matrix<2,1>& a, const Matrix<2,1>& b, const Matrix<2,1>& c);

template <int N>
Vector<N> barycentricCombination(const Matrix<N,1>& q, 
                                 const Matrix<N,1>& r, 
                                 double alpha);

template <int R, int C>
Matrix<R,2> getBounds(const Matrix<R,C>& p);

template <int N>
bool inside(const Matrix<2,1>& p, 
            const Matrix<2,1>& r, const Matrix<2,1>& s, const Matrix<2,1>& t);

template <int N>
bool intersect(const Matrix<2,1>& p, const Matrix<2,1>& q,
               const Matrix<2,1>& r, const Matrix<2,1>& s,
               double& alpha, double& beta);

template <int N>
Vector<2> perp(const Matrix<2,1>& a);

template <int N>
double toImplicit(const Matrix<2,1>& p, const Matrix<2,1>& q, Matrix<2,1>* n);



/**
 * Compute the area of a triangle from its three vertices
 *
 * The vertices can be (i.e., are) assumed to be ordered correctly
 * (i.e., obey the right-hand rule)
 *
 * Note: This is a function template to avoid problems of duplicate 
 * definitions when linking
 * 
 * @param a  The first vertex
 * @param b  The second vertex
 * @param c  The third vertex
 */
template <int N>
double area(const Matrix<2,1>& a, const Matrix<2,1>& b, const Matrix<2,1>& c)
{
}


/**
 * Returns the point alpha q + (1-alpha)r
 *
 * @param q      One point
 * @param r      The other points
 * @param alpha  The weight
 */
template <int N>
Vector<N> barycentricCombination(const Matrix<N,1>& q, const Matrix<N,1>& r, double alpha)
{
}


/**
 * Returns the bounds of the given line, triangle, or polygon.
 *
 * This method returns a matrix with two columns.  Column 0 contains the
 * minimums value and column 1 contains the maximum values.
 * (The rows correspond to the rows of the points.)
 *
 * @param p  The line, triangle, or polygon
 * @return   The bounding rectangle (as described above)
 */
template <int R, int C>
Matrix<R,2> getBounds(const Matrix<R,C>& p)
{
}


//2D
/**
 * Determine whether the point p is inside the triangle
 * formed by the vertices r, s, t
 *
 * Note: This is a function template to avoid problems of 
 * duplicate definitions when linking
 *
 * @param p   The test point
 * @param r   The first vertex of the triangle
 * @param s   The second vertex of the triangle
 * @param t   The third vertex of the triangle
 */
template <int N>
bool inside(const Matrix<2,1>& p, 
            const Matrix<2,1>& r, const Matrix<2,1>& s, const Matrix<2,1>& t)
{
}


    
/**
 * Find the intersection of two lines (NOT line segments)
 *
 * This method returns false if the lines are parallel
 * and true if the lines intersect.
 *
 * If the lines intersect it calculates the (convex combination) weights 
 * that define the intersection point.  Letting
 * alpha denote the weight for line 0 and 
 * beta denote the weight for line 1, the intersection
 * point is given by:
 *
 *    x: alpha*p[0] + (1-alpha)*q[0]
 *    y: alpha*p[1] + (1-alpha)*q[1]
 *
 * and or:
 *
 *    x: beta*r[0] + (1-beta)*s[0]
 *    y: beta*r[1] + (1-beta)*s[1]
 *
 * If alpha is in [0, 1] then the intersection point is
 * within the line segment from p to q.  Similarly, 
 * if beta is in [0, 1] then the intersection point is 
 * within the line segment from r to s.
 *
 * @param p     One endpoint of the line from p to q
 * @param q     The other endpoint of the line from p to q
 * @param r     One endpoint of the line from r to s
 * @param s     The other endpoint of  the line from r to s
 * @param alpha One of the weights (outbound)
 * @param beta  The other weight (outbound)
 * @return      true if the lines intersect; false otherwise
 */
template <int N>
bool intersect(const Matrix<2,1>& p, const Matrix<2,1>& q,
               const Matrix<2,1>& r, const Matrix<2,1>& s,
               double& alpha, double& beta)
{
}


/**
 * Find a perpendicular to the given 2-vector
 *
 * @param a   The 2-vector (which is a Mtrix<2,1> to increase flexibility)
 * @return    The perpendicular (i.e., [-a[1], a[0]])
 */
template <int N>
Vector<2> perp(const Matrix<2,1>& a)
{
}


/**
 * Compute the implicit form of a line defined by two points
 *
 * The implicit form is the set of points r that satify
 * by n.r = b
 *
 * n is passed into this method empty and is filled. b is
 * returned.
 *
 * Note: This is a function template to avoid problems of duplicate
 * definitions when linking
 *
 * @param p  One endpoint
 * @param q  The other endpoint
 * @param n  The vector parameter of the homogenous form (returned)
 * @return   The scalar parameter of the homogenous form
 */
template <int N>
double toImplicit(const Matrix<2,1>& p, const Matrix<2,1>& q, Matrix<2,1>* n)
{
}

#endif
