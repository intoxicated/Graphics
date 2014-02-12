#ifndef edu_jmu_cs_Rasterizer2D_h
#define edu_jmu_cs_Rasterizer2D_h

#include "Color.h"
#include "FrameBuffer.h"
#include "Geometry.hpp"
#include <math.h>
#include "../pa5/Matrix.hpp"
#include "../pa5/Vector.hpp"

/**
 * An encapsulation of objects that can render various 2-D
 * shapes.
 *
 * Note: Since we don't need to transform points, they are 
 * in Cartesian (rather than homogeneous) coordinates and stored in
 * a Matrix<2,1> (i.e., a 2-element column vector which is the same as
 * a Vector<2>). 
 */
class Rasterizer2D
{
  public:
   static const int SCAN_LINE = 0;
   static const int POINTWISE = 1;

  /**
   * Explicit Value Constructor
   *
   * @param fb  A pointer to the FrameBuffer to use
   */
   Rasterizer2D(FrameBuffer* fb);   

  /**
   * Fill the entire FrameBuffer with the given color
   *
   */
   void clear(const Color& color);

  /**
   * Draw a line using the (non-incremental) parametric approach
   *
   * @param p     One end point
   * @param q     The other end point
   * @param color The color to use
   */
   void drawLine(const Matrix<2,1>& p, const Matrix<2,1>& q,
                 const Color& color);

  /**
   * Set the color of a single pixel
   *
   * @param x      The horizontal coordinate
   * @param y      The vertical coordinate
   * @param color  The Color to use
   */
   void drawPoint(int x, int y, const Color& color);
   
  /**
   * Set the color of a single pixel
   *
   * @param x      The horizontal coordinate
   * @param y      The vertical coordinate
   * @param color  The Color to use
   */
   void drawPoint(Matrix<2,1>& point, const Color& color);

  /**
   * Draw the edges of a quadrilateral
   *     
   * @param quad  The vertices of the quadrilateral
   * @param color The color to use
   */
   void drawQuadrilateral(const Matrix<2,4>& quad,
                          const Color& color);

  /**
   * Draw the edges of a triangle
   *     
   * @param triangle  The vertices of the triangle
   * @param color     The color to use
   */
   void drawTriangle(const Matrix<2,3>& triangle,
                     const Color& color);   

  /**
   * Fill a quadrilateral (by calling a method that implements
   * a specific fill algorithm). This is a convenience method
   * for users that are indifferent to the algorithm used.
   *
   * @param quad    The vertices of the quadrilateral
   * @param color   The color to use
   */
   void fillQuadrilateral(const Matrix<2,4>& quad,
                          const Color& color);

  /**
   * Fill a triangle  (by calling a method that implements
   * a specific fill algorithm). This is a convenience method
   * for users that are indifferent to the algorithm used.
   *
   * @param triangle The vertices of the triangle
   * @param color    The color to use
   */
   void fillTriangle(const Matrix<2,3>& triangle,const Color& color);
   
  /**
   * Fill a quadrilateral by testing all of the points
   * in its bounding rectangle using the halfspace test
   *
   * @param quad    The vertices of the quadrilateral
   * @param color   The color to use
   */
   void pointwiseFillQuadrilateral(const Matrix<2,4>& quad,
                                   const Color& color);

  /**
   * Fill a triangle point-by-point in the given color  using
   * the signed-area algorithm
   *
   * @param triangle The vertices of the triangle
   * @param color The color to use
   */
   void pointwiseFillTriangle(const Matrix<2,3>& triangle, const Color& color);
   

  private:
   FrameBuffer*   fb;
   int            fillTechnique;
   
   
};

#endif
