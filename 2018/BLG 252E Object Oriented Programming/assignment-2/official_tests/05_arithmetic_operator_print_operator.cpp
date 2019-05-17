#include<iostream>
using namespace std;

//#define MAX_OPERATOR_SIZE 50
#include "assignment2.cpp"


int main(){
   ArithmeticOperator ar_operator1(1,2,3,'+');
   ArithmeticOperator ar_operator2(4,5,6,'-');
   ArithmeticOperator ar_operator3(7,8,9,'x');
   ArithmeticOperator ar_operator4(1,3,5,'/');

   ar_operator1.print_operator(); 
   cout << endl; 

   ar_operator2.print_operator(); 
   cout << endl; 

   ar_operator3.print_operator(); 
   cout << endl; 

   ar_operator4.print_operator(); 
   cout << endl; 

   return 0;
}

