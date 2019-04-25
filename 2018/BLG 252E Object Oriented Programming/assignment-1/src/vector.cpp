/*
 * vector.cpp
 *
 *      Author: Şahin Akkaya
 *      Number: 150170098
 */
#include "vector.h"
#include <iostream>


int Vector::vector_count = 0;


// Constructor with no parameters. Meaningless but required for 
// using a variable as a placeholder.
Vector::Vector(){
    vector_count++;
    id = vector_count;
    size = 0;
    contents = NULL;
}
/*
 / Actual Constructor
 / takes an integer for size of the Vector and
 / double* for contents 
*/
Vector::Vector(int& s, double* c){
    vector_count++;
    id = vector_count;
    size =  s;
    contents = new double[s];
    for(int i=0;i<s;i++)
        contents[i] = c[i];
}
// Copy constructor
Vector::Vector(const Vector& vin){
    vector_count++;
    id = vector_count;
    size = vin.get_size();
    contents = new double[size];
    for(int i=0;i<size;i++){
        contents[i] = vin.get_content(i);
    }
}

Vector& Vector::operator=(const Vector& vin){
    size = vin.get_size();
    delete [] contents;
    contents = new double[size];
    for(int i=0;i<size;i++){
        contents[i] = vin.get_content(i);
    }
    return *this;
}
// Destructor
Vector::~Vector(){
    vector_count--;
    delete [] contents;
}

int Vector::get_size() const{
    return size;
}

double Vector::get_content(int index)const{
    return contents[index];
}

Vector Vector::operator+(const Vector& vin){
    
    int size = vin.get_size();
    if (size != this->get_size())
        throw "Vectors have different sizes. Operation cannot be performed. Skipping...";
    double* contents = new double[size];
    for(int i=0;i<size;i++){
        contents[i] = this->get_content(i) + vin.get_content(i);
    }
    Vector result = Vector(size,contents);
    delete [] contents;
    return result;
}

double Vector::operator*(const Vector& vin){
    int size = vin.get_size();
    if (size != this->get_size())
        throw "Vectors have different sizes. Operation cannot be performed. Skipping...";
    double result = 0;
    for(int i=0;i<size;i++){
        result += this->get_content(i) * vin.get_content(i);
    }
    return result;
}

Vector Vector::operator*(const double& scalar){
    int size = this->get_size();
    double* contents = new double[size];
    for(int i=0;i<size;i++){
        contents[i] = this->get_content(i) * scalar;
    }
    Vector result = Vector(size, contents);
    delete [] contents;
    return result;
    
}

