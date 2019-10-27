/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 27.10.2019 */

#include "sorting_algorithms.h"

#include <vector>
#include <iostream>

using namespace std;

void merge_sort(vector<int>& A){
    cout << "merge" << endl;
};

void bubble_sort(vector<int>& A){
    int i = A.size();
    bool sorted = false;
    while (i>1 && !sorted){
        sorted = true;
        for(int j = 1; j<i; j++){
            if (A[j] < A[j-1]){
                int temp = A[j-1];
                A[j-1] = A[j];
                A[j] = temp;
                sorted = false;
            }
        }
        i--;
    }
};
