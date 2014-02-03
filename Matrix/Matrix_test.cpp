/**
 * Matrix Unit test
 *
 * Author: Wooyoung Chung
 *
 * Last Modified: 1/24/14
 *
 */

#include <iostream>
#include <gtest/gtest.h>

#include "Matrix.hpp"

#define DESC(func, desc) cout << "[ TEST     ] " << func << endl << "[ DESC     ] " << desc << end

class MatrixUnittest : public ::testing::Test {
    protected:
        MatrixUnittest () 
        {
            a = {1, 1, 1, 2, 2, 2, 3, 3, 3};
            b = {1.03, 1.49,
                 3.512, 49.2};
            c = {4, 4, 4, 4, 4,
                 5, 5, 5, 5, 5,
                 6, 6, 6, 6, 6};
            d = {3.59, 89.2,
                 0.421, 9.2413};
        }
        Matrix<3,3> a;
        Matrix<2,2> b;
        Matrix<3,5> c;
        Matrix<2,2> d;
};

/**
 * Test constructor with valid input, should not throw any exception or error
 */
TEST_F(MatrixUnittest, constructor_valid)
{
    Matrix<2,2> test;
    Matrix<4,5> test2;
    Matrix<10,2> test3;
}

/**
 * Test copy construct with valid input, should have same value of original matrix
 */
TEST_F(MatrixUnittest, constructor_copy_valid)
{
    Matrix<3,3> test(a);

    EXPECT_EQ(test(0,0), 1);
    EXPECT_EQ(test(0,2), 1);
    EXPECT_EQ(test(1,2), 2);
}

/**
 * Test operator= initializer_list, should have correct value
 */
TEST_F(MatrixUnittest, operator_initlist_assign_valid)
{
    EXPECT_EQ(a(0,1), 1);
    EXPECT_EQ(a(1,1), 2);
    EXPECT_EQ(c(2,4), 6); 
}

/**
 * Test operator= initializer_list, should have correct value 
 */
TEST_F(MatrixUnittest, operator_initlist_assign_valid2)
{
    EXPECT_EQ(b(0,0), 1.03);
    EXPECT_EQ(b(1,1), 49.2);
}

/**
 * Test operator= initializer_list with unmatched dimension matrix
 * it should throw length error expcetion
 */
TEST_F(MatrixUnittest, operator_initlist_invalid)
{
    Matrix<2,2> result;

    EXPECT_THROW((result = { 1.5315, 483.34 }), std::length_error);
}

/**
 * Test operator= other matrix, should have same value of right hand matrix
 */
TEST_F(MatrixUnittest, operator_assign_valid)
{
    Matrix<2,2> result;
    result = b;

    EXPECT_EQ(b(0,0), result(0,0));
    EXPECT_EQ(b(1,1), result(1,1));
}

/**
 * Test operator= other matrix, should have same value of right hand matrix
 */
TEST_F(MatrixUnittest, operator_assign_valid2)
{
    Matrix<3,3> result;
    result = a;

    EXPECT_EQ(a(0,1), result(0,1));
    EXPECT_EQ(a(2,2), result(2,2));
}

/**
 * Test operator= other matrix with invalid right hand matrix
 * Since we uses template to catch this error in compile time
 * we do not need to test as normal test case
 */
TEST_F(MatrixUnittest, operator_assign_invalid)
{
    //Matrix<2,2> result;
    //result = a; <-- compile error
}

/**
 * test operator() (int) with valid input, should return correct value
 */
TEST_F(MatrixUnittest, operator_access_singleRL_valid)
{
    Matrix<1,3> result;

    result = { 1, 2, 3 };
    EXPECT_NO_THROW(result(1));
    EXPECT_EQ(result(1), 2);
    EXPECT_EQ(result(2), 3);
}

/**
 * test operator() (int) with valid input, should return correct value
 */
