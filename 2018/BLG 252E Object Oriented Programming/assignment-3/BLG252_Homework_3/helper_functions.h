#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include <iostream>
#include <vector>
using namespace std;


void split(string line, string delim, vector<string>& fields, int num_of_fields);

bool vector_contains(const vector<string>& v, string& t);

string join(string join_with, vector<string>& v, int begin = 0, int end = -1);
#endif