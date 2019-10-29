/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 27.10.2019 */

#include "sorting_algorithms.h"

#include <vector>
#include <iostream>

using namespace std;

void merge(vector<int> &a, int low, int mid, int high)
{
    int k = low;
    int i = low;
    int j = mid + 1;
    vector<int> b;
    while (k <= mid && j <= high)
    {
        if (a[k] <= a[j])
        {
            b.push_back(a[k]);
            k = k + 1;
        }
        else
        {
            b.push_back(a[j]);
            j++;
        }
        i++;
    }
    if (k > mid)
    {
        for (int h = j; h <= high; h++)
        {
            b.push_back(a[h]);
            i++;
        }
    }
    else
    {
        for (int h = k; h <= mid; h++)
        {
            b.push_back(a[h]);
            i++;
        }
    }
    for (int h = low; h <= high; h++)
    {
        a[h] = b[h-low];
    }
}

void merge_sort(vector<int> &A, int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
};

void bubble_sort(vector<int> &A)
{
    int i = A.size();
    bool sorted = false;
    while (i > 1 && !sorted)
    {
        sorted = true;
        for (int j = 1; j < i; j++)
        {
            if (A[j] < A[j - 1])
            {
                int temp = A[j - 1];
                A[j - 1] = A[j];
                A[j] = temp;
                sorted = false;
            }
        }
        i--;
    }
};
