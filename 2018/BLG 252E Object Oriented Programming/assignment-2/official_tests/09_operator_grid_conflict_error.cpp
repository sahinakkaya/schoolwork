#include<iostream>
using namespace std;

//#define MAX_OPERATOR_SIZE 50
#include "assignment2.cpp"


int main(){
   OperatorGrid operator_grid(3,5);


   ArithmeticOperator *ar_operator1 = new ArithmeticOperator(2,2,1,'x');
   ArithmeticOperator *ar_operator2 = new ArithmeticOperator(2,3,1,'x');
   ArithmeticOperator *ar_operator3 = new ArithmeticOperator(2,4,1,'x');


   operator_grid.place_operator(ar_operator1);
   operator_grid.place_operator(ar_operator2);
   operator_grid.place_operator(ar_operator3);


   operator_grid.move_operator(1, 1, 'R', 2);
   operator_grid.move_operator(1, 2, 'R', 1);
   operator_grid.move_operator(1, 2, 'L', 1);
   operator_grid.move_operator(1, 5, 'L', 2);

   return 0;
}

