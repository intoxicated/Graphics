/**
 * Vector Unittest with gtest
 *
 * Purpose: Unittest Vector with google test framework
 *
 * Author: Wooyoung Chung
 *
 * Date: Jan 13th, 2014
 *
 * This work complies with the JMU Honor Code.
 */


#include <iostream>
#include <gtest/gtest.h>

#include "Helpers.h"
#include "Vector.h"

#define DESC(func, desc) cout << "[ TEST     ] " << func << endl << "[ DESC     ] " << desc << endl

TEST(VectorOneConstructorTest, PassValidInput) {
    DESC("Vector(int size)", "Pass valid size to constructor");
    
	EXPECT_NO_THROW(Vector v(1));
    EXPECT_NO_THROW(Vector v(100));

	Vector v3(10);
	
	EXPECT_EQ(v3.getSize(), 10);
	EXPECT_TRUE(v3.getOrientation() == Vector::ROW);
}
 
TEST(VectorOneConstructorTest, PassInvalidInput) {
    DESC("Vector(int size)", "Pass invalid size to constructor, should throw exception");
    EXPECT_THROW(Vector v(-1),  std::invalid_argument);
    ASSERT_THROW(Vector v(-120),  std::invalid_argument);
}

TEST(VectorTwoConstrutorTest, PassValidInput) {
    DESC("Vector(int size, char orientation)", "Pass valid size and orientation to constructor");
    EXPECT_NO_THROW(Vector v(1, Vector::ROW));
    EXPECT_NO_THROW(Vector v(5, Vector::COLUMN));
}

TEST(VectorTwoConstrutorTest, PassInvalidSize) {
    DESC("Vector(int size, char orientation)", "Pass invalid size to constructor, should throw exception");
    EXPECT_THROW(Vector v(-1, Vector::ROW),  std::invalid_argument);
    ASSERT_THROW(Vector v(-120, Vector::COLUMN),  std::invalid_argument);
}

TEST(VectorTwoConstrutorTest, PassInvalidOrientation) {
    DESC("Vector(int size, char orientation)", "Pass invalid size to constructor, should throw exception");
    EXPECT_THROW(Vector v(4, -1),  std::invalid_argument);
    ASSERT_THROW(Vector v(20, 5),  std::invalid_argument);
}

TEST(VectorCopyConstructorTest, ValidCopy) {
    DESC("Vector(const Vector& original)", "Perform valid copy and compare size");
    Vector v(2);
	v = { 1, 2 };
    Vector v1 = v;

    EXPECT_TRUE(v.getSize() == v1.getSize());
	EXPECT_TRUE(arrayMatch(v.get_content(), v1.get_content(), v.getSize()));
}

TEST(VectorCopyConstructorTest, ValidCopy2) {
    DESC("Vector(const Vector& original)", "Perform valid copy and compare contents");
    Vector v(5, Vector::ROW);
    v = {4.0,7.0,12.1,9.8,1.4};

    Vector v1 = v;
    
    EXPECT_TRUE(v.getSize() == v1.getSize());
    EXPECT_TRUE(v.getOrientation() == v1.getOrientation());
    EXPECT_TRUE(arrayMatch(v.get_content(), v1.get_content(), v.getSize()));
}

TEST(VectorGet, ValidGet) {
    DESC("double get(int i) const", "Verify get function returns right values");
    Vector v(5);
    v = { 6.0, 3.0, 10.3, 94.1, 9.2 };
    double expected[] = { 6.0, 3.0, 10.3, 94.1, 9.2 };
    
    for(int i = 0; i < 5; ++i)
    {
        //std::cout << " Expect: " << expect[i] << endl;
        //std::cout << " Actual: " << v.get(i) << endl;
        EXPECT_TRUE(v.get(i) == expected[i]);
    }
}

