/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 25.10.2019 */

#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>
#include "sorting_algorithms.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cerr << "You entered " << argc << " argument" << (argc == 1 ? "" : "s") << "." << endl;
        cerr << "Please enter exactly 4 arguments." << endl;
        return EXIT_FAILURE;
    }

    char algorithm_type = argv[1][0];
    try
    {
        if (algorithm_type != 'b' && algorithm_type != 'm')
            throw algorithm_type;
    }
    catch (char e)
    {
        cerr << "Algorithm type should be 'b' or 'm'." << endl
             << "You entered " << e << "." << endl;
        return EXIT_FAILURE;
    }
    int num_of_integers;
    try
    {
        num_of_integers = stoi(argv[2]);
        if (num_of_integers <= 0)
            throw num_of_integers;
    }
    catch (invalid_argument e)
    {
        cerr << "Third argument should be integer." << endl;
        cerr << argv[2] << " is not an integer." << endl;
        return EXIT_FAILURE;
    }
    catch (int e)
    {
        cerr << "Total number of integers should be positive. " << endl
             << "You entered " << e << "." << endl;
        return EXIT_FAILURE;
    }
    string filename = argv[3];

    // Open file...
    ifstream file(filename);

    if (file.fail())
    { // If cannot opened,
        cerr << "Cannot open file '" << filename << "'. No such file." << endl;
        return EXIT_FAILURE;
    }

    vector<int> numbers;

    int number;
    while (num_of_integers--)
    {
        file >> number;
        cout << number << ", ";
        numbers.push_back(number);
    }

    if (algorithm_type == 'b')
        bubble_sort(numbers);
    else
        merge_sort(numbers);
}