TEST_F(MatrixUnittest, operator_access_singleRL_valid2)
{
    Matrix<3,1> result;
    result = { 3.45135, 9.214241, 0.231255 };

    EXPECT_NO_THROW(result(2));
    EXPECT_EQ(result(1), 9.214241);
    EXPECT_EQ(result(0), 3.45135);

}

/**
 * test opeator() (int) with invalid input
 * it should throw out of range if input is not valid
 * it should throw length error if matrix is not <1,R> or <R,1>
 */
TEST_F(MatrixUnittest, operator_access_singleRL_invalid)
{
    Matrix<1,3> result;

    result = {5,53.21, 93.1};
    EXPECT_THROW(result(3), std::out_of_range);
    EXPECT_THROW(a(1), std::length_error);
    EXPECT_THROW(b(3), std::length_error); 
}

/**
 * test opetator() (int,int) with valid input
 * it should return correct value from matrix
 */
TEST_F(MatrixUnittest, operator_access_valid)
{
    EXPECT_NO_THROW(b(1,1));
    EXPECT_EQ(b(0,0), 1.03);
    EXPECT_EQ(b(1,0), 3.512);
    EXPECT_EQ(b(1,1), 49.2);
}

/**
 * test opetator() (int,int) with valid input
 * it should return correct value from matrix
 */
TEST_F(MatrixUnittest, operator_access_valid2)
{
    EXPECT_NO_THROW(a(1,2));
    EXPECT_EQ(a(0,1), 1);
    EXPECT_EQ(a(2,2), 3);
    EXPECT_EQ(a(2,0), 3);
}

/**
 * test operator() (int,int) with invalid input
 * it should throw out of range exception 
 */
TEST_F(MatrixUnittest, operator_access_invalid)
{
    EXPECT_THROW(b(-1,1), std::out_of_range);
    EXPECT_THROW(b(3,1), std::out_of_range);
    EXPECT_THROW(c(9,3), std::out_of_range);
    EXPECT_THROW(c(-1,9), std::out_of_range);
}

/** 
 * test operator+ (Matrix, Matrix) with valid operand
 * the result matrix should have correct value (i.e. a+b value)
 */
TEST_F(MatrixUnittest, operator_plus_valid)
{
    Matrix<2,2> result;

    EXPECT_NO_THROW((result = b + d));
    EXPECT_DOUBLE_EQ(result(0,0), 4.62);
    EXPECT_DOUBLE_EQ(result(1,1), 58.4413);
}

/** 
 * test operator+ (Matrix, Matrix) with valid operand
 * the result matrix should have correct value (i.e. a+b value)
 */
TEST_F(MatrixUnittest, operator_plus_valid2)
{
    Matrix<3,3> result, other;

    other = {1,1,1,2,2,2,3,3,3};

    EXPECT_NO_THROW((result = a + other));
    EXPECT_EQ(result(1,1), 4);
    EXPECT_EQ(result(2,2), 6);
}

/** 
 * test operator+ (Matrix, Matrix) with valid operand
 * the result matrix should have correct value (i.e. a+b value)
 */
TEST_F(MatrixUnittest, operator_plus_valid3)
{
    Matrix<3,5> other;
    Matrix<3,5> result;
    other = c;

    result = c + other;

    EXPECT_EQ(result(0,0), (c(0,0) * 2));
    EXPECT_EQ(result(2,4), (c(2,4) * 2));
    EXPECT_EQ(result(1,3), (c(1,3) * 2));
}

/**
 * test operator+ (Matrix, Matrix) with invalid operand
 *  we catch this in compile time 
 */
TEST_F(MatrixUnittest, operator_plus_invalid)
{
    //Matrix<2,2> result;
    //result = a + b;
}

/** 
 * test operator- (Matrix, Matrix) with valid operand
 * the result matrix should have correct value (i.e. a-b value)
 */
TEST_F(MatrixUnittest, operator_minus_valid)
{
    Matrix<2,2> result;

    result = b - d;

    EXPECT_DOUBLE_EQ(result(0,0), -2.56);
    EXPECT_DOUBLE_EQ(result(1,1), 39.9587);
}

