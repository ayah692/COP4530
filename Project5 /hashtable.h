#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>
#include <utility>
#include <functional>
#include <fstream>
#include <iostream>

using namespace std;
namespace cop4530 {

template <typename K, typename V>
class HashTable {
    public:

        HashTable(size_t size = 101);  // Constructor
        ~HashTable();                                       // Destructor

        bool contains(const K &k) const;
        bool match(const std::pair<K, V> &kv) const;
        bool insert(const std::pair<K, V> &kv);
        bool insert(std::pair<K, V> &&kv);
        bool remove(const K &k);
        void clear();
        bool load(const char *filename);
        void dump() const;
        size_t size() const;
        bool write_to_file(const char *filename) const;

private:
    void makeEmpty();
    void rehash();
    size_t myhash(const K &k) const;

    unsigned long prime_below(unsigned long n) ;
    void setPrimes(std::vector<unsigned long> &vprimes);

    std::vector<std::list<std::pair<K, V>>> table;
    size_t current_size;
    // Constants
    static const unsigned int max_prime = 1301081;
    static const unsigned int default_capacity = 101;
};

#include "hashtable.hpp"  // Include the implementation
}  // namespace cop4530

#endif
