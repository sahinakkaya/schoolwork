/*
 * main.cpp
 *
 *      Author: Şahin Akkaya
 *      Number: 150170098
 */
#include <fstream>
#include <iostream>
#include <list>
#include <regex>
#include <string>
#include "polynomial.h"
#include "vector.h"

using namespace std;

void print_as_superscript(int power){
  map<int, string> fancy_powers = {{0,"⁰"},{1,"¹"},{2,"²"},{3,"³"},{4,"⁴"},{5,"⁵"},{6,"⁶"},{7,"⁷"},{8,"⁸"},{9,"⁹"}};
  string s = "";
  while (power>0){
    s = fancy_powers[power%10] + s;
    power /= 10;
  }
  cout << s;
}

ostream& operator<<(ostream& os, Polynomial& pin) {
  for (int j = 0; j < pin.get_degree() + 1; j++) {
    double coefficent = pin.get_content(j);
    int power = pin.get_degree() - j;
    if (coefficent!=0){
      if(j!=0){
        if(coefficent>0) cout << " + ";
        else cout << " -";
      }else if (coefficent<0) cout << "-";
      if (abs(coefficent) != 1 || power == 0) cout << abs(coefficent);
      if (power >= 1){
          cout << "x";
          if (power > 1)
            print_as_superscript(power);
      }
    }
  }
  return os;
}

ostream& operator<<(ostream& os, Vector& vin) {
  cout << "(";
  for (int j = 0; j < vin.get_size(); j++) {
    if (j > 0)
      cout << ", ";
    cout << vin.get_content(j);
  }
  cout << ")";
  return os;
}

/*
 / Prompt user and get input, if input is valid return it to 
 the caller function, otherwise show an error message
*/
string input(const string& s) {
  cout << "Which " << s << " operation would you like to do?(+: addition, ";
  cout << "*: " << (s == "vector" ? "scalar " : "") << "multiplication";
  cout << (s == "vector" ? ", .: dot product" : "") << "):" << endl;
  string x;
  cin.ignore();
  getline(cin, x);
  regex vector_r("\\s*\\d+\\s*[.*+]\\s*-?\\d+(.\\d+)?\\s*");
  regex polynomial_r("\\s*\\d+\\s*[+*]\\s*\\d+\\s*");
  if (s == "vector") {
    if (regex_match(x, vector_r)) return x;
  } else if (regex_match(x, polynomial_r))
    return x;
  cerr << "The operation you entered is not valid for " << s << "s. Skipping..." << endl;
  return "";
}

void print_possible_actions() {
  cout << endl
       << endl
       << "Possible Actions:" << endl;
  cout << "1. Print Polynomial and Vector lists" << endl;
  cout << "2. Do a polynomial operation" << endl;
  cout << "3. Do a vector operation" << endl;
  cout << "4. Help: Print possible actions" << endl;
  cout << "0. Exit the program" << endl
       << endl;
}
template <typename T>
void find_operands(const string& s, list<T*>& input_list, T& first_operand, 
                  T& second_operand, char& op, double& scalar1, double& scalar2) {
  regex fields("\\s*(\\d+)\\s*([.*+])\\s*(-?\\d+(.\\d+)?)\\s*");
  smatch items;
  regex_match(s.cbegin(), s.cend(), items, fields);
  typename list<T*>::iterator it;
  for (it = input_list.begin(); it != input_list.end(); it++) {
    if ((*it)->get_id() == stoi(items[1]))
      first_operand = **it;
    if ((*it)->get_id() == stoi(items[3]))
      second_operand = **it;
  }
  op = string(items[2])[0];
  scalar1 = stod(items[1]);
  scalar2 = stod(items[3]);
}

void print_result(const string& s, list<Polynomial*>& polynomial_list){
  Polynomial first, second;
  char operation;
  double first_scalar,second_scalar;
  int list_size =  polynomial_list.size();
  find_operands(s, polynomial_list, first, second, operation, first_scalar,second_scalar);
  if(first_scalar>list_size || second_scalar >list_size){
    cerr << "Polynomials does not present. Skipping..."<<endl;
    return;
  }
  Polynomial result;
  if(operation=='+')
    result = first + second;
  else if(operation=='*')
    result = first*second;
  cout << "("<<first<< ") "<< operation<<" (" << second << ") = " << result << endl;
}

