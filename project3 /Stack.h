#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
namespace cop4530{

 template<typename T>   
   class Stack
   {
        public:
           Stack(); //zero srgu constructor
           ~Stack(); //destructor
           Stack (const Stack<T>&);  //copy constructor
           Stack(Stack<T> &&x); //move constructor.
           Stack<T>& operator= (const Stack <T>&x);// copy assignment operator=.
       Stack<T> & operator=(Stack<T> &&);// move assignment operator=
           bool empty() const; //returns true if the Stack contains no elements, and false otherwise.  
           void clear();// delete all elements from the stack.
           void push(const T& x); //adds x to the  stack copy version
           void push(T&& x);// adds x to the stack move version
           void pop(); //removes the most recently added element of the stack
           T & top(); //mutator
          const T& top() const; // accessor
          int size() const; // returns the number of elements stored in the Stack.
          void print(std::ostream& os, char ofc = ' ') const;
          std::vector<T> getVector() const;



         private:
                std::vector<T> vec;

};

#include "Stack.hpp"
//non-member global functions
template<typename T>    
 std::ostream& operator<< (std::ostream& os, const Stack<T>& a); //invokes the print() method to print the Stack<T> a in the specified ostream   

template<typename T>    
bool operator== (const Stack<T>& a, const Stack <T>&b); //return true

template<typename T>    
 bool operator!= (const Stack<T>& a, const Stack <T>& b); //return f

 template<typename T>   
bool operator<=(const Stack<T>& a, const Stack <T>& b);
}
 //namespace cop4530

#endif