/** 
 * test operator- (Matrix, Matrix) with valid operand
 * the result matrix should have correct value (i.e. a-b value)
 */
TEST_F(MatrixUnittest, operator_minus_valid2)
{
    Matrix<2,2> result;

    result = d - b;

    EXPECT_DOUBLE_EQ(result(0,0), 2.56);
    EXPECT_DOUBLE_EQ(result(0,1), 87.71);
}

/** 
 * test operator- (Matrix, Matrix) with valid operand
 * the result matrix should have correct value (i.e. a-b value)
 */
TEST_F(MatrixUnittest, operator_minus_valid3)
{
    Matrix<3,3> other;
    other = {1, 2, 3,
             4, 5, 6,
             7, 8, 9};

    Matrix<3,3> result;
    result = other - a;

    EXPECT_EQ(result(0,0), 0);
    EXPECT_EQ(result(1,1), 3);
    EXPECT_EQ(result(2,0), 4);
}

/**
 * test operator- (Matrix, Matrix) with invalid operand
 * we catch this in compile time
 */
TEST_F(MatrixUnittest, operator_minus_invalid)
{
    //Matrix<3,3> result;
    //result = a - b;
}

/** 
 * test operator* (Matrix, Matrix) with valid operand
 * the result matrix should have correct value (i.e. a*b value)
 */
TEST_F(MatrixUnittest, operator_multiply_valid)
{
    Matrix<1,2> ta;
    Matrix<2,1> tb;
    
    Matrix<1,1> r;

    ta = { 1, 2};
    tb = { 3, 4};

    r = ta * tb;

    EXPECT_EQ(r(0,0), 11);
}

/** 
 * test operator* (Matrix, Matrix) with valid operand
 * the result matrix should have correct value (i.e. a*b value)
 */
TEST_F(MatrixUnittest, operator_multiply_valid2)
{
    Matrix<3,4> ta;
    Matrix<4,3> tb;

    ta = { 1.03, 3.53, 9.32, 2.31,
           0.21, -9.6, 5.12, 3.4,
           10.4, -43.2, -8.215, 5.662 };
    tb = { 0.43, 0.235, 3.21,
           8.42, 5.01, 2.461,
           9.63, -4.2, 8.673,
           3.1, -5.26, 9.12 };

    Matrix <3,3> result;
    result = ta * tb;

    EXPECT_DOUBLE_EQ(result(0,0), 
            (1.03*0.43 + 3.53*8.42 + 9.32*9.63 + 2.31*3.1));
}

/** 
 * test operator* (Matrix, Matrix) with valid operand
 * the result matrix should have correct value (i.e. a*b value)
 */
TEST_F(MatrixUnittest, operator_multiply_valid3)
{
    Matrix<2,4> ta;
    Matrix<4,2> tb;

    ta = { 1, 1, 1, 1,
           2, 0, 2, 1};
    tb = { 1, 2,
           3, 4,
           1, 2,
           3, 4};

    Matrix<2,2> result;
    result = ta * tb;

    EXPECT_EQ(result(0,0), 8);
    EXPECT_EQ(result(1,0), 7);
    EXPECT_EQ(result(0,1), 12);
    EXPECT_EQ(result(1,1), 12);
}

/**
 * test operator* (Matrix, Matrix) with invalid operand
 * we catch this in compile time
 */
TEST_F(MatrixUnittest, operator_multiply_invalid)
{
    //Matrix<2,2> result;
    //reult = a * b;
}

/**
 * test operator* (double, Matrix) with valid operand
 * The result matrix should have value with each spot 
 * multiply by scalar
 */