void print_result(const string& s, list<Vector*>& vector_list) {
  Vector first, second;
  char operation;
  double first_scalar,second_scalar;
  int list_size =  vector_list.size();
  find_operands(s, vector_list, first, second, operation, first_scalar,second_scalar);
  if (operation=='+'||operation=='.'){
    if(first_scalar>list_size || first_scalar<0 || second_scalar >list_size || second_scalar <0 ){
    cerr << "Vectors does not present. Skipping..."<<endl;
    return;
    }
  }else{
    if(first_scalar>list_size || first_scalar<0){
    cerr << "Vectors does not present. Skipping..."<<endl;
    return;
    }
  }
  Vector result;
  try {
    if (operation == '+') {
      result = first + second;
      cout << first << " + " << second << " = " << result << endl;
    } else if (operation == '*') {
      result = first * second_scalar;
      cout << first << " * " << second_scalar << " = " << result << endl;
    } else if (operation == '.') {
      double result = first*second;
      cout << first << " . " << second << " = " << result << endl;
    }
  } catch (const char* msg) {
    cerr << msg << endl;
  }
  cout << endl;
}

template <typename T>
void print(list<T*>& vl) {
  typename list<T*>::iterator it;
  for (it = vl.begin(); it != vl.end(); it++) {
    cout << (*it)->get_id() << ". " << **it << endl;
  }
  cout << endl;
}

bool perform_operation(int& option, list<Vector*>& vectorlist, list<Polynomial*>& polynomiallist) {
  switch (option) {
    case 1:  { // Print Polynomial and Vector lists
      cout << "Vectors:" << endl;
      print(vectorlist);
      cout << "Polynomials:" << endl;
      print(polynomiallist);
      return false;
    }
    case 2: { // Do a polynomial operation
      string operation = input("polynomial");
      if (operation != "") print_result(operation, polynomiallist);
      return false;
    }
    case 3: {  // Do a vector operation
      string operation = input("vector");
      if (operation != "") print_result(operation, vectorlist);
      return false;
    }
    case 4:
      print_possible_actions();
      return false;
    case 0: // return true in order to exit program
      return true;
    default:
      cout << "Invalid option. Skipping... Press '4' to see possible actions. " << endl;
      return false;
  }
}

int main() {
  // Open files...

  ifstream file_v("Vector.txt");

  if (file_v.fail()) { // If cannot opened,
    cerr << "Cannot open file 'Vector.txt'. No such file." << endl;
    return EXIT_FAILURE;
  }

  ifstream file_p("Polynomial.txt");

  if (file_p.fail()) { // If cannot opened,
    cerr << "Cannot open file 'Polynomial.txt'. No such file." << endl;
    return EXIT_FAILURE;
  }
  // Read file and initalize the vector list
  int number_of_lines, size, degree;
  file_v >> number_of_lines;
  list<Vector*> vectors;
  for (int i = 0; i < number_of_lines; i++) {
    file_v >> size;
    double* contents = new double[size];
    for (int j = 0; j < size; j++)
      file_v >> contents[j];
    Vector* v = new Vector(size, contents);
    delete contents;
    vectors.push_back(v);
  }
  file_v.close();

  // Read file and initalize the polynomial list
  file_p >> number_of_lines;
  list<Polynomial*> polynomials;
  for (int i = 0; i < number_of_lines; i++) {
    file_p >> degree;
    double* contents = new double[degree + 1];
    for (int j = 0; j <= degree; j++) {
      file_p >> contents[j];
    }
    Polynomial* p = new Polynomial(degree, contents);
    delete contents;
    polynomials.push_back(p);
  }
  file_p.close();


  cout << "Polynomial and Vector List Program!" << endl;
  cout << "Polynomials and Vectors are read from text files!" << endl;
  print_possible_actions();
  bool end = false;
  int option = 0;

  while (!end) {
    cout << "Enter an option: ";
    cin >> option;
    end = perform_operation(option, vectors, polynomials);
  }


  // Deallocate memory to prevent memory leak
  list<Vector*>::iterator it;
  for (it = vectors.begin(); it != vectors.end(); it++) delete *it;

  list<Polynomial*>::iterator that;
  for (that = polynomials.begin(); that != polynomials.end(); that++) delete *that;

  return EXIT_SUCCESS;
}