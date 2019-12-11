/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 11.12.2019 */

#include <iostream>
#include <fstream>
#include <queue>
#include "event.h"

using namespace std;

class Comparator 
{ 
    public:
        static string compare_behaviour;
        bool operator()(const Event& e1, const Event& e2) 
        {
            if (compare_behaviour.compare("greater"))
                return e1.get_event_time() > e2.get_event_time();
            else
                return e1.get_event_time() >= e2.get_event_time();
        } 

};

string Comparator::compare_behaviour = "greater-than";

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
    priority_queue <Event, vector<Event>, Comparator > pq; 
    while(file >> event_name >> start_time >> end_time){
        Event e1 = Event(event_name, start_time, "START");
        Event e2 = Event(event_name, end_time, "END");
        pq.push(e1);
        pq.push(e2);
    }
    Comparator::compare_behaviour = "greater";
    string name;
    int event_time=0;
    int clock = 1;
    string type;
    while (!pq.empty()) 
    { 

        Event e = pq.top();
        name = e.get_event_name();
        event_time = e.get_event_time();
        type = e.get_event_type();
        if (clock < event_time){
            while (clock != event_time){
                cout << "TIME " << clock << ": NO EVENT" << endl;
                clock++;
            }
        }
        cout << "TIME " << event_time << ": " << name << " " << type << "ED" << endl; 
        pq.pop();
        clock = event_time + 1; 
    }
    cout << "TIME " << event_time << ": " << "NO MORE EVENTS, SCHEDULER EXITS" << endl;
    return EXIT_SUCCESS;

}