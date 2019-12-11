/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 11.12.2019 */

#ifndef EVENT_H
#define EVENT_H

#include <iostream>

using namespace std;
class Event 
{ 
    private:
        string event_name; 
        int event_time;
        string event_type;
    public:
        Event(string , int, string);
        string get_event_name() const;
        
        int get_event_time() const;
        string get_event_type() const;
}; 
#endif