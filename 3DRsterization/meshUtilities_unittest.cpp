#include <gtest/gtest.h>
#include "meshUtilities.h"
#include <list>
#include "Triangle.h"
#include "../Matrix/Matrix.hpp"

class meshUtilitiesUnit : public ::testing::Test {

};

TEST_F(meshUtilitiesUnit, valid_read)
{
    list<Triangle *> triangles;
    read("teapot.txt", triangles);
    EXPECT_FALSE(triangles.size() == 0);
}
TEST_F(meshUtilitiesUnit, valid_findBound)
{
    list<Triangle *> triangles;
    read("teapot.txt", triangles);
    Matrix<4,2> ret;
    ret = findBounds(triangles);
}

TEST_F(meshUtilitiesUnit, valid_findBound2)
{

}

TEST_F(meshUtilitiesUnit, valid_findBound3)
{

}

TEST_F(meshUtilitiesUnit, valid_scaleAndTrans)
{
    list<Triangle *> triangles;
    read("teapot.txt", triangles);
    Matrix<4,2> ret;

    scaleAndTranslate(triangles, 801,801,801);

    ret = findBounds(triangles);
}

TEST_F(meshUtilitiesUnit, valid_scaleAndTrans2)
{

}

TEST_F(meshUtilitiesUnit, valid_scaleAndTrans3)
{

}
