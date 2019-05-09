#include "helper_functions.h"
#include <algorithm>


bool open_files(const string file_names[], int length, map <string, ifstream*>& files){
    for(int i = 0; i<length;i++){
        files[file_names[i]] = new ifstream(file_names[i] + ".txt");
        if(files[file_names[i]]->fail()){
            close_files(file_names, i+1, files);
            cerr << "Cannot open file '" << file_names[i] << ".txt'. No such file." << endl;
            return false;
        }
    }
    return true;
}

void close_files(const string file_names[], int length, map <string, ifstream*>& files){
    for(int i = 0; i<length;i++){
        files[file_names[i]]->close();
        delete files[file_names[i]];
    }
}

void split(string line, string delim, vector<string>& fields, int num_of_fields){
    int first = 0, last = 0;
    for(int i = 0; i< num_of_fields || num_of_fields == -1;i++){
        last = line.find(delim, first);
        fields.push_back(line.substr(first, last-first));
        if(first>last){
            break;
        }
        first = last+delim.length();
        
        
    }
}

bool vector_contains(const vector<string>& v, string& t)
{
    bool found = (std::find(v.begin(), v.end(), t) != v.end());
    return found;
}

string join(string join_with, vector<string>& v, int begin, int end){
    string s = "";
    if(end == -1)
        end = (int) v.size();
    for(int i = begin; i< end; i++){
        s += join_with + v[i];
    }
    return s.substr(1,s.length()-1);
}