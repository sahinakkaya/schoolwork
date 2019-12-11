#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "event.h"
#include <vector>
class MinHeap{
    private:
        vector <Event> heap;
        int left(int);
        int right(int);
        int parent(int);
        void bubble_up(int);
        void bubble_down(int);
    public:
        MinHeap() {};
        void insert(Event event);
        Event extract_min();
        void print_events();
        int size();
    
};


#endif