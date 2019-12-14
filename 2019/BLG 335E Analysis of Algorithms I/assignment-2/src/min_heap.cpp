/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 12.12.2019 */

#include "min_heap.h"

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

void MinHeap::bubble_down(int index) {
    int left_child = left(index);
    int right_child = right(index);
    if (left_child >= 0 && right_child >= 0 && heap[left_child] > heap[right_child]) {
        left_child = right_child;
    }
    if (left_child > 0 && heap[index] > heap[left_child]) {
        Event e = heap[index];
        heap[index] = heap[left_child];
        heap[left_child] = e;
        bubble_down(left_child);
    }
}

int MinHeap::left(int parent_index) {
    int left = 2 * parent_index + 1;
    if (left < size())
        return left;
    return -1;
}

int MinHeap::right(int parent_index) {
    int right = 2 * parent_index + 2;
    if (right < size())
        return right;
    return -1;
}

int MinHeap::parent(int child_index) {
    int parent = (child_index - 1) / 2;
    if (child_index == 0)
        return -1;
    return parent;
}

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

void MinHeap::bubble_up(int index) {
    if (index >= 0 && parent(index) >= 0 && heap[parent(index)] > heap[index]) {
        Event temp = heap[index];
        heap[index] = heap[parent(index)];
        heap[parent(index)] = temp;
        bubble_up(parent(index));
    }
}
