#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
#include "Stack.h"

using namespace cop4530;

template<typename T>
Stack<T>::Stack() : vec() {}

template<typename T>
Stack<T>::~Stack() {
    vec.clear(); // Clear elements
}

template<typename T>
Stack<T>::Stack(const Stack<T>& x) : vec(x.vec) {}

template<typename T>
Stack<T>::Stack(Stack<T>&& x) : vec(std::move(x.vec)) {}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& x) {
    if (this != &x) { // Self-assignment check
        vec = x.vec; // Copy the internal vector
    }
    return *this; // Return current object
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& x) {
    if (this != &x) { // Self-assignment check
        vec = std::move(x.vec); // Move the internal vector
    }
    return *this; // Return current object
}

template<typename T>
bool Stack<T>::empty() const {
    return vec.empty();
}

template<typename T>
void Stack<T>::clear() {
    vec.clear(); // Clear internal vector
}

template<typename T>
void Stack<T>::push(const T& x) {
    vec.push_back(x); // Push copy
}

template<typename T>
void Stack<T>::push(T&& x) {
    vec.push_back(std::move(x)); // Push move
}

template<typename T>
void Stack<T>::pop() {
    if (!vec.empty()) {
        vec.pop_back(); // Pop last element
    }
}

template<typename T>
T& Stack<T>::top() {
    return vec.back(); // Return reference to top element
}

template<typename T>
const T& Stack<T>::top() const {
    return vec.back(); // Return const reference to top element
}

template<typename T>
int Stack<T>::size() const {
    return vec.size(); // Return number of elements
}

template<typename T>
void Stack<T>::print(std::ostream& os, char ofc) const {
   for(auto i = vec.begin(); i != vec.end(); i++)
  {
    os << *i;
    os << ofc;
  }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a) {
    a.print(os); // Call print method
    return os; // Return stream
}

template<typename T>
bool operator==(const Stack<T>& a, const Stack<T>& b) {
    return a.getVector() == b.getVector(); // Compare vectors
}

template<typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b) {
    return !(a == b); // Not equal
}

template<typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b) {
    return a.getVector() <= b.getVector(); // Lexicographical comparison
}

template<typename T>
std::vector<T> Stack<T>::getVector() const {
    return vec; // Return copy of vector
}
// namespace cop4530

#endif // STACK_HPP



