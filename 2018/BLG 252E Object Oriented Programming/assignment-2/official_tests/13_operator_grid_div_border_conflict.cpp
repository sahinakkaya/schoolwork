#include<iostream>
using namespace std;

//#define MAX_OPERATOR_SIZE 50
#include "assignment2.cpp"


int main(){
   OperatorGrid operator_grid(5,5);


   ArithmeticOperator *ar_operator1 = new ArithmeticOperator(3,2,1,'/');
   ArithmeticOperator *ar_operator2 = new ArithmeticOperator(3,3,2,'/');
   ArithmeticOperator *ar_operator3 = new ArithmeticOperator(4,3,1,'/');


   operator_grid.place_operator(ar_operator1);
   operator_grid.place_operator(ar_operator2);
   operator_grid.place_operator(ar_operator3);


   operator_grid.move_operator(1, 5, 'L', 1);
   operator_grid.move_operator(5, 1, 'R', 1);
   operator_grid.move_operator(4, 2, 'U', 1);
   operator_grid.move_operator(2, 4, 'D', 1);

   return 0;
}

