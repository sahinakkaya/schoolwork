#include<iostream>
using namespace std;

//#define MAX_OPERATOR_SIZE 50
#include "assignment2.cpp"


int main(){
   ArithmeticOperator ar_operator1(1,2,3,'+');
   ArithmeticOperator ar_operator2(4,5,6,'-');
   ArithmeticOperator ar_operator3(7,8,9,'x');
   ArithmeticOperator ar_operator4(1,3,5,'/');

   cout << "SIGN=" << ar_operator1.get_sign() << endl; 
   cout << "SIGN=" << ar_operator2.get_sign() << endl; 
   cout << "SIGN=" << ar_operator3.get_sign() << endl; 
   cout << "SIGN=" << ar_operator4.get_sign() << endl; 

   return 0;
}