TEST(VectorGet, ValidGet2) {
    DESC("double get(int i) const", "Verify get function returns right values");
    Vector v(6);
    v = { 6, -3, 10, 94.1, 9, -19 };
    double expected[] = { 6, -3, 10, 94.1, 9, -19 };
    
    for(int i = 0; i < 5; ++i)
    {
        //std::cout << " Expect: " << expect[i] << endl;
        //std::cout << " Actual: " << v.get(i) << endl;
        EXPECT_TRUE(v.get(i) == expected[i]);
    }
}

TEST(VectorGet, EmptyGet) {
    DESC("double get(int i) const", "Attempt to get value from empty vector, should throw exception");
    Vector v(0);
    EXPECT_THROW(v.get(0), std::out_of_range);
    EXPECT_THROW(v.get(1), std::out_of_range);
}

TEST(VectorGet, OutofRangeGet) {
    DESC("double get(int i) const", "Attempt to get value from vector but out of range, should throw exception");
    Vector v(5);
    EXPECT_THROW(v.get(7), std::out_of_range);
    EXPECT_THROW(v.get(-1), std::out_of_range);
    EXPECT_THROW(v.get(5), std::out_of_range);
}

TEST(VectorOrientation, DefaultOrientation) {
    DESC("char getOrientation() const", "Default Constructor with size should return default orientation (ROW)");
	Vector v(5);
    EXPECT_TRUE(v.getOrientation() == Vector::ROW);
}

TEST(VectorOrientation, ValidOrientation) {
    DESC("char getOrientation() const", "Set orientation through constructor then getter should return right orientation");
    Vector v(5, Vector::ROW);
    Vector v1(2, Vector::COLUMN);
    
    EXPECT_TRUE(v.getOrientation() == Vector::ROW);
    EXPECT_TRUE(v1.getOrientation() == Vector::COLUMN);
}

TEST(VectorOrientation, CopyAndValidate) {
    DESC("char getOrientation() const", "Copy from other vector should have same orientation");
    Vector v(5, Vector::ROW);
    Vector v1 = v;
    
    EXPECT_TRUE(v.getOrientation() == Vector::ROW);
    EXPECT_TRUE(v1.getOrientation() == v.getOrientation());
}

TEST(VectorGetSize, ValidSize) {
    DESC("int getSize() const", "getSize should return correct size of vector");
    Vector v(3);
    EXPECT_TRUE(v.getSize() == 3);
}

TEST(VectorGetSize, EmptySize) {
    DESC("int getSize() const", "getSize should return 0 size of vector");
    Vector v(0);
    EXPECT_TRUE(v.getSize() == 0);
}

TEST(VectorGetSize, CopyAndValidate) {
    DESC("int getSize() const", "getSize should return same size as a vector that it was copied");
    Vector v(5);
    Vector v1 = v;
    EXPECT_TRUE(v.getSize() == 5);
    EXPECT_TRUE(v.getSize() == v1.getSize());
}

TEST (VectorNorm, validNorm) {
    DESC("friend double norm(const Vector& a)", "norm should return correct value of norm from vector");
    Vector v(5, Vector::ROW);
    v = {4, 1, 6, 9, 3};
    
    double ret = norm(v);
    
    //calculate norm
    //sqrt(4^2 + 1^2 + 6^2 + 9^2 + 3^2)
    double expect = sqrt(pow(4, 2) + pow(1,2) + pow(6, 2) + pow(9,2) + pow(3, 2));
    
    EXPECT_TRUE(ret == expect);
}

TEST (VectorNorm, validNorm2) {
    DESC("friend double norm(const Vector& a)", "norm should return correct value of norm from vector");
    Vector v(5, Vector::ROW);
    v = {-4, 1, -6, 9, 3};
    
    double ret = norm(v);
    
    //calculate norm
    //sqrt(4^2 + 1^2 + 6^2 + 9^2 + 3^2)
    double expect = sqrt(pow(-4, 2) + pow(1,2) + pow(-6, 2) + pow(9,2) + pow(3, 2));
    
    EXPECT_TRUE(ret == expect);
}

