/**
 *  Vector Unit test
 *
 *  Author: Wooyoung Chung
 *
 *  Last Modified: 1/24/14
 *
 */


#include <iostream>
#include <gtest/gtest.h>

#include "Vector.hpp"

#define DESC(func, desc) cout << "[ TEST     ] " << func << endl << "[ DESC     ] " << desc << end


class VectorUnittest : public ::testing::Test {
    protected:

};

/**
 * test norm(Matrix) 
 * it should return correct norm value of matrix
 */
TEST_F(VectorUnittest, norm_valid)
{
    Vector<3> test;

    test = {1, 2, 3};

    double result = norm(test);
    double expect = sqrt(pow(1,2) + pow(2,2) + pow(3,2));
    EXPECT_EQ(result, expect);
}

/**
 * test norm(Matrix) 
 * it should return correct norm value of matrix
 */
TEST_F(VectorUnittest, norm_valid2)
{
    Vector<4> test;

    test = {4.9231, 3.4331, 9.12, 0.2315};

    double result = norm(test);
    double expect = sqrt(pow(4.9231, 2) + pow(3.4331, 2) +
            pow(9.12, 2) + pow(0.2315, 2));

    EXPECT_DOUBLE_EQ(result, expect);
}

/**
 * test norm(Matrix) 
 * it should return correct norm value of matrix
 */
TEST_F(VectorUnittest, norm_valid3)
{
    Vector<3> test;

    test = {1.239152812, 4.192418, 2.3914391};

    double result = norm(test);
    double expect = sqrt(pow(test.get(0,0), 2) + pow(test.get(1,0),2) 
            + pow(test.get(2,0), 2));

    EXPECT_DOUBLE_EQ(result, expect);
}

/**
 * test normalized(Matrix)
 * it should return correct Matrix(vector) 
 */
TEST_F(VectorUnittest, normalized_valid)
{
    Vector<3> test, result;

    test = { 1, 2, 3 };

    double norm_value = norm(test);
    result = normalized(test);

    EXPECT_EQ(result.get(0,0), test.get(0,0)/norm_value);
    EXPECT_EQ(result.get(1,0), test.get(1,0)/norm_value);
    EXPECT_EQ(result.get(2,0), test.get(2,0)/norm_value);
}
/**
 * test normalized(Matrix)
 * it should return correct Matrix(vector) 
 */
TEST_F(VectorUnittest, normalized_valid2)
{
    Vector <4> test, result;

    test = {1.15121, 2.651325, 3.12, 4.52};

    double norm_value = norm(test);
    result = normalized(test);

    EXPECT_DOUBLE_EQ(result.get(0,0), test.get(0,0)/norm_value);
    EXPECT_DOUBLE_EQ(result.get(1,0), test.get(1,0)/norm_value);
    EXPECT_DOUBLE_EQ(result.get(2,0), test.get(2,0)/norm_value);
}

/**
 * test normalized(Matrix)
 * if assign to different dimension of Vector, won't compile
 */
TEST_F(VectorUnittest, normalized_valid3)
{
    //Vector <4> test;
    //Vector <3> result;

    //result = normalized(test);
}

/**
 * test operator=(initializer_list) 
 * Vector should have correct values from initializer list
 */
TEST_F(VectorUnittest, initializer_valid)
{
    Vector<3> test;

    EXPECT_NO_THROW((test = { 1, 2, 3}));
}

/**
 * test operator=(initializer_list) 
 * Vector should have correct values from initializer list
 */
TEST_F(VectorUnittest, initializer_valid2)
{
    Vector<3> test;
    test = { 4, 63.341, 3.2415125 };

    EXPECT_EQ(test(0,0), 4);
    EXPECT_EQ(test(1,0), 63.341);
    EXPECT_DOUBLE_EQ(test(2,0), 3.2415125);
}

/**
 * test operator=(initializer_list)
 * invalid size of input should throw exception
 */
TEST_F(VectorUnittest, initializer_invalid)
{
    Vector<3> test;
    
    EXPECT_THROW((test = {1,2,3,4}), std::length_error);
}

/**
 * test operator=(Matrix)
 * should return Vector with size of given matrix's row
 */
TEST_F(VectorUnittest, operator_assign_valid)
{
    Vector<3> test, result;

    test = { 1,2,3 };

    result = test;

    EXPECT_EQ(result(0,0), test(0,0));
    EXPECT_EQ(result(1,0), test(1,0));
    EXPECT_EQ(result(2,0), test(2,0));
}

/**
 * test operator=(Matrix)
 * should return Vector with size of given matrix's row
 */
TEST_F(VectorUnittest, operator_assign_valid2)
{
    Vector<2> test, result;

    test = { 1.1351251, 3.1241241};

    result = test;

    EXPECT_EQ(result(0,0), test(0,0));
    EXPECT_EQ(result(1,0), test(1,0));
}

/**
 * test operator=(Matrix)
 * assigning different size of vector to other vector should
 * be caught in compile time
 */
TEST_F(VectorUnittest, operator_assign_invalid)
{
    //Vector<3> test;
    //Vector<4> result;

    //test = { 1, 2, 3};
    //result = test;
}













