/**
 * 2D Rasterization implementation 
 *
 * Author: Wooyoung Chung
 *
 * 2/14/14
 */

#include "Rasterizer2D.h"


Rasterizer2D::Rasterizer2D(FrameBuffer *fb)
{
    this->fb = fb;
}

void 
Rasterizer2D::clear(const Color& color)
{
    this->fb->clear(color);
}

void 
Rasterizer2D::drawLine(const Matrix<2,1>& p, const Matrix<2,1>& q,
                            const Color& color)
{
    double x,y;
    int xEnd, xStart, yEnd, yStart;
    double alpha, slope;
    //find slope here
    if(q.get(0,0) == p.get(0,0))
        slope = INFINITY;
    else
        slope = (q.get(1,0)-p.get(1,0))/(q.get(0,0) - p.get(0,0));
    
    if((slope >= -1.0) && (slope <= 1.0))
        goto STDSLOPE;
    else
        goto OTHERSLOPE;

STDSLOPE:
    if(p.get(0,0) <= q.get(0,0))
    {
        xStart = round(p.get(0,0));
        xEnd = round(q.get(0,0));
    }
    else
    {
        xStart = round(q.get(0,0));
        xEnd = round(p.get(0,0));
    }

    for (int i = xStart; i <= xEnd; i++)
    {
        if(q.get(0,0) == p.get(0,0))
        {
            y = p.get(1,0);
        }
        else
        {
            alpha = (i - p.get(0,0)) / (q.get(0,0) - p.get(0,0));
            y = p.get(1,0) + alpha * (q.get(1,0) - p.get(1,0));
        }
        
        fb->setPixel(i, round(y), color);
    }
    return;

OTHERSLOPE:
    if(p.get(1,0) <= q.get(1,0))
    {
        yStart = round(p.get(1,0));
        yEnd = round(q.get(1,0));
    }
    else
    {
        yStart = round(q.get(1,0));
        yEnd = round(p.get(1,0));
    }

    for (int i = yStart; i <= yEnd; i++)
    {
        if(q.get(1,0) == p.get(1,0))
        {
            x = p.get(0,0);
        }
        else
        {
            alpha = (i - p.get(1,0)) / (q.get(1,0) - p.get(1,0));
            x = p.get(0,0) + alpha * (q.get(0,0) - p.get(0,0));
        }
        
        fb->setPixel(round(x), i, color);
    }
}

void
Rasterizer2D::drawPoint(int x, int y, const Color& color)
{
    fb->setPixel(x, y, color);
}

void
Rasterizer2D::drawPoint(Matrix<2,1>& point, const Color& color)
{
    fb->setPixel(round(point.get(0,0)), round(point.get(1,0)), color);
}

void
Rasterizer2D::drawQuadrilateral(const Matrix<2,4>& quad,
                                const Color& color)
{
    for(int i = 0; i < 4; i++)
        drawLine(quad.getColumn(i%4), quad.getColumn((i+1)%4), color);
}

void
Rasterizer2D::drawTriangle(const Matrix<2,3> &triangle,
                           const Color& color)
{
    for(int i = 0; i < 3; i++)
        drawLine(triangle.getColumn(i%3), triangle.getColumn((i+1)%3), color);
}

void
Rasterizer2D::fillQuadrilateral(const Matrix<2,4>& quad,
                                const Color& color)
{
    pointwiseFillQuadrilateral(quad, color);
}

void
Rasterizer2D::fillTriangle(const Matrix<2,3>& triangle, 
                           const Color& color)
{
    pointwiseFillTriangle(triangle, color);
}

void
Rasterizer2D::pointwiseFillQuadrilateral(const Matrix<2,4>& quad,
                                         const Color& color)
{
    //find bounding rect
    Matrix<2,2> bound;
    bound = getBounds(quad);

    Vector<2> origin, testPoint;
    origin = {0,0};

    Vector<2> implicit[4];
    double bs[4];
    double sign[4];

    //pre-calculate implicit form of each eadge
    for(int i = 0; i < 4; ++i)
         bs[i] = toImplicit<2>(quad.getColumn(i%4), quad.getColumn((i+1)%4), &implicit[i]);

    //store halfspace test result of next vertex
    for(int i = 0; i < 4; ++i)
        sign[i] = testHalfspace<2>(quad.getColumn((i+2)%4), implicit[i], bs[i]);

    for(int y = bound(1,0); y <= bound(1,1); y++)
    {
        for(int x = bound(0,0); x <= bound(0,1); x++)
        {
            testPoint = {x,y};
            
            if((testHalfspace<2>(testPoint, implicit[0], bs[0]) == sign[0]) &&
                    (testHalfspace<2>(testPoint, implicit[1], bs[1]) == sign[1]) &&
                    (testHalfspace<2>(testPoint, implicit[2], bs[2]) == sign[2]) &&
                    (testHalfspace<2>(testPoint, implicit[3], bs[3]) == sign[3]))
            {   
                fb->setPixel(x,y, color); 
            }
        }

    }
}

void
Rasterizer2D::pointwiseFillTriangle(const Matrix<2,3>& triangle,
                                    const Color& color)
{
    Matrix<2,2> bound;
    bound = getBounds(triangle);
    Vector<2> testPoint;
    int xstart,xend;

    for(int y = bound(1,0); y <= bound(1,1); y++)
    {
        /*
        for(int x = bound(0,0); x < bound(0,1); x++)
        {
            testPoint = {x,y};
            if(inside<2>(testPoint, triangle.getColumn(0), triangle.getColumn(1), triangle.getColumn(2)))
            {
                xstart = x;
                break;
                //fb->setPixel(x,y, color);
            }
        }

        for (int x = bound(0,1); x > xstart; x--)
        {
            testPoint = {x,y};
            if(inside<2>(testPoint, triangle.getColumn(0), triangle.getColumn(1), triangle.getColumn(2)))
            {
                xend = x;
                break;
                //fb->setPixel(x,y, color);
            }
        }

        for (int x = xstart; x < xend; x++)
        {
            fb->setPixel(x,y,color);
        }
        */
        for(int x = bound(0,0); x <= bound(0,1); x++)
        {
            testPoint = {x,y};
            if(inside<2>(testPoint, triangle.getColumn(0), triangle.getColumn(1), triangle.getColumn(2)))
            {
                fb->setPixel(x,y, color);
            }
        }
    }
}

