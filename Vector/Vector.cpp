/**
 * Vector Implementation
 * 
 * Purpose: Vector class allows an application to perform
 *          vector arithmatic in a simple manner. 
 *
 * Author: Wooyoung Chung
 *
 * Date: Jan 13th, 2014
 *
 * This work complies with the JMU Honor Code.
 */

#include "Vector.h"

#pragma mark - Constructors

Vector::Vector(int size)
{
    this->setSize(size, Vector::ROW);
    this->allocateMemory();
    this->setValues(0.0);
}

Vector::Vector(int size, char orientation)
{
    this->setSize(size, orientation);
    this->allocateMemory();
    this->setValues(0.0);
}

Vector::Vector(const Vector& original)
{
    this->setSize(original.size, original.orientation);
    this->allocateMemory();
    this->setValues(original.values);
}

Vector::~Vector()
{
    this->deallocateMemory();
}

#pragma mark - Access members methods

double Vector::get(int i) const
{
    if(this->size < i || 0 >= i)
       throw std::out_of_range("Out of range"); //throw exception
    
    return this->values[i-1];
}

char Vector::getOrientation() const
{
    return this->orientation;
}

int Vector::getSize() const
{
    return this->size;
}

#pragma mark - Norm related methods

double norm(const Vector& a)
{
    double retNorm = 0;
    
    for(int i = 0; i < a.size; ++i)
        retNorm += pow(a.values[i], 2);
    
    return sqrt(retNorm);
}

Vector normalized(const Vector& a)
{
    Vector normVector(a.size, a.orientation);
    double normVal = norm(a);
    for(int i = 0; i < a.size; ++i)
        normVector.values[i] = a.values[i] / normVal;
    
    return normVector;
}

#pragma mark - Overloading operator methods

double& Vector::operator()(int i)
{
    if( this->size < i|| 0 >= i)
        throw std::out_of_range("Out of range"); //throw exception
    
    return this->values[i-1];
}

Vector& Vector::operator=(std::initializer_list<double> values)
{
	if(values.size() != this->size)
		throw std::length_error("Size is not matched");
    //clean perivous allocation
    std::initializer_list<double>::iterator it;

    int i;
    for(i = 0, it = values.begin(); it != values.end(); ++it, ++i)
        this->values[i] = *it;
    
    return *this;
}

Vector& Vector::operator=(const Vector &other)
{
    if(this->size != other.size)
        throw std::length_error("Two vector's length is not same"); // throw exception
    if(this->orientation != other.orientation)
        throw std::length_error("Two vector's orientation is not same");
    
    this->setValues(other.values);
    
    return *this;
}

Vector operator+(const Vector& a, const Vector& b)
{
    if(a.size != b.size)
        throw std::length_error("Two vector's length is not same"); // throw exception
    if(a.orientation != b.orientation)
        throw std::length_error("Two vector's orientation is not same");
    
    Vector *c = new Vector(a.size, a.orientation);
    
    for(int i = 0; i < a.size; ++i)
        c->values[i] = a.values[i] + b.values[i];
    
    return *c;
}

Vector operator-(const Vector& a, const Vector& b)
{
    if(a.size != b.size)
        throw std::length_error("Two vector's length is not same"); // throw exception
    if(a.orientation != b.orientation)
        throw std::length_error("Two vector's orientation is not same");
    
    Vector *c = new Vector(a.size, a.orientation);
    
    for(int i = 0; i < a.size; ++i)
        c->values[i] = a.values[i] - b.values[i];
    
    return *c;
}

double operator*(const Vector& a, const Vector& b)
{
    if(a.size != b.size)
        throw std::length_error("Two vector's length is not same"); // throw exception
    if(a.orientation != b.orientation)
        throw std::length_error("Two vector's orientation is not same");
    
    double ret = 0;
    
    for(int i = 0; i < a.size; ++i)
        ret += a.values[i] * b.values[i];
    
    return ret;
}

Vector operator*(double k, const Vector& a)
{
    Vector * retVector = new Vector(a.size, a.orientation);
    
    for(int i = 0; i < a.size; ++i)
        retVector->values[i] = a.values[i] * k;
    
    return *retVector;
}

Vector operator*(const Vector& a, double k)
{
    Vector * retVector = new Vector(a.size, a.orientation);
    
    for(int i = 0; i < a.size; ++i)
        retVector->values[i] = a.values[i] * k;
    
    return *retVector;
}

bool operator==(const Vector& a, const Vector& b)
{
    if(a.size != b.size || a.orientation != b.orientation)
		return false;
    
    bool ret = true;
    
    for(int i = 0; i < a.size; ++i)
    {
        if(a.values[i] != b.values[i])
        {
            ret = false;
            break;
        }
    }
    
    return ret;
}

bool operator!=(const Vector& a, const Vector& b)
{
    if(a.size != b.size || a.orientation != b.orientation)
		return true;
    
    bool ret = false;
    
    for(int i = 0; i < a.size; ++i)
    {
        if(a.values[i] != b.values[i])
        {
            ret = true;
            break;
        }
    }
    
    return ret;
}

#pragma mark - Miscellaneous methods

Vector trans(const Vector& a)
{
    Vector retVector(a);
    
    if(a.orientation == Vector::ROW)
        retVector.orientation = Vector::COLUMN;
    else
        retVector.orientation = Vector::ROW;
    
    return retVector;
}

#pragma mark - Debug helper methods

double * Vector::get_content() const
{
    /*printf("====== Vector Information =====\n");
    printf("= vector size : %d\n", this->size);
    printf("= vector orientation : %s\n", this->orientation == 0 ? "Column" : "Row");
    printf("= vector values start\n");
    for(int i = 0; i < this->size; ++i)
    {
        printf("%2f ", this->values[i]);
    }
    printf("\n= vector values end\n");
    printf("======= Vector Info End ======\n");
   */ 
    return this->values;
}

#pragma mark - Protected methods

void Vector::allocateMemory()
{
    this->values = new double[this->size];
}

void Vector::deallocateMemory()
{
    delete[] this->values;
}

void Vector::setSize(int size, char orientation)
{
    if(size < 0)
        throw std::invalid_argument("Negative size is invalid"); //throw exception
    if(orientation != this->ROW && orientation != this->COLUMN)
        throw std::invalid_argument("Not valid orientation"); //throw exception
    
    this->size = size;
    this->orientation = orientation;
}

void Vector::setValues(double value)
{
    for(int i = 0; i < this->size; ++i)
        this->values[i] = value;
}

void Vector::setValues(const double *values)
{
    for(int i = 0; i < this->size; ++i)
    {
        this->values[i] = values[i];
    }
}