TEST_F(MatrixUnittest, operator_scalar_multiply_valid)
{
    Matrix<2,2> ta;

    ta = { 1, 2,
           3, 4 };

    Matrix<2,2> result;

    result = ta * 2;

    EXPECT_EQ(result(0,0), 2);
    EXPECT_EQ(result(0,1), 4);
    EXPECT_EQ(result(1,0), 6);
    EXPECT_EQ(result(1,1), 8);
}

/**
 * test operator* (double, Matrix) with valid operand
 * The result matrix should have value with each spot 
 * multiply by scalar
 */
TEST_F(MatrixUnittest, operator_scalar_multiply_valid2)
{
    Matrix<3,3> result;

    result = a * 1.5;

    EXPECT_EQ(result(0,0), 1.5);
    EXPECT_EQ(result(0,1), 1.5);
    EXPECT_EQ(result(0,2), 1.5);
    EXPECT_EQ(result(1,0), 3);
    EXPECT_EQ(result(1,1), 3);
    EXPECT_EQ(result(1,2), 3);
    EXPECT_EQ(result(2,0), 4.5);
    EXPECT_EQ(result(2,1), 4.5);
}

/**
 * test operator* (double, Matrix) with valid operand
 * The result matrix should have value with each spot 
 * multiply by scalar
 */
TEST_F(MatrixUnittest, operator_scalar_multiply_valid3)
{
    Matrix<2,2> result;

    result = 1.0584 * d;
    
    EXPECT_EQ(result(0,0), 1.0584 * 3.59);
    EXPECT_EQ(result(0,1), 1.0584 * 89.2);
    EXPECT_EQ(result(1,0), 1.0584 * 0.421);
    EXPECT_EQ(result(1,1), 1.0584 * 9.2413);
}

/** 
 * test operator== (Matrix, Matrix) 
 * it should return true if compared values are within TOLERANCE
 */
TEST_F(MatrixUnittest, operator_equal_valid)
{
    Matrix<2,2> ta;
    ta = { 1.03001, 1.4901,
           3.51201, 49.20004}; 

    EXPECT_TRUE(ta == b);
}

/** 
 * test operator=! (Matrix, Matrix) 
 * it should return true if compared values are within TOLERANCE
 */
TEST_F(MatrixUnittest, operator_equal_valid2)
{
    Matrix<2,2> ta;
    ta = { 1.0302, 1.49,
           3.512, 49.2 };

    EXPECT_TRUE(ta != b);
}

/** 
 * test operator== (Matrix, Matrix) 
 * it should return true if compared values are within TOLERANCE
 * if dimension is different, we catch it in compile time
 */
TEST_F(MatrixUnittest, operator_equal_valid3)
{
//    EXPECT_FALSE(a == b);
}

/**
 * test trans(Matrix) 
 * should return a transposed matrix
 */
TEST_F(MatrixUnittest, trans_valid)
{
    Matrix<2,2> result;

    result = trans(b);

    EXPECT_DOUBLE_EQ(result(0,0), 1.03);
    EXPECT_DOUBLE_EQ(result(0,1), 3.512);
    EXPECT_DOUBLE_EQ(result(1,0), 1.49);
    EXPECT_DOUBLE_EQ(result(1,1), 49.2);
}

/**
 * test trans(Matrix) 
 * should return a transposed matrix
 */
TEST_F(MatrixUnittest, trans_valid2)
{
    Matrix<4,1> result;
    Matrix<1,4> original;

    original = { 1, 2, 3, 4 };

    result = trans(original);

    EXPECT_EQ(result(0,0), 1);
    EXPECT_EQ(result(1,0), 2);
    EXPECT_EQ(result(2,0), 3);
    EXPECT_EQ(result(3,0), 4);
}

/**
 * test identity() 
 * should return apropriate size of identity matrix
 */
TEST_F(MatrixUnittest, identity_valid)
{
    Matrix<2,2> idn = identity<2>();

    EXPECT_EQ(idn(0,0), 1);
    EXPECT_EQ(idn(0,1), 0);
    EXPECT_EQ(idn(1,0), 0);
    EXPECT_EQ(idn(1,1), 1);
}

