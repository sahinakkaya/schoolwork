#include<iostream>
using namespace std;

//#define MAX_OPERATOR_SIZE 50
#include "assignment2.cpp"


int main(){
   OperatorGrid operator_grid(6,7);


   ArithmeticOperator *ar_operator1 = new ArithmeticOperator(3,3,2,'+');
   ArithmeticOperator *ar_operator2 = new ArithmeticOperator(6,3,2,'-');
   ArithmeticOperator *ar_operator3 = new ArithmeticOperator(3,6,1,'/');
   ArithmeticOperator *ar_operator4 = new ArithmeticOperator(6,6,1,'x');


   operator_grid.place_operator(ar_operator1);
   operator_grid.place_operator(ar_operator2);
   operator_grid.place_operator(ar_operator3);
   operator_grid.place_operator(ar_operator4);


   operator_grid.move_operator(4, 5, 'D', 1);
   operator_grid.move_operator(3, 1, 'R', 1);
   operator_grid.move_operator(6, 3, 'L', 1);

   return 0;
}

