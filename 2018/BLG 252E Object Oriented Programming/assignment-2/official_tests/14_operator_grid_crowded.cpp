#include<iostream>
using namespace std;

//#define MAX_OPERATOR_SIZE 50
#include "assignment2.cpp"


int main(){
   OperatorGrid operator_grid(10,7);

   ArithmeticOperator *ar_operator1 = new ArithmeticOperator(2,2,1,'x');
   ArithmeticOperator *ar_operator2 = new ArithmeticOperator(2,4,1,'+');
   ArithmeticOperator *ar_operator3 = new ArithmeticOperator(2,6,1,'x');
   ArithmeticOperator *ar_operator4 = new ArithmeticOperator(2,1,9,'/');
   ArithmeticOperator *ar_operator5 = new ArithmeticOperator(9,4,3,'-');
   ArithmeticOperator *ar_operator6 = new ArithmeticOperator(5,4,3,'/');
   ArithmeticOperator *ar_operator7 = new ArithmeticOperator(5,4,3,'-');
   ArithmeticOperator *ar_operator8 = new ArithmeticOperator(5,2,1,'-');
   ArithmeticOperator *ar_operator9 = new ArithmeticOperator(7,6,1,'/');
   ArithmeticOperator *ar_operator10 = new ArithmeticOperator(5,6,1,'+');


   operator_grid.place_operator(ar_operator1);
   operator_grid.place_operator(ar_operator2);
   operator_grid.place_operator(ar_operator3);
   operator_grid.place_operator(ar_operator4);
   operator_grid.place_operator(ar_operator5);
   operator_grid.place_operator(ar_operator6);
   operator_grid.place_operator(ar_operator7);
   operator_grid.place_operator(ar_operator8);
   operator_grid.place_operator(ar_operator9);
   operator_grid.place_operator(ar_operator10);


   operator_grid.move_operator(1, 1, 'D', 2);
   operator_grid.move_operator(5, 1, 'D', 5);
   operator_grid.move_operator(1, 1, 'D', 2);
   operator_grid.move_operator(2, 4, 'L', 1);
   operator_grid.move_operator(2, 4, 'L', 2);
   operator_grid.move_operator(8, 5, 'L', 3);
   operator_grid.move_operator(1, 7, 'D', 5);
   operator_grid.move_operator(10, 1, 'R', 7);
   operator_grid.move_operator(5, 4, 'U', 3);

   return 0;
}

