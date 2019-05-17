#include<iostream>
using namespace std;

//#define MAX_OPERATOR_SIZE 50
#include "assignment2.cpp"


int main(){
   Operator operator1(1,2,3);

   cout << "X=" << operator1.get_x() << " Y=" << operator1.get_y() << " SIZE=" << operator1.get_size() << endl; 

   return 0;
}

