/**
 * Gemotry unittest 
 *
 * author: Wooyoung Chung
 *
 * 2/14/14
 */

#include <iostream>
#include <gtest/gtest.h>

#include "Geometry.hpp"

class GeometryUnittest : public ::testing::Test {
    protected:

};

TEST_F(GeometryUnittest, area_valid)
{
    Vector<2> a, b, c;

    c = {0, 2};
    b = {2, 2};
    a = {2, 0};

    double ret = area<2>(a, b, c);

    EXPECT_DOUBLE_EQ(2, ret);
}

TEST_F(GeometryUnittest, area_valid2)
{
    Vector<2> a, b, c;
    a = {-1, 3};
    b = {2, 3};
    c = {2, 6};

    double ret = area<2>(a, b, c);

    EXPECT_DOUBLE_EQ(9.0/2.0, ret);
}

TEST_F(GeometryUnittest, area_valid3)
{
    Vector<2> a, b, c;
    a = {2.315, 4.35135};
    b = {0.4214, 8.3515};
    c = {9.1215, 0.31};

    double ret = area <2>(a,b,c);
}

TEST_F(GeometryUnittest, bary_valid)
{
    Vector<2> a, b, baryComb;
    
    a = { 1, 2 };
    b = { 0, 2 };

    baryComb = barycentricCombination(a, b, 0.7);

    EXPECT_DOUBLE_EQ(baryComb.get(0,0), 0.7);
    EXPECT_DOUBLE_EQ(baryComb.get(1,0), 2);
}

TEST_F(GeometryUnittest, bary_valid2)
{
    Vector<2> a, b, bary;

    a = {1.2, 4.25};
    b = {6.23, 9.23};

    bary = barycentricCombination(a, b, 0.2);
    
    EXPECT_DOUBLE_EQ(bary(0), 1.2*0.2 + 6.23*0.8);
    EXPECT_DOUBLE_EQ(bary(1), 4.25*0.2 + 9.23*0.8);
}

TEST_F(GeometryUnittest, bary_valid3)
{

}

TEST_F(GeometryUnittest, getBounds_valid)
{
    Matrix<2,3> triangle;

    triangle = { 0, 6, 3,
                 0, 3, 6};

    Matrix<2,2> bound = getBounds(triangle);
    
    EXPECT_EQ(bound(0,0), 0);
    EXPECT_EQ(bound(1,0), 0);
    EXPECT_EQ(bound(0,1), 6);
    EXPECT_EQ(bound(1,1), 6);
}

TEST_F(GeometryUnittest, getBounds_valid2)
{

}

TEST_F(GeometryUnittest, getBounds_valid3)
{

}

TEST_F(GeometryUnittest, inside_valid)
{
    Vector<2> p, q, p2, r,s,t;

    p = { 3,3 };
    q = { 2,3 };

    r = { 5,1 };
    s = { 3,5 };
    t = { 2,2 };

    EXPECT_TRUE(inside<2>(p, r, s, t));
    EXPECT_FALSE(inside<2>(q, r, s, t));
}


TEST_F(GeometryUnittest, inside_valid2)
{
    Vector<2> a,b,c,p,r;

    a = {0,0}, b = {5,3}, c = {2,6};
    p = {4.23, 4};
    r = {2,5.3423};

    EXPECT_FALSE(inside<2>(p, a, b, c));
    EXPECT_TRUE(inside<2>(r, a, b, c));
}

TEST_F(GeometryUnittest, inside_valid3)
{
    Vector<2> a,b,c,p;

    a = {2.341, 5.142};
    b = {10.42, 9.24};
    c = {8.313, 8.421};

    p = {5.2914, 3.1531};

    EXPECT_FALSE(inside<2>(p,a,b,c));
}

TEST_F(GeometryUnittest, toImplicit_valid)
{
    Vector<2> a, b, n;

    a = {23, 1};
    b = {3, 11};
    double ret = toImplicit<2>(a, b, &n);
    
    EXPECT_DOUBLE_EQ(-250, ret);
}

TEST_F(GeometryUnittest, toImplicit_valid2)
{
    Vector<2> a, b, n;

    a = {1, 3};
    b = {0, 2};
    double ret = toImplicit<2>(a, b, &n);

    EXPECT_DOUBLE_EQ(-2, ret);
}

TEST_F(GeometryUnittest, toImplicit_valid3)
{
    Vector<2> a, b, n;

    a = {3, 3};
    b = {-4, -4};
    double ret = toImplicit<2>(a, b, &n);

    EXPECT_DOUBLE_EQ(0, ret);
}


TEST_F(GeometryUnittest, intersect_valid)
{
    Vector<2> p,q,r,s;
    double alpha, beta;

    p = { 0,0 };
    q = { 2,2 };

    r = { 0,2 };
    s = { 1,0 };

    alpha = 0, beta = 0;

    EXPECT_TRUE(intersect<2>(p,q,r,s,alpha,beta));
}

TEST_F(GeometryUnittest, intersect_valid2)
{

}

TEST_F(GeometryUnittest, intersect_valid3)
{

}

TEST_F(GeometryUnittest, signedarea_valid)
{

}

TEST_F(GeometryUnittest, signedarea_valid2)
{

}

TEST_F(GeometryUnittest, signedarea_valid3)
{

}

TEST_F(GeometryUnittest, halfspace_valid)
{

}

TEST_F(GeometryUnittest, halfspace_valid2)
{

}

TEST_F(GeometryUnittest, halfspace_valid3)
{

}
