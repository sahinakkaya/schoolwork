#include<iostream>
using namespace std;

//#define MAX_OPERATOR_SIZE 50
#include "assignment2.cpp"


int main(){
   OperatorGrid operator_grid(5,8);


   ArithmeticOperator *ar_operator1 = new ArithmeticOperator(1,3,2,'-');
   ArithmeticOperator *ar_operator2 = new ArithmeticOperator(1,7,1,'-');
   ArithmeticOperator *ar_operator3 = new ArithmeticOperator(2,7,1,'-');
   ArithmeticOperator *ar_operator4 = new ArithmeticOperator(3,3,2,'-');
   ArithmeticOperator *ar_operator5 = new ArithmeticOperator(4,4,3,'-');


   operator_grid.place_operator(ar_operator1);
   operator_grid.place_operator(ar_operator2);
   operator_grid.place_operator(ar_operator3);
   operator_grid.place_operator(ar_operator4);
   operator_grid.place_operator(ar_operator5);


   operator_grid.move_operator(1, 5, 'D', 1);
   operator_grid.move_operator(2, 6, 'D', 1);
   operator_grid.move_operator(1, 8, 'D', 1);
   operator_grid.move_operator(4, 1, 'D', 1);
   operator_grid.move_operator(3, 6, 'D', 1);
   operator_grid.move_operator(4, 7, 'L', 1);
   operator_grid.move_operator(5, 7, 'R', 1);

   return 0;
}

