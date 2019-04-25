/*
 * runtime.cpp
 *
 *      Author: Şahin Akkaya
 *      Number: 150170098
 */

#include "runtime.h"
#include <iostream>

using namespace std;


template <class T>
void Stack<T>::create() {
    head = NULL;
    nodecount = 0;
};

template <class T>
bool Stack<T>::is_empty() {
    if (head) return false;
    return true;
};

template <class T>
int Stack<T>::get_nodecount() {
    return nodecount;
};

template <class T>
void Stack<T>::push(T array[], int size, const AddressValue lep) {
    Node<T>* newnode = new Node<T>;
    newnode->last_execution_point = lep;
    for (int i = 0; i < size; i++) {
        newnode->variables[i] = array[i];
    }
    newnode->next = head;
    head = newnode;
    nodecount++;
};

template <class T>
Node<T>* Stack<T>::pop() {
    if (!is_empty()) {
        Node<T>* r = head;
        head = head->next;
        nodecount--;
        return r;
    }
    cout << "Warning: Pop from empty stack." << endl;
    return NULL;
};

template <class T>
void Stack<T>::close() {
    Node<T>* d;
    while (head) {
        d = head;
        head = head->next;
        delete d;
        nodecount--;
    }   
};

ScalarValue* get_variable(const string& arg, ScalarValue variables[5]) {
    return &variables[arg[0] - 97];
};

ScalarValue get_value(const string& arg, ScalarValue variables[5]) {
    char first_character = arg[0];
    if ('a' <= first_character && first_character <= 'e') return variables[first_character - 97];
    return stoi(arg);
};

void do_the_math(ScalarValue& arg, ScalarValue val, const string operation) {
    if (operation == "inc") arg += val;
    else if (operation == "dec") arg -= val;
    else if (operation == "mul") arg *= val;
    else if (operation == "div") arg /= val;
    else cerr << "Error: Unknown operation, " << operation << endl;
};

bool created_before = false;

AddressValue executeStatement(const Statement& statement,
                              const AddressValue currentAddress,
                              ScalarValue variables[5],
                              Stack<ScalarValue>& callStack,
                              const AddressValue addressOfCalleeIfCall,
                              bool& isDone) {
    
    // If statement type is a simple arithmetic, do the math.
    if (statement.type == "inc" || statement.type == "dec" ||
        statement.type == "mul" || statement.type == "div") {
            ScalarValue* variable = get_variable(statement.arg1, variables);
            ScalarValue scalar = get_value(statement.arg2, variables);
            do_the_math(*variable, scalar, statement.type);
 
    } else if (statement.type == "call") {
        if (!created_before){      
             callStack.create();          
             created_before = true;
        }

        // Push the contents of caller to callStack
        callStack.push(variables, VARIABLE_COUNT, currentAddress);
        
        // Zero a, b, c, d, e except argument2.
        int arg_index = statement.arg2[0] - 97;
        for (int i = 0; i < VARIABLE_COUNT; i++) {
            if (i != arg_index) 
                variables[i] = 0;
        }
        // Jump to next statement after where function is defined.
        return addressOfCalleeIfCall + 1;

    // If statement type is return 
    } else if (statement.type == "return") {
        if (callStack.is_empty()) {                             // If the stack is empty, we're returning from main.
            cout << variables[statement.arg1[0] - 97] << endl;  // Print the result to the screen
            isDone = true;                                      // Set isDone to true to program to terminate
            callStack.close();                                  // Close the stack
            return 0;
        } else {                                               // Otherwise, we're returning to the caller from calle.
            Node<ScalarValue>* node = callStack.pop();         // Pop contents of the caller from callStack
            int arg_index = statement.arg1[0] - 97;            // Restore a, b, c, d, e except argument1
            for (int i = 0; i < VARIABLE_COUNT; i++) {
                if (i != arg_index) 
                    variables[i] = node->variables[i];
            }
            AddressValue last_executed_line = node->last_execution_point; 
            delete node;
            return last_executed_line + 1;                     // Jump to next statement after where calle is called previously.
        }
    }
    return currentAddress + 1;
}