TEST (VectorNorm, ValidNorm3) {
    DESC("friend double norm(const Vector& a)", "norm should return correct value of norm from vector");
    Vector v(5, Vector::ROW);
    v = {23.1, 1.5, 8.2, 4.8, 3.9};
    
    Vector v1(5, Vector::ROW);
    v1 = {-4, 1, -6, 9, 3};
    
    Vector v3 = v + v1;
    double ret = norm(v3);

    //calculate norm
    double expect = sqrt(pow(19.1, 2) + pow(2.5,2) + pow(2.2, 2) + pow(13.8,2) + pow(6.9, 2));
    
    EXPECT_TRUE(ret == expect);
}

TEST (VectorNormalized, ValidNormalized) {
    DESC("friend Vector normalized(const Vector& a)", "normalized should return correct vector with valid inputs");
	
	Vector v(3);
	v = { 1, 2, 3 };

	Vector v1 = normalized(v);
	
	double n = norm(v); 
	double expected[] = {1/n, 2/n, 3/n};

	EXPECT_TRUE(arrayMatch(expected, v1.get_content()));
}

TEST (VectorNormalized, ValidNormalized2) {
    DESC("friend Vector normalized(const Vector& a)", "normalized should return correct vector with valid inputs");
	
	Vector v(3);
	v = { 1.4, 8.5, 3.86 };

	Vector v1 = normalized(v);

	double n = norm(v);
	double expected[] = {1.4/n, 8.5/n, 3.86/n};

	EXPECT_TRUE(arrayMatch(expected, v1.get_content()));
}

TEST (VectorNormalized, ValidNormalized3) {
    DESC("friend Vector normalized(const Vector& a)", "normalized should return correct vector with valid inputs");
	
	Vector v(3);
	v = { 1, 2, 3 };

	Vector v1 = normalized(normalized(v));

	double n = norm(v);
	Vector v2(3);
	v2 = {1/n, 2/n, 3/n};
	n = norm(v2);

	double expected[] = {v2.get(0)/n, v2.get(1)/n, v2.get(2)/n};

	EXPECT_TRUE(arrayMatch(expected, v1.get_content()));
}


TEST (VectorAccessOperator, ValidOperator) {
    DESC("double& operator()(int i)", "operator() to access values in vector");
	
	Vector v(3);
	v = { 1, 2, 3 };

	EXPECT_EQ(v(1), 1);
	EXPECT_EQ(v(2), 2);
	EXPECT_EQ(v(3), 3);
}

TEST (VectorAccessOperator, ValidOperator2) {
    DESC("double& operator()(int i)", "operator() to access and modifiy values in vector");
	
	Vector v(3);
	v = { 1, 2, 3 };

	v(2) = 5;
	v(1) = 10.1;

	EXPECT_EQ(5, v(2));
	EXPECT_EQ(10.1, v(1));
}

TEST (VectorAccessOperator, InvalidOperator) {
    DESC("double& operator()(int i)", "operator() to access invalid index, should throw exception");
	
	Vector v(3);
	v = { 1, 2, 3 };

	EXPECT_THROW(v(4), std::out_of_range);
	EXPECT_THROW(v(-1), std::out_of_range);
}

TEST(VectorInitListOperator, ValidOperator) {
    DESC("Vector& operator=(std::initializer_list<double> values)", "Set initializer_list to vector and compare");
    Vector v(3);
    v = { 1,2,3 };
    double expected[] = {1,2,3};
    EXPECT_TRUE(arrayMatch(expected, v.get_content()));
}

TEST(VectorInitListOperator, ValidOperator2) {
    DESC("Vector& operator=(std::initializer_list<double> values)", "Set initializer_list to vector and compare");
    Vector v(5);
    v = { 1,2,3,4,5 };
    double expected[] = {1,2,3,4,5};
    EXPECT_TRUE(v.getSize() != 3);
    EXPECT_TRUE(v.getSize() == 5);
    EXPECT_TRUE(arrayMatch(expected, v.get_content()));
}

