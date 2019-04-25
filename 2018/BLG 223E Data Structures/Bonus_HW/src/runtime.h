/*
 * runtime.h
 *
 *      Author: Şahin Akkaya
 *      Number: 150170098
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

#define VARIABLE_COUNT 5
#include <string>
#include <iostream>

struct Statement {
    std::string type;
    std::string arg1;
    std::string arg2;
};

typedef unsigned AddressValue;
typedef int ScalarValue;

template <typename T>
class Node {
   public:
    T variables[5];
    AddressValue last_execution_point;
    Node* next;
};

template <typename T>
class Stack {
    Node<T>* head;
    int nodecount;

   public:
    void create();
    bool is_empty();
    int get_nodecount();
    void push(T[], int, const AddressValue);
    Node<T>* pop();
    void close();
};

AddressValue executeStatement(const Statement& statement,
                              const AddressValue currentAddress,
                              ScalarValue variables[5],
                              Stack<ScalarValue>& callStack,
                              const AddressValue addressOfCalleeIfCall,
                              bool& isDone);

ScalarValue get_value(const std::string&, ScalarValue variables[5]);
ScalarValue* get_variable(const std::string&, ScalarValue variables[5]);
void do_the_math(ScalarValue&, ScalarValue, const std::string);
#endif /* RUNTIME_H_ */
