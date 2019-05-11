#include "helper_functions.h"
#include <algorithm>

/*
 /brief open files and store them in a map, return true if success false otherwise
 /param file_names an array of strings that holds the name of the files that is going to be opened
 /param length an integer that is equal to number of elements in file_names array
 /files a reference to map object that will keep file_name as a key and ifstream* as a value
 /return true if all files can bo opened succesfully, false otherwise
*/
bool open_files(const string file_names[], int length, map<string, ifstream*>& files) {
    for (int i = 0; i < length; i++) {
        files[file_names[i]] = new ifstream(file_names[i] + ".txt");
        if (files[file_names[i]]->fail()) {
            close_files(file_names, i + 1, files);
            cerr << "Cannot open file '" << file_names[i] << ".txt'. No such file." << endl;
            return false;
        }
    }
    return true;
}

/*
 /brief close files and give back dynamically allocated memory of ifstream pointers
 /param file_names an array of strings that holds the name of the files that is going to be closed
 /param length an integer that is equal to number of files that is going to be closed
 /files a reference to map object that  keeps file_name as a key and ifstream* as a value
*/
void close_files(const string file_names[], int length, map<string, ifstream*>& files) {
    for (int i = 0; i < length; i++) {
        files[file_names[i]]->close();
        delete files[file_names[i]];
    }
}

/*
 /brief split a string with given delimeter and store the results
 /param line a string that is going to be splitted
 /param delim the delimeter according which to split the string
 /param fields a vector<string> reference that keeps result of split operation
 /param max_split maximum number of splits to do. -1 (the default value) means no limit.
*/
void split(string line, string delim, vector<string>& fields, int max_split) {
    int first = 0, last = 0;
    for (int i = 0; i < max_split || max_split == -1; i++) {
        last = line.find(delim, first);
        fields.push_back(line.substr(first, last - first));
        if (first > last) {
            break;
        }
        first = last + delim.length();
    }
}

/*
 /brief check whether a string is inside a vector or not.
 /param v a vector<string> reference
 /param t a string
 /return true if vector contains the string, false otherwise
*/
bool vector_contains(const vector<string>& v, string& t) {
    bool found = (std::find(v.begin(), v.end(), t) != v.end());
    return found;
}

/*
 /brief concatenate elements of a vector with given string
 /param join_with a string that will be used to concatenate elements of vector
 /param v a vector<string> reference
 /begin an integer that shows the starting index of the concatenation operation, default 0
 /end an integer that shows the ending index of the concatenation operation, default -1 which means until the very end
 /return concatenated string
*/
string join(string join_with, vector<string>& v, int begin, int end) {
    string s = "";
    if (end == -1)
        end = (int)v.size();
    for (int i = begin; i < end; i++) {
        s += join_with + v[i];
    }
    return s.substr(1, s.length() - 1);
}