TEST(VectorInitListOperator, InvalidOperator) {
    DESC("Vector& operator=(std::initializer_list<double> values)", "Set empty list to vector, which should be fine");
    Vector v(0);
   	
	EXPECT_THROW((v = {1,2,3}), std::length_error);
    EXPECT_TRUE(v.getSize() == 0);
}

TEST(VectorAssignVectorOperator, ValidOperator) {
    DESC("Vector& operator=(const Vector& other)", "Testing valid assignment operator");
	Vector v(3);
	v = { 1, 2, 3 };
	Vector v1(3), v2(3);

	v1 = v2 = v;

	EXPECT_TRUE(arrayMatch(v1.get_content(), v.get_content(), v.getSize()));
	EXPECT_TRUE(arrayMatch(v.get_content(), v2.get_content(), v.getSize()));
	EXPECT_TRUE(arrayMatch(v1.get_content(), v2.get_content(), v.getSize()));
}

TEST(VectorAssignVectorOperator, ValidOperator2) {
    DESC("Vector& operator=(const Vector& other)", "Testing valid assignment operator after changing values");

	Vector v(5, Vector::COLUMN);
	v = { 1, 2, 3, 4, 5 };

	Vector v1(v);

	v = { 5, 6, 7, 8, 9 };
	v1 = { 10, 11, 12, 13, 14};

	v = v1;

	EXPECT_TRUE(arrayMatch(v.get_content(), v1.get_content(), v.getSize()));
}

TEST(VectorAssignVectorOperator, InvalidOperator) {
    DESC("Vector& operator=(const Vector& other)", "Invalid assignment operator when either length or orientation is different, should throw exception");

	Vector v(4, Vector::COLUMN);
	Vector v1(4, Vector::ROW);

	v = { 1, 2, 3, 4 };
	
	EXPECT_THROW(v = v1, std::length_error);

	Vector v2(3, Vector::ROW);

	EXPECT_THROW(v2 = v1, std::length_error);
}

TEST(VectorPlusOperator, ValidOperator) {
    DESC("friend Vector operator+(const Vector& a, const Vector& b)", "Adding two vectors should be valid");

	Vector v(3, Vector::COLUMN);
	v = { 2,3,4 };

	Vector v1(3, Vector::COLUMN);
	v1 = { 5,6,7 };
	
	Vector result(3, Vector::COLUMN);

	double expected[] = {7,9,11};
	EXPECT_NO_THROW(result = v + v1);
	EXPECT_TRUE(arrayMatch(expected, result.get_content()));
	
}

TEST(VectorPlusOperator, ValidOperator2) {
    DESC("friend Vector operator+(const Vector& a, const Vector& b)", "Adding multiple vectors should be valid");

	Vector v(3), v1(3), v2(3), result(3);

	v = { 1, 2, 3 };
	v1 = { 2, 3, 4 };
	v2 = { 3, 4, 5 };

	double expected[] = { 6, 9, 12 };

	EXPECT_NO_THROW((result = v + v1 + v2));
	EXPECT_TRUE(result.getSize() == 3);
	EXPECT_TRUE(result.getOrientation() == Vector::ROW);
	EXPECT_TRUE(arrayMatch(expected, result.get_content()));
}


TEST(VectorPlusOperator, InvalidOperator) {
    DESC("friend Vector operator+(const Vector& a, const Vector& b)", "Adding different size of vector should throw exception");
	Vector v(3);
	v = { 1, 2, 3 };

	Vector v1(4);
	v1 = { 4, 5, 6, 7 };

	Vector result(4);

	EXPECT_THROW((result = v + v1), std::length_error);
}

