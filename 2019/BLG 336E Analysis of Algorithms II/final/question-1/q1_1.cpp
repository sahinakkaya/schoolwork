#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void print_arr(vector<int>& arr, int first, int last)
{
    for (int i = first; i <= last; i++)
    {
        string if_eol = (i == last) ? "\n" : ", ";

        cout << arr[i] << if_eol;
    }
}
void merge(vector<int>& arr, int first, int mid, int dummy, int last){
    int i = first, j = mid + 1;
    vector<int> temp;
    while(i<=mid and j<=last){
        if (arr[i]<arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }
    while (i<=mid)
        temp.push_back(arr[i++]);
    while (j<=last)
        temp.push_back(arr[j++]);
    i = first, j=0;
    while(i<=last)
        arr[i++] = temp[j++];
}

void func(vector<int>& arr, int first, int last)
{
    print_arr(arr, first, last);
    int k = first, m, x;
    while(k<last){
        if (arr[k]>arr[k+1]){
            int temp = arr[k];
            arr[k] = arr[k+1];
            arr[k+1] = temp;
        }
        k += 2;
    }
    k = first + 1;
    vector<int> A;
    while (k<=last){
        A.push_back(arr[k]);
        k += 2;
    }
    x = first;
    k = first;
    while (k<=last)
    {
        arr[x] = arr[k];
        x += 1;
        k += 2;
    }
    k = 0;
    m = (int) A.size();
    while(k<m)
        arr[x++] = A[k++];
}

void sort(vector<int>& arr, int first, int last)
{
    int n = last - first + 1;
    if (n <= 1)
        return;
    if (first < last){
        func(arr, first, last);
        int mid = (first + last)/2;
        sort(arr, first, mid);
        sort(arr, mid+1, last);
        merge(arr, first, mid, mid + 1, last);
    } 
    
}

int main(int argc, char *argv[])
{

    vector<int> all_values;


    try {
        
        string filename = argv[1];

        ifstream myfile(filename);

        
        if (myfile.is_open())
        {
            string line;
            while (getline(myfile, line))
            {
                int number = stoi(line);
                all_values.push_back(number);
            }
            sort(all_values, 0, all_values.size() - 1);

            print_arr(all_values, 0, all_values.size() - 1);
        }
        else
        {
            cout << "File is not available." << endl;
            throw;
        }

    }
    catch (const ifstream::failure& e)
    {
        cerr << "Exception opening the file!" << endl;
        return -1;
    }
    catch (...)
    {
        cerr << "Something's wrong!" << endl;
        return -1;
    }



    return 0;
}