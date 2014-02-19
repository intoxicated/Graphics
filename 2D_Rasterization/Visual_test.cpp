#include "Rasterizer2D.h"
#include "Color.h"
#include "FrameBuffer.h"
#include "GraphicsWindow.h"
#include "../Matrix/Matrix.hpp"
#include "../Matrix/Vector.hpp"

Color YELLOW = { 255,255,0 };
Color WHITE = { 255, 255, 255};
Color BLACK = { 0, 0, 0 };

Vector<2> a, b, c, d;
GraphicsWindow * window;
FrameBuffer * fb;
Rasterizer2D * rast;

typedef bool (*fptr) ();
void setup();
void teardown();

void testHorizontalLineSegment()
{
    setup();
    //horizontal line test
    //left to right
    std::cout << "[TEST  ] Horizontal line " << endl;
    a = { 0, 0}, b = { 50, 0};
    rast->drawLine(a, b, BLACK);
    //right to left
    a = { 50, 50}, b = { 0, 50};
    rast->drawLine(a, b, BLACK);

    fb->show();
    teardown();
}

void testVerticalLineSegment()
{
    setup();    
    std::cout << "[TEST  ] Vertical line " << endl;
    
    a = { 0, 0 }, b = { 0, 50};
    rast->drawLine(a,b, BLACK);

    a = { 50, 50}, b = { 50, 0};
    rast->drawLine(a,b, BLACK);
    fb->show();
    teardown();
}

void testStdSlopeLineSegement()
{
    setup();
    std::cout << "[TEST  ] standard slope line " << endl;

    a = {0, 0}, b = { 100, 100};
    rast->drawLine(a, b, BLACK);

    a = {-50, -50}, b = {-180, -80};
    rast->drawLine(b, a, BLACK);

    a = { 0, 0}, b = {200, 0};
    rast->drawLine(a, b, BLACK);
    
    fb->show();
    teardown();
}

void testOtherSlopeLineSegment()
{
    setup();
    std::cout << "[TEST  ] other than std slope (less than -1 and more than 1) " << endl;

    a = {0, 0}, b = {10, 100};
    rast->drawLine(a, b, BLACK);

    a = {-200, -100}, b = {-150, 100};
    rast->drawLine(a, b, BLACK);

    fb->show();
    teardown();

}

void testTriangles()
{
    setup();
    std::cout << "[TEST  ] Triangles " << endl;

    a = {0,0}, b = {50,50}, c = {-50, 50};
    rast->drawTriangle(a|b|c, BLACK);

    a = {-30, -30}, b = { 50, -90 }, c = { -110, -90};
    rast->drawTriangle(a|b|c, BLACK);

    a = {20,20}, b = {60,-80}, c = {60, 120};
    rast->drawTriangle(a|b|c, BLACK);

    fb->show();
    teardown();
}

void testMoreTriangles()
{
    setup();
    std::cout << "[TEST  ] More Triangles " << endl;

    a = {0,0}, b = {50,0}, c = {25, 250};
    rast->drawTriangle(a|b|c, BLACK);

    a = {-30, -30}, b = { -50, -30 }, c = { -40, -250};
    rast->drawTriangle(a|b|c, BLACK);

    fb->show();
    teardown();
}

void testWithFillTriangle()
{

    setup();
    std::cout << "[TEST  ] Filled Triangles " << endl;

    a = {0,0}, b = {50,50}, c = {-50, 50};
    rast->drawTriangle(a|b|c, BLACK);
    rast->fillTriangle(a|b|c, BLACK);

    a = {-30, -30}, b = { 50, -90 }, c = { -110, -90};
    rast->drawTriangle(a|b|c, BLACK);

    a = {20,20}, b = {60,-80}, c = {60, 120};
    rast->drawTriangle(a|b|c, BLACK);
    rast->fillTriangle(a|b|c, BLACK);

    fb->show();
    teardown();
}

void testQuads()
{
    setup();

    a = {0,0}, b = {50, 0}, c = {50, 50}, d = {0, 50};
    rast->drawQuadrilateral(a|b|c|d, BLACK);

    a = {-20,-20}, b = {-10, -100}, c = {-80, -60}, d = {-90, -25};
    rast->drawQuadrilateral(a|b|c|d, BLACK);

    a = {-30, 20}, b = {-50, 180}, c = {-80, 250}, d = {-100, 170};
    rast->drawQuadrilateral(a|b|c|d, BLACK);

    fb->show();
    teardown();
}

void testFillQuads()
{

    setup();

    a = {0,0}, b = {50, 0}, c = {50, 50}, d = {0, 50};
    rast->drawQuadrilateral(a|b|c|d, BLACK);
    rast->fillQuadrilateral(a|b|c|d, BLACK);

    a = {-20,-20}, b = {-10, -100}, c = {-80, -60}, d = {-90, -25};
    rast->drawQuadrilateral(a|b|c|d, BLACK);
    rast->fillQuadrilateral(a|b|c|d, BLACK);

    a = {-30, 20}, b = {-50, 180}, c = {-80, 250}, d = {-100, 170};
    rast->drawQuadrilateral(a|b|c|d, BLACK);
    rast->fillQuadrilateral(a|b|c|d, BLACK);
    fb->show();
    teardown();
}

int main(int argc, char ** argv)
{
    testHorizontalLineSegment();
    testVerticalLineSegment();
    testStdSlopeLineSegement();
    testOtherSlopeLineSegment();
    testTriangles();
    testMoreTriangles();
    testWithFillTriangle();
    testQuads();
    testFillQuads();
    return 0;
}

void setup()
{
    window = new GraphicsWindow(501,501);
    fb = window->getFrameBuffer();

    rast = new Rasterizer2D(fb);
    rast->clear(WHITE);
}

void teardown()
{
    delete window;
    delete rast;
}
