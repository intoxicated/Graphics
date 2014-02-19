/**
 * Geometry template 
 *
 * author: Wooyoung Chung
 *
 * 2/14/14
 */

#ifndef __GEOMETRY_HPP__
#define __GEOMETRY_HPP__


#include <cmath>
#include "../Matrix/Matrix.hpp"
#include "../Matrix/Vector.hpp"

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

template <int N>
bool signedArea(const Matrix<2,1>& p, const Matrix<2,1>& r, 
    const Matrix<2,1>& s);

template <int N>
int testHalfspace(const Matrix<2,1>& p, const Matrix<2,1>& r,
       const Matrix<2,1>& a, const Matrix<2,1>& b);

template <int N>
int testHalfspace(const Matrix<2,1>& p, const Matrix<2,1>& n, double b);

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
    Vector<2> na, nb, nc;
    na = { 0, 0 };
    nb = b - a;
    nc = c - a;

    Matrix<2,2> aa, bb, cc;
    aa = na | nb ;
    bb = nb | nc ;
    cc = nc | na ;

    double retVal = 0.5 * (det(aa) + det(bb) + det(cc));
    
    return retVal;
}


/**
 * Returns the point alpha q + (1-alpha)
 *
 * @param q      One point
 * @param r      The other points
 * @param alpha  The weight
 */
template <int N>
Vector<N> barycentricCombination(const Matrix<N,1>& q, const Matrix<N,1>& r, double alpha)
{
    Vector<N> ret;
    ret = (alpha *q) + ((1-alpha)*r);
    return ret;
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
    Vector<R> minVal;
    Vector<R> maxVal;

    //initially set to first vector for max and min
    for(int i = 0; i < R; ++i)
    {
        minVal(i) = p.get(i,0);
        maxVal(i) = p.get(i,0);
    }

    for(int i = 1; i < C; ++i)
    {
        for(int j = 0; j < R; ++j)
        {
            if(minVal(j) > p.get(j,i)) 
                minVal(j) = p.get(j,i);
            if(maxVal(j) < p.get(j,i))
                maxVal(j) = p.get(j,i);
        }
    }
    
    return minVal | maxVal;
}


/**
 * calculate signed area of triangle with given three vectors
 *
 * @return true if signed area is positive, otherwise false
 */
template <int N>
bool signedArea(const Matrix<2,1>& p, const Matrix<2,1>& r,
            const Matrix<2,1>& s)
{
   Matrix<2,2> rs;
   rs = (s-r) | (p-r);
   return (det(rs) > 0.0f) ? true : false;
}

/** 
 * test if given two vectors are same side of line 
 *
 * @param p one vector
 * @param r other vector
 * @param a one point of line
 * @param b the other point of line
 * @return 1 if p and r is same side, -1 otherwise.
 */
template <int N>
int testHalfspace(const Matrix<2,1>& p, const Matrix<2,1>& r, 
        const Matrix<2,1>& a, const Matrix<2,1>& b)
{
    Matrix<2,1> n,m;
    double scalarB;

    scalarB = toImplicit<2>(a,b, &n);
    int retA = (dot(n,p) + scalarB >= 0) ? 1 : -1;
    int retB = (dot(n,r) + scalarB >= 0) ? 1 : -1;
    return (retA == retB) ? 1 : -1;
}

/**
 *  test halfspace of given point p with implicit form of line r.p = b
 *  
 *  @param p testing vector
 *  @param n vector parameter of homogeneous form
 *  @param b scalar paramter of homogeneous form 
 *  @return signed of half space of point 
 */
template <int N>
int testHalfspace(const Matrix<2,1>& p, const Matrix<2,1>& n, double b)
{
    return (dot(n,p) + b >= 0) ? 1 : -1;
}

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
    int sign1 = signedArea<2>(p,r,s);
    int sign2 = signedArea<2>(p,s,t);
    int sign3 = signedArea<2>(p,t,r);
    
    return ((sign1 == sign2) && (sign2 == sign3)) ? true : false;
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
    Vector<2> n,t, pq, rs;
    double ai, bi;

    ai = toImplicit<2>(p, q, &n);
    bi = toImplicit<2>(r, s, &t);

    //if they are intersected, calculate intersection point
    if( n != t )
    {
       //change to parametric form
       pq = q - p, rs = s - r;
       
       alpha = dot((r - p), perp<2>(rs)) / dot(pq, perp<2>(rs));
       beta = dot((p - r), perp<2>(pq)) / dot(rs, perp<2>(pq));
    }
    return (n != t) ? true : false;
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
    Vector<2> ret;
    ret = {-a.get(1,0), a.get(0,0)};
    return ret;
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
    double ret;
    
    *n = perp<2>(p - q);
    ret = -(dot(*n, p));
    return ret;
}

#endif
