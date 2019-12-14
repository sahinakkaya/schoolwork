/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 12.12.2019 */

#include "min_heap.h"

/*
 / I'm creating a binary tree and I'll use vector to store the elements
 / instead of using pointers (left, right, parent etc.) If we index the 
 / tree elements starting from root and visiting each level from left to
 / right, we realize that we can find the index of left child of some node
 / with index i as 2*i + 1, and right child is 2*i + 2 of course. We can
 / similarly calculate the parent index from some node. With that said, I
 / implemented the MinHeap class by looking at Binomial Heaps file from
 / recitation session and writing the logic for the algorithms.
*/

int MinHeap::size() {
    return heap.size();
}

void MinHeap::insert(Event event) {
    heap.push_back(event);
    bubble_up(size() - 1);
}

Event MinHeap::extract_min() {
    if (heap.empty())
        throw "Cannot extract from an empty heap";

    Event e = heap.front();
    heap[0] = heap.at(size() - 1);
    heap.pop_back();
    bubble_down(0);
    return e;
}

/*
 / As long as the node is not a leaf node and it is 
 / bigger than it's children, we're swapping it with
 / its smallest child.
*/
void MinHeap::bubble_down(int index) {
    int left_child_index = left(index);
    int right_child_index = right(index);
    int smallest_child_index = left_child_index;
    if (left_child_index > 0 && right_child_index > 0 && heap[left_child_index] > heap[right_child_index]) {
        smallest_child_index = right_child_index;
    }
    if (smallest_child_index > 0 && heap[index] > heap[smallest_child_index]) {
        Event e = heap[index];
        heap[index] = heap[smallest_child_index];
        heap[smallest_child_index] = e;
        bubble_down(smallest_child_index);
    }
}

int MinHeap::left(int parent_index) {
    int left = 2 * parent_index + 1;
    if (left >= size())
        return -1;
    return left;
}

int MinHeap::right(int parent_index) {
    int right = 2 * parent_index + 2;
    if (right >= size())
        return -1;
    return right;
}

int MinHeap::parent(int child_index) {
    int parent = (child_index - 1) / 2;
    if (child_index == 0)
        return -1;
    return parent;
}

/* 
 / We are extracting the minimum element (root) and as long as
 / the current time is smaller than its time, we are printing:
 / TIME t: NO EVENT
 / Then we are printing the event description and repeating this
 / process until there are no events in the heap

*/
void MinHeap::print_events() {
    int event_time = 1;
    int clock = 1;
    while (!heap.empty()) {
        Event e = extract_min();
        string name = e.get_event_name();
        event_time = e.get_event_time();
        string type = e.get_event_type();
        if (clock < event_time) {
            while (clock != event_time) {
                cout << "TIME " << clock << ": NO EVENT" << endl;
                clock++;
            }
        }
        cout << "TIME " << event_time << ": " << name << " " << type << "ED" << endl;

        clock = event_time + 1;
    }
    cout << "TIME " << event_time << ": "
         << "NO MORE EVENTS, SCHEDULER EXITS" << endl;
}

/*
 / As long as the node is not a root node and it is smaller than
 / its parent, we are swapping it with its parent
*/
void MinHeap::bubble_up(int index) {
    if (index >= 0 && parent(index) >= 0 && heap[parent(index)] > heap[index]) {
        Event temp = heap[index];
        heap[index] = heap[parent(index)];
        heap[parent(index)] = temp;
        bubble_up(parent(index));
    }
}
