#include <iostream>
#include <fstream>
#include <map>

using namespace std;

bool open_files(const string file_names[], int length, map <string, ifstream*>& files);
void close_files(const string file_names[], int length, map <string, ifstream*>& files);

int main(){
    string file_names[] = {"stock", "menu", "order"};
    map <string, ifstream*> files;
    if(!open_files(file_names, 3, files)) // If cannot open any of the files
        return EXIT_FAILURE;
    
    



    close_files(file_names, 3, files);
    return EXIT_SUCCESS;

}



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