TEST(VectorMinusOperator, ValidOperator) {
    DESC("friend Vector operator-(const Vector& a, const Vector& b)", "Subtract two vectors should be valid");
	Vector v(3), v1(3), result(3);

	v = { 1, 2, 3 };
	v1 = { 2, 3, 4 };

	double expected[] = { -1, -1, -1 };

	EXPECT_NO_THROW((result = v - v1));
	EXPECT_TRUE(arrayMatch(expected, result.get_content()));
}

TEST(VectorMinusOperator, ValidOperator2) {
    DESC("friend Vector operator-(const Vector& a, const Vector& b)", "Subtract multiple vectors should be valid");
	
	Vector v(3), v1(3), v2(3), result(3);

	v = { 1, 2, 3 };
	v1 = { 2, 4, 6 };
	v2 = { 3, 6, 9 };

	double expected[] = { 0, 0, 0 };

	EXPECT_NO_THROW((result = v + v1 - v2));
	EXPECT_TRUE(arrayMatch(expected, result.get_content()));
}

TEST(VectorMinusOperator, InvalidOperator) {
    DESC("friend Vector operator-(const Vector& a, const Vector& b)", "Subtract different size of vector should throw exception");
	
	Vector v(3), v1(3), v2(4), result(4), result2(3);

	v = { 1, 2, 3 };
	v1 = { 2, 3, 4 };
	v2 = { 3, 4, 5, 6 };

	EXPECT_THROW((result = v - v1), std::length_error);
	EXPECT_THROW((result = v - v2), std::length_error);
	EXPECT_THROW((result2 = v - v2), std::length_error);
}

TEST(VectorMultiplyOperator, ValidOperator) {
    DESC("friend double operator*(const Vector& a, const Vector& b)", "Basic multiplication of two vectors should be valid");
	Vector v(4), v1(4);

	v = { 1, 2, 3, 4};
	v1 = { 2, 3, 4, 5};

	double expected = 1*2 + 2*3 + 3*4 + 4*5;
	double actual = v * v1;

	EXPECT_TRUE(expected == actual);
}

TEST(VectorMultiplyOperator, ValidOperator2) {
    DESC("friend double operator*(const Vector& a, const Vector& b)", "Multiplying two vectors with double values should return valid result");

	Vector v(4), v1(4);

	v = { 1.1, 1.1, 1.1, 1.1 };
	v1 = { 2.5, 2.5, 2.5, 2.5 };

	double expected = 2.5*1.1 + 2.5*1.1 + 2.5*1.1 + 2.5*1.1;
	double actual = v * v1;

	EXPECT_FLOAT_EQ(expected, actual);		
}

TEST(VectorMultiplyOperator, InvalidOperator) {
    DESC("friend double operator*(const Vector& a, const Vector& b)", "Multplying two different size of vector should throw exception");
	
	Vector v(4), v1(3);

	v = { 1, 1, 1, 1 };
	v1 = { 2, 2, 2 };

	EXPECT_THROW(v*v1, std::length_error);
}

TEST(VectorScalarOperator, ValidOperator) {
    DESC("friend Vector operator*(double k, const Vector& a)\n\t\
         friend Vector operator*(const Vector& a, double k)", "multiply scalar before vector should be operated without error");
	
	Vector v(3);
	v = { 1, 2, 3 };

	v = 2 * v;

	double expected[] = { 2, 4, 6 };

	EXPECT_TRUE(arrayMatch(expected, v.get_content()));
}

TEST(VectorScalarOperator, ValidOperator2) {
    DESC("friend Vector operator*(double k, const Vector& a)\n\t\
         friend Vector operator*(const Vector& a, double k)", "multiply scalar after vector should be valid");
	
	Vector v(5);
	v = { 1.2, 5.3, 8.1, 93.1, 3};
	
	double scale = 2.1;
	double expected[] = {2.1*1.2, 5.3*2.1, 8.1*2.1, 93.1*2.1, 3*2.1};

	v = v * scale;
	
	EXPECT_TRUE(arrayMatch(expected, v.get_content()));
}