/**
 * test identity() 
 * should return apropriate size of identity matrix
 */
TEST_F(MatrixUnittest, identity_valid2)
{
    Matrix<3,3> idn = identity<3>();

    EXPECT_EQ(idn(0,0), 1);
    EXPECT_EQ(idn(1,1), 1);
    EXPECT_EQ(idn(2,2), 1);
    EXPECT_EQ(idn(2,0), 0);
    EXPECT_EQ(idn(2,1), 0);
}

/**
 * test operator| (Matrix, Matrix) with valid inputs
 * should return a matrix that has a | b values
 */
TEST_F(MatrixUnittest, operator_concat_valid)
{
    Matrix<2,4> result;

    result = b | d;

    EXPECT_EQ(result(0,0), b(0,0));
    EXPECT_EQ(result(1,1), b(1,1));
    EXPECT_EQ(result(0,2), d(0,0)); 
    EXPECT_EQ(result(0,3), d(0,1));
}

/**
 * test operator| (Matrix, Matrix) with valid inputs
 * should return a matrix that has a | b values
 */
TEST_F(MatrixUnittest, operator_concat_valid2)
{
    Matrix<4,4> result;
    Matrix<4,2> a;
    Matrix<4,2> b;

    a = { 1, 2,
          3, 4,
          5, 6,
          7, 8};

    b = { 9, 0,
          1, 2,
          3, 4,
          5, 6};

    result = a | b;

    EXPECT_EQ(result(0,0), 1);
    EXPECT_EQ(result(3,3), 6);
    EXPECT_EQ(result(3,2), 5);
    EXPECT_EQ(result(1,3), 2);

}

/**
 * test operator| (Matrix, Matrx) with invalid inputs
 * if two matrices' rows are not match, it cannot be concated
 * we catch this in compile time
 */
TEST_F(MatrixUnittest, operator_concat_invalid)
{
    //Matrix<4,4> result;
    //result = a | b;
}

/**
 * test cof(Matrix, int, int) with valid values
 * it should return cofactor of given matrix and 
 * exclude given row and column
 */
TEST_F(MatrixUnittest, cof_valid)
{
    double result = cof(b, 0, 0);

    EXPECT_EQ(result, 49.2);
}

/**
 * test cof(Matrix, int, int) with valid values
 * it should return cofactor of given matrix and 
 * exclude given row and column
 */
TEST_F(MatrixUnittest, cof_valid2)
{
    double result = cof(a, 0, 0);

    EXPECT_EQ(result, 0);
}

/**
 * test cof(Matrix, int, int) with valid values
 * it should return cofactor of given matrix and 
 * exclude given row and column
 */
TEST_F(MatrixUnittest, cof_valid3)
{
    Matrix<3,3> ta;

    ta = { 1, 3, 1,
           5, 2, 2,
           6, 4, 9};

    double result = cof(ta, 0, 1);

    EXPECT_EQ(result, -33);
}

/**
 * test cof(Matrix, int, int) with invalid values
 * it should throw out of range exception
 */
TEST_F(MatrixUnittest, cof_invalid)
{
    double result;

    EXPECT_THROW((result = cof(a, -1, 0)), std::out_of_range);
}

/**
 * test Matrix submatrix(Matrix,int,int) with valid values
 * it should return submatrix of given matrix 
 */
TEST_F(MatrixUnittest, submatrix_valid)
{
    Matrix <2,2> result;

    result = submatrix(a,0,0);

    EXPECT_EQ(result(0,0), 2);
    EXPECT_EQ(result(1,1), 3);
}

/**
 * test Matrix submatrix(Matrix,int,int) with valid values
 * it should return submatrix of given matrix 
 */
TEST_F(MatrixUnittest, submatrix_valid2)
{
    Matrix<2,4> result;

    result = submatrix(c,1,2);

    EXPECT_EQ(result(0,0), 4);
    EXPECT_EQ(result(1,3), 6);
}

