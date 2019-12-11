/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 11.12.2019 */

#include <iostream>
#include <fstream>


using namespace std;
int main(int argc, char *argv[]){
    if (argc != 2)
    {
        cerr << "You entered " << argc << " argument" << (argc == 1 ? "" : "s") << "." << endl;
        cerr << "Please enter exactly 2 arguments." << endl;
        return EXIT_FAILURE;
    }

    string filename = argv[1];
    ifstream file(filename);
    if (file.fail())
    { // If cannot opened,
        cerr << "Cannot open file '" << filename << "'. No such file." << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}