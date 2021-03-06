/**
 * Rasterizer 3D header
 * 
 * Wooyoung Chung
 *
 * 3/4/14
 */

#ifndef __Rasterizer3D_H__
#define __Rasterizer3D_H__

#include "../2DRasterization/Color.h"
#include "../2DRasterization/Geometry.hpp"
#include <list>
#include "../Matrix/Matrix.hpp"
#include "../2DRasterization/Rasterizer2D.h"
#include "Triangle.h"
#define TOLERANCE  0.0001

using namespace std;


/**
 * A Rasterizer3D object rasterizes three-dimensional objects
 */
class Rasterizer3D
{
 private:
   // Add as needed
    Rasterizer2D * rast;
    double theta, phi;

    Matrix<4,4> view;

    int viewOption;

    static const int THREE_PERSPECTIVE = 4;
    static const int TWO_PERSPECTIVE = 3;
    static const int TRIVIEW = 2;
    static const int DIVIEW = 1;
    static const int ISOVIEW = 0;
    
    void setProjections(double phi, double theta);

    Matrix<4,1> applyTransform(const Matrix<4,1>& v, 
                               const Matrix<4,4>& tran);
    
 public:
    /**
     * Explicit Value Constructor
     *
     * @param fb   The FrameBuffer containing the pixels
     */
    Rasterizer3D(FrameBuffer* fb);    

    /**
     * Destructor
     */ 
    ~Rasterizer3D();
    
    /**
     * Fill the entire FrameBuffer with the given color
     *
     * @param color   The color
     */
    void clear(const Color& color);    
    
    /**
     * Draw a list of Triangle objects
     *
     * @param triangles  The Triangle objects
     */
    void draw(list<Triangle*> triangles);    

    /**
     * Instructs the rasterizer to use a dimetric view.
     * Specifically, this method updates the two rotation matrices
     * so that they are appropriate for a dimetric view.
     *
     * @param phi   The rotation around the x-axis (in radians)
     */
    void useDimetricView(double phi);

    /**
     * Instructs the rasterizer to use an isometric view.
     * Specifically, this method updates the two rotation matrices
     * so that they are appropriate for an isometric view.
     */
    void useIsometricView();

    /**
     * Instructs the rasterizer to use a three-point perspective view.
     * Specifically, this method updates the rotation 
     * and translation matrices so that they are appropriate 
     * for a three-point perspective view.
     *
     * @param d     The COP
     * @param tx    Translation along the x-axis
     * @param ty    Translation along the y-axis
     * @param tz    Translation along the z-axis
     * @param phi   Rotation around the x-axis (in radians)
     * @param theta Rotation around the y-axis (in radians)
     */
    void useThreePointPerspectiveView(double d, 
                                      double tx, double ty, double tz,
                                      double phi, double theta);

    /**
     * Instructs the rasterizer to use a trimetric view.
     * Specifically, this method updates the two rotation matrices
     * so that they are appropriate for a trimetric view.
     *
     * @param phi   Rotation around the x-axis (in radians)
     * @param theta Rotation around the y-axis (in radians)
     */
    void useTrimetricView(double phi, double theta);

    /**
     * Instructs the rasterizer to use a two-point perspective view.
     * Specifically, this method updates the rotation 
     * and translation matrices so that they are appropriate 
     * for a two-point perspective view.
     *
     * @param d     The COP
     * @param ty    Translation along the y-axis
     * @param tz    Translation along the z-axis
     * @param theta Rotation around the y-axis (in radians)
     */
    void useTwoPointPerspectiveView(double d, 
                                    double ty, double tz,
                                    double theta);
    
    
    
    
};
#endif
