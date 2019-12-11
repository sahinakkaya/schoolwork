/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 11.12.2019 */

#include <iostream>
#include <fstream>
#include <queue>
#include "event.h"


class Sorter 
{ 
    public:
        bool operator()(const Event& e1, const Event& e2) 
        {
            return e1.get_event_time() > e2.get_event_time();
        } 

}; 

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

    string event_name;
    int start_time;
    int end_time;
    priority_queue <Event, vector<Event>, Sorter > pq; 
    while(file >> event_name >> start_time >> end_time){
        Event e1 = Event(event_name, start_time, "START");
        Event e2 = Event(event_name, end_time, "END");
        pq.push(e1);
        pq.push(e2);
    }

    return EXIT_SUCCESS;

}