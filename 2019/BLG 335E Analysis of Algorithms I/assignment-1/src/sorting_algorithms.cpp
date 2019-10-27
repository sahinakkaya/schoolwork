#include "sorting_algorithms.h"

#include <vector>
#include <iostream>

using namespace std;

void merge_sort(vector<int>& v){
    cout << "merge" << endl;
};

void bubble_sort(vector<int>& v){
    int i = v.size();
    bool sorted = false;
    while (i>1 && !sorted){
        sorted = true;
        for(int j = 1; j<i; j++){
            if (v[j] < v[j-1]){
                int temp = v[j-1];
                v[j-1] = v[j];
                v[j] = temp;
                sorted = false;
            }
        }
        i--;
    }
};
