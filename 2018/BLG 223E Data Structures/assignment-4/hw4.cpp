#include <iostream>
#include <fstream>
using namespace std;


struct Node{
    int data;
    Node* next;
};

struct queueAnt{
    Node* front;
    Node* back;
    queueAnt();
    void enqueue(int);
    int dequeue();
    void print();
    bool is_empty();
    void close();
};

struct stackAnt{
    Node* head;
    stackAnt();
    bool is_empty();
    void push(int);
    int pop();
    void close();

};
struct Ants {
    queueAnt ants ;
    queueAnt holeDepths ;
    stackAnt hole ;
    void ReadFile ( char *);
    void ShowContents ( bool );
    void CrossRoad ();
    void close();
};

/*
  /brief initialize the stack
*/ 
stackAnt::stackAnt(){
    head = NULL;
}

/*
  /return true if stack is empty, false otherwise
*/
bool stackAnt::is_empty() {
    return !head;
};


/*
  /brief add given data to the stack as a top element
  /param data an integer that holds ant number
*/
void stackAnt::push(int data) {
    Node* newnode = new Node;
    newnode->data = data;
    newnode->next = head;
    head = newnode;
};

/*
  /brief remove the top element from stack and return it's data
  /return data of the top element
*/
int stackAnt::pop() {
    Node* node = head;
    int data = node->data;
    head = head->next;
    delete node;
    return data;
};

/*
  /brief remove all elements in the stack
*/
void stackAnt::close() {
    Node* d;
    while(head){
        d = head;
        head = head->next;
        delete d;
    }   
};

/*
  /brief initialize the queue
*/ 
queueAnt::queueAnt(){
    front = NULL;
    back = NULL;
};

/*
  /return true if queue is empty, false otherwise
*/
bool queueAnt::is_empty(){
    return front == NULL;
};

/*
  /brief add given data to the queue as a back element
  /param data an integer that is going to queued
*/
void queueAnt::enqueue(int data){
    Node* newnode = new Node;
    newnode->data = data;
    newnode->next = NULL;
    if ( is_empty() ) {
        back = newnode;
        front = back;
    } else {
        back->next = newnode;
        back = newnode;
    }
};

/*
  /brief remove the front element from queue and return it's data
  /return data of the front element
*/
int queueAnt::dequeue(){
    if(is_empty()){
        cerr << "Warning: Dequeueing from empty queue." <<endl;
    }
    Node* t = front;
    front = front->next;
    int data = t->data;
    delete t;
    return data;
};

/*
  /brief print the contents of the queue
*/
void queueAnt::print(){
    Node* t = front;

    while(t){
        cout << t->data<< " ";
        t = t->next;
    }
};

/*
  /brief remove all elements in the queue
*/
void queueAnt::close(){
    Node* t;
    while(front){
        t = front;
        front = front->next;
        delete t;
    }
};

/*
  /brief read data from file and initialize the queues.
  /param filename a character pointer to a file that is going to be read
*/
void Ants::ReadFile(char* filename){
    // Initialize stacks.

    // Open file...
    ifstream file(filename);
    
    if(file.fail()){ // If cannot opened,
        cerr << "Cannot open file '" << filename << "'. No such file." << endl;
        return;
    }
    
    int number_of_ants;
    file >> number_of_ants;

    for(int i = 1; i<=number_of_ants; i++){
        ants.enqueue(i);
    }

    int hole_depth;

    // Prepare table deck
    while(file>>hole_depth){
        holeDepths.enqueue(hole_depth);
    }
    file.close();
};

/*
  /brief print the contents of the queues
  /param ant if true ants queue will be printed, otherwise hole depths will be printed
*/
void Ants::ShowContents(bool ant){
    if(ant){
        ants.print();
    }else {
        holeDepths.print();
    }
    cout <<endl;

};

void Ants::CrossRoad(){
    while(!holeDepths.is_empty()){             // As long as there are hole(s),
        int hole_depth = holeDepths.dequeue(); // Get next hole depth.
        for(int i = 0;i<hole_depth;i++){       
            hole.push(ants.dequeue());         // put the hole depth ants to the hole
        }
        while(!hole.is_empty())                // as long as there are ant(s) in the hole
            ants.enqueue(hole.pop());          // pick it up and add it to queue 
    }

};
/*
  /brief close all containers in the struct
*/
void Ants::close(){
    ants.close();
    hole.close();
    holeDepths.close();
};

int main ( int argc , char * argv[] ){
    Ants a ;
    a . ReadFile ( argv [1]); // store the number of ants and depths of holes
    cout << " The initial Ant sequence is: " ;
    a . ShowContents (1); // list ant sequence ( initially : 1 , 2 , ... , N )
    cout << " The depth of holes are: " ;
    a . ShowContents (0); // list depth of holes
    a . CrossRoad ();
    cout << " The final Ant sequence is: " ;
    a . ShowContents (1);
    a . close();
    return 0;
}
