#include<iostream>
using namespace std;

//#define MAX_OPERATOR_SIZE 50
#include "assignment2.cpp"


int main(){
   OperatorGrid operator_grid(7,7);

   ArithmeticOperator *ar_operator1 = new ArithmeticOperator(3,5,1,'+');
   ArithmeticOperator *ar_operator2 = new ArithmeticOperator(7,6,1,'-');
   ArithmeticOperator *ar_operator3 = new ArithmeticOperator(5,3,1,'x');
   ArithmeticOperator *ar_operator4 = new ArithmeticOperator(2,4,1,'/');

   operator_grid.place_operator(ar_operator1);
   operator_grid.place_operator(ar_operator2);
   operator_grid.place_operator(ar_operator3);
   operator_grid.place_operator(ar_operator4);

   operator_grid.move_operator(7, 6, 'U', 1);
   operator_grid.move_operator(3, 5, 'R', 1);
   operator_grid.move_operator(5, 3, 'D', 1);
   operator_grid.move_operator(2, 4, 'L', 1);

   return 0;
}

