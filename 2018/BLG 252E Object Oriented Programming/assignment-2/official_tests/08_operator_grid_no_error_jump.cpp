#include<iostream>
using namespace std;

//#define MAX_OPERATOR_SIZE 50
#include "assignment2.cpp"


int main(){
   OperatorGrid operator_grid(7,7);

   ArithmeticOperator *ar_operator1 = new ArithmeticOperator(2,2,1,'+');
   ArithmeticOperator *ar_operator2 = new ArithmeticOperator(5,3,2,'x');
   ArithmeticOperator *ar_operator3 = new ArithmeticOperator(4,3,2,'/');


   operator_grid.place_operator(ar_operator1);
   operator_grid.place_operator(ar_operator2);
   operator_grid.place_operator(ar_operator3);


   operator_grid.move_operator(5, 3, 'R', 2);
   operator_grid.move_operator(3, 3, 'U', 2);
   operator_grid.move_operator(2, 3, 'D', 1);

   return 0;
}

