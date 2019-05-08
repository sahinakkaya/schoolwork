#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

bool open_files(const string file_names[], int length, map <string, ifstream*>& files);
void close_files(const string file_names[], int length, map <string, ifstream*>& files);

void split(string line, string delim, vector<string>& fields, int num_of_fields);

bool vector_contains(const vector<string>& v, string& t);

string join(string join_with, vector<string>& v, int begin = 0, int end = -1);
#endif