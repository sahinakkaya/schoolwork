#include "helper_functions.h"
void split(string line, string delim, vector<string>& fields, int num_of_fields){
    int first = 0, last = 0;
    //cout << line << endl;
    for(int i = 0; i<num_of_fields;i++){
        last = line.find(delim, first);
        fields.push_back(line.substr(first, last-first));
        //cout << line.substr(first, last-first) << endl;
        cout << "first:" << first << " last: "<< last << endl;
        if(first>last){
            break;
        }
        first = last+delim.length();
        
        
    }
}