/**
 * test Matrix submatrix(Matrix,int,int) with valid values
 * it should return submatrix of given matrix 
 */
TEST_F(MatrixUnittest, submatrix_valid3)
{

    Matrix<3,3> ta;

    ta = { 2, 4, 3,
           5, 1, 0,
           9, 2, 1 }; 
    
    Matrix<2,2> result;

    result = submatrix(ta,0,2);

    EXPECT_EQ(result(0,0), 5);
    EXPECT_EQ(result(1,0), 9);
    EXPECT_EQ(result(0,1), 1);
    EXPECT_EQ(result(1,1), 2);
}

/**
 * test det(Matrix) with givnen matrix
 * it should return correct determinent of matrix
 */
TEST_F(MatrixUnittest, det_valid)
{
    Matrix<2,2> ta;
    ta = { 2, 4,
           1, 9}; // det is 2*9 - 4*1 = 14

    double result = det(ta);

    EXPECT_EQ(14, result);
}

/**
 * test det(Matrix) with givnen matrix
 * it should return correct determinent of matrix
 */
TEST_F(MatrixUnittest, det_valid2)
{
    Matrix<3,3> ta;

    ta = { 2, 4, 3,
           5, 1, 0,
           9, 2, 1 }; 

    // 2*1 - 4*5 + 3*(1) 
    
    double result = det(ta);

    EXPECT_EQ(-15, result);
}

/**
 * test det(Matrix) with givnen matrix
 * it should return correct determinent of matrix
 */
TEST_F(MatrixUnittest, det_valid3)
{
    Matrix<4,4> ta;

    ta = { 5, 2, 9, 1,
           0, 3, 4, 8,
           7, 2, 10, 3,
           1, 5, 4, 1 };

    double result = det(ta);

    EXPECT_EQ(484, result);
}

/**
 * test det(Matrix) with givnen matrix
 * it should return correct determinent of matrix
 */
TEST_F(MatrixUnittest, det_valid4)
{
    Matrix<5,5> ta;

    ta = { 5, 4, 3, 2, 1,
           1, 2, 3, 4, 5,
           6, 7, 8, 9, 10,
           4, 2, 4, 6, 5,
           19, 2, 1, 4, 0 };

    double result = det(ta);

    EXPECT_EQ(0, result);
}

/** 
 * test getColumn(int) 
 * it should return column matrix <R,1> with given <R,C> matrix
 */
TEST_F(MatrixUnittest, getcolumn_valid)
{
    Matrix <2,1> result;

    result = b.getColumn(0);

    
    EXPECT_EQ(result(0,0), 1.03);
    EXPECT_EQ(result(1,0), 3.512);

}

/** 
 * test getColumn(int) 
 * it should return column matrix <R,1> with given <R,C> matrix
 */
TEST_F(MatrixUnittest, getcolumn_valid2)
{
    Matrix<3,1> result;

    result = a.getColumn(1);

    EXPECT_EQ(result(0,0), a(0,1));
    EXPECT_EQ(result(1,0), a(1,1));
    EXPECT_EQ(result(2,0), a(2,1));

}

/** 
 * test getColumn(int)  with invalid values
 * it should throw exception
 */
TEST_F(MatrixUnittest, getcolumn_valid3)
{
    Matrix<3,1> result;;

    EXPECT_THROW((result = a.getColumn(4)), std::out_of_range);
}

/**
 * test minor(Matrix, int, int)
 * it should return minor of given matrix
 */
TEST_F(MatrixUnittest, minor_valid)
{
    double result = matrix_minor(b, 0, 0);

    EXPECT_EQ(result, 49.2);
}

/**
 * test minor(Matrix, int, int)
 * it should return minor of given matrix
 */
TEST_F(MatrixUnittest, minor_valid2)
{
    double result = matrix_minor(a, 0, 0);

    EXPECT_EQ(result, 0);
}
