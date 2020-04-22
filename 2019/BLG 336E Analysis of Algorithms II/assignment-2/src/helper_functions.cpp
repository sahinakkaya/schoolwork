#include <iostream>
#include <iomanip>
using namespace std;

int** allocate_matrix(int node_count){
    int** m = new int*[node_count];
    for(int i = 0; i < node_count; ++i) {
        m[i] = new int[node_count];
        for(int j = 0; j<node_count;j++)
            m[i][j] = 0;
    }
    return m;
}

void print_matrix(int** matrix, int length){
    cout << "   ";
    for(int i =0;i<length;i++)
        cout<<setw(3)<<setfill(' ') <<i;
    cout << endl;
    for(int i =0;i<length;i++){
        cout  << setw(3)<<setfill(' ') <<i;
        for(int j=0; j<length;j++){
            cout << setw(3)<<setfill(' ') <<matrix[i][j];
        }
        cout << endl;
    }
}

