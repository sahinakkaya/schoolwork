/*
 * polynomial.cpp
 *
 *      Author: Şahin Akkaya
 *      Number: 150170098
 */

#include "polynomial.h"
#include <iostream>


int Polynomial::polynomial_count = 0;

// Constructor with no parameters. Meaningless but required for 
// using a variable as a placeholder.
Polynomial::Polynomial(){
    polynomial_count++;
    id = polynomial_count;
    degree = 0;
    contents = NULL;
}

/*
 / Actual Constructor
 / takes an integer for degree of the polynomial and
 / double* for contents 
*/
Polynomial::Polynomial(int& d, double* c){
    polynomial_count++;
    id = polynomial_count;
    degree =  d;
    contents = new double[degree+1];
    for(int i=0;i<degree+1;i++)
        contents[i] = c[i];
}
// Copy constructor
Polynomial::Polynomial(const Polynomial& vin){
    polynomial_count++;
    id = polynomial_count;
    degree = vin.get_degree();
    contents = new double[degree+1];
    for(int i=0;i<degree+1;i++){
        contents[i] = vin.get_content(i);
    }
}

Polynomial& Polynomial::operator=(const Polynomial& pin){
    degree = pin.get_degree();
    delete [] contents;
    contents = new double[degree+1];
    for(int i=0;i<degree+1;i++){
        contents[i] = pin.get_content(i);
    }
    return *this;
}
// Destructor
Polynomial::~Polynomial(){
    polynomial_count--;
    delete [] contents;
}

int Polynomial::get_degree() const{
    return degree;
}

double Polynomial::get_content(int index)const{
    return contents[index];
}

Polynomial Polynomial::operator+(const Polynomial& pin){
    int degree = pin.get_degree();
    const Polynomial *bigger_polynomial = this, *smaller_polynomial=&pin;
    if(degree>this->get_degree()){
         bigger_polynomial = &pin;
         smaller_polynomial = this;
    }
    int bigger_p_degree = bigger_polynomial->get_degree();
    int smaller_p_degree = smaller_polynomial->get_degree();
 
    double* contents = new double[bigger_p_degree+1];
    for(int i=0;i<bigger_p_degree+1;i++){
        contents[i] = bigger_polynomial->get_content(i);
        int index = smaller_p_degree - bigger_p_degree + i;
        if(index>=0){
            contents[i]+=smaller_polynomial->get_content(index);
        }
    }

    Polynomial result = Polynomial(bigger_p_degree,contents);
    delete [] contents;
    return result;
}

Polynomial Polynomial::operator*(const Polynomial& pin){
    int left_p_degree = this->get_degree();
    int right_p_degree = pin.get_degree();
    int new_degree = left_p_degree + right_p_degree;
    double* contents = new double[new_degree+1]{0};
    for(int i=0;i<left_p_degree+1;i++){
        for(int j=0;j<right_p_degree+1;j++){
            contents[i+j] += this->get_content(i)*pin.get_content(j); 
        }
    }
    Polynomial result = Polynomial(new_degree,contents);
    delete [] contents;
    return result;
}