TEST(VectorScalarOperator, ValidOperator3) {
    DESC("friend Vector operator*(double k, const Vector& a)\n\t\
         friend Vector operator*(const Vector& a, double k)", "two scalars multiply back and forth of vector should be valid");
	
	Vector v(3);
	v = { 1.42, 5.315, 9.19 };

	double scale = 2.12;
	double expected[] = {scale*1.42*scale, scale*5.315*scale, scale*9.19*scale};

	v = scale * v * scale;

	EXPECT_TRUE(arrayMatch(expected, v.get_content()));
}

TEST(VectorEqualOperator, ValidOperator) {
    DESC("friend bool operator==(const Vector& a, const Vector& b)", "Should return true for vectors that was created through constructor with identical parameters");
    
    Vector v(4, Vector::ROW);
    Vector v2(4, Vector::ROW);
    
    EXPECT_TRUE(v == v2);
}

TEST(VectorEqualOperator, ValidOperator2) {
    DESC("friend bool operator==(const Vector& a, const Vector& b)", "Should return true for identical vectors setting with initializer_list");
    
    Vector v(5);
    v = {1, 2, 3, 4, 5};
    Vector v1(5);
	v1 = {1, 2, 3, 4, 5};
	   
    EXPECT_TRUE(v == v1);	
}

TEST(VectorEqualOperator, ValidOperator3) {
    DESC("friend bool operator==(const Vector& a, const Vector& b)", "Should return false if orientation is different");
    
    Vector v(3, Vector::COLUMN);
    Vector v2(3, Vector::ROW);
    
    EXPECT_FALSE((v == v2));
}

TEST(VectorNotEqualOperator, ValidOperator) {
    DESC("friend bool operator!=(const Vector& a, const Vector& b)", "Should return true if orientation is different");
	
	Vector v(3, Vector::ROW), v1(3, Vector::COLUMN);

	v = { 1, 2, 3 };
	v1 = { 1, 2, 3 };

	EXPECT_TRUE(v != v1);
}

TEST(VectorNotEqualOperator, ValidOperator2) {
    DESC("friend bool operator!=(const Vector& a, const Vector& b)", "One element difference should return true");
	
	Vector v(3), v1(3);

	v = { 1, 2, 3 };
	v1 = { 1, 2, 4 };

	EXPECT_TRUE(v != v1);
}

TEST(VectorNotEqualOperator, ValidOperator3) {
    DESC("friend bool operator!=(const Vector& a, const Vector& b)", "It should return false if two vectors are identical, otherwise true");

	Vector v(3), v1(3);

	v = { 1 ,2 ,3 };
	v1 = { 1, 2, 3 };

	EXPECT_FALSE(v != v1);
}

TEST(VectorTranspose, ValidInput) {
    DESC("friend Vector trans(const Vector& a)", "Initially set vector to COLUMN and call trans, the result vector should have ROW orientation");
	
	Vector v(3, Vector::COLUMN);
	v = { 1, 2, 3 };

	Vector v1 = trans(v);
	EXPECT_TRUE(v1.getOrientation() == Vector::ROW);	
}

TEST(VectorTranspose, ValidInput2) {
    DESC("friend Vector trans(const Vector& a)", "Initially set vector to ROW and call trans, the result vector should have COLUMN orientation");

	Vector v(3, Vector::ROW);
	v = { 2, 3, 4 };

	Vector v1 = trans(v);
	EXPECT_TRUE(v1.getOrientation() == Vector::COLUMN);
}

TEST(VectorTranspose, ValidInput3) {
    DESC("friend Vector trans(const Vector& a)", "valid trans twice, the result should be same as parameter vector");

	Vector v(3, Vector::ROW);
	v = { 1, 2, 3 };

	Vector v1 = trans(trans(v));

	EXPECT_TRUE(v1 == v1);
}
