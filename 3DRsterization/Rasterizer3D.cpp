/**
 * Rasterizer 3D Implementation
 * 
 * Wooyoung Chung
 *
 * 3/4/14
 */

#include "Rasterizer3D.h"
#include <cmath>

#define PI 3.14159265358979323846

Rasterizer3D::Rasterizer3D(FrameBuffer * fb)
{
    this->view = {1,0,0,0,
                  0,1,0,0,
                  0,0,1,0,
                  0,0,0,1};

    this->rast = new Rasterizer2D(fb);
}

Rasterizer3D::~Rasterizer3D()
{
    delete this->rast;
}

void
Rasterizer3D::clear(const Color& color)
{
    this->rast->clear(color);
}

/**
 * apply transformation to a given vector
 *
 * @param v vector
 * @param tran transform matrix 
 *
 * @return transformed vector 
 */
Matrix<4,1>
Rasterizer3D::applyTransform(const Matrix<4,1>& v, const Matrix<4,4>& tran)
{
    Matrix<4,1> ret;
    ret = tran * v;
    return ret;
}

void
Rasterizer3D::draw(list<Triangle*> triangles)
{
    //iterate list
    std::list<Triangle*>::iterator it;

    Matrix<4,3> trans, applyMatrix;
    Matrix<4,1> a,b,c;

    Matrix<2,4> pre;
    pre = {1,0,0,0,
           0,1,0,0};

    Color WHITE = {255,255,255};
    for(it = triangles.begin(); it != triangles.end(); ++it)
    {
        //apply transform to each vertex
        a = applyTransform((*it)->vertices.getColumn(0), this->view);
        b = applyTransform((*it)->vertices.getColumn(1), this->view);
        c = applyTransform((*it)->vertices.getColumn(2), this->view);
        //conat vetices back 
        applyMatrix = a|b|c; 
       
        //take off x,y from transformed triangle
        Matrix<2,3> tri = pre * applyMatrix;

        //draw it on 2d
        this->rast->drawTriangle(tri, (*it)->frontColor);
        //this->rast.drawTriangle(tri,(*it)->backColor);
    }
}

/**
 * calculate transform view of trimetric and dimetric
 *
 * @param phi phi angle in radians
 * @param theta theta angle in radians
 */
void
Rasterizer3D::setProjections(double phi, double theta)
{
    Matrix<4,4> rx, ry;
    
    rx = {1,        0,         0, 0,
          0, cos(phi), -sin(phi), 0,
          0, sin(phi),  cos(phi), 0,
          0,        0,         0, 1};

    ry = {cos(theta),0,sin(theta),0,
                   0,1,         0,0,
         -sin(theta),0,cos(theta),0,
                   0,0,         0,1};
    
    this->view = rx * ry;  
}

void
Rasterizer3D::useDimetricView(double phi)
{
    this->viewOption = DIVIEW;
    this->theta = asin( pow(sin(phi),2) / 
            (1 - pow(sin(phi),2)) );
    this->phi = phi;

    this->setProjections(this->phi, this->theta);
}

void
Rasterizer3D::useIsometricView()
{
    this->viewOption = ISOVIEW;
    this->theta = asin(sqrt(0.5));
    this->phi = asin(sqrt(1.0/3.0));

    this->setProjections(this->phi, this->theta);
}

void
Rasterizer3D::useThreePointPerspectiveView(double d,
	double tx, double ty, double tz,
	double phi, double theta)
{
    this->viewOption = THREE_PERSPECTIVE;
    Matrix<4,4> p, rx, ry, t;
    
    p = {1,0,  0,0,
         0,1,  0,0,
         0,0,  0,0,
         0,0,1/d,1};
    
    rx = {1,        0,         0, 0,
          0, cos(phi), -sin(phi), 0,
          0, sin(phi),  cos(phi), 0,
          0,        0,         0, 1};

    ry = {cos(theta),0,sin(theta),0,
                   0,1,         0,0,
         -sin(theta),0,cos(theta),0,
                   0,0,         0,1};
    
    t = {1,0,0,tx,
         0,1,0,ty,
         0,0,1,tz,
         0,0,0, 1};

    this->view = p * t * rx * ry;
}

void
Rasterizer3D::useTrimetricView(double phi, double theta)
{
    this->viewOption = TRIVIEW;
    this->theta = theta;
    this->phi = phi;

    this->setProjections(this->phi, this->theta);
}

void
Rasterizer3D::useTwoPointPerspectiveView(double d,
	double ty, double tz,
	double theta)
{
   this->viewOption = TWO_PERSPECTIVE;
   this->view = {cos(theta), 0,     sin(theta),        0,
                          0, 1,              0,       ty,
                          0, 0,              0,        0,
              -sin(theta)/d, 0,   cos(theta)/d, tz/d + 1 };
}
