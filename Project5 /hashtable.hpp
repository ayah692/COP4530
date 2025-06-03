#include "hashtable.h"

using namespace cop4530;

// Constructor
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size) 
        : table(prime_below(size)) {
    current_size = 0;
}

// Destructor
template <typename K, typename V>
HashTable<K, V>::~HashTable() {
    clear();
}

// Check if the key exists
template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) const {
    auto & whichList = table[myhash(k)];
    for (const auto & thisPair : whichList) {
        if (thisPair.first == k)
            return true;
    }
    return false;
}

// Check if the key-value pair exists
template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const {
    auto & whichList = table[myhash(kv.first)];
    for (auto & thisPair : whichList) {
        if (thisPair == kv)
            return true;
    }
    return false;
}


// Insert key-value pair
template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv) {
    auto & whichList = table[myhash(kv.first)];
    for (auto & thisPair : whichList) {
        if (thisPair.first == kv.first) {
            if (thisPair.second == kv.second)
                return false;
            thisPair.second = kv.second;
            return true;
        }
    }
    whichList.push_back(kv);
    if (++current_size > table.size())
        rehash();
        
    return true;
}


// Move version of insert
template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> && kv) {
    auto & whichList = table[myhash(kv.first)];
    for (auto & thisPair : whichList) {
        if (thisPair.first == kv.first) {
            if (thisPair.second == kv.second)
                return false;
            thisPair.second = std::move(kv.second);
            return true;
        }
    }
    whichList.push_back(std::move(kv));
    if (++current_size > table.size())
        rehash();
        
    return true;
}

// Remove key
template <typename K, typename V>
bool HashTable<K, V>::remove(const K &k) {
    auto &list = table[myhash(k)];
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->first == k) {
            list.erase(it);
            --current_size;
            return true;
        }
    }
    return false;
}

// Clear the hash table
template <typename K, typename V>
void HashTable<K, V>::clear() {
    makeEmpty();
}

// Load from file
template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
    std::ifstream infile(filename);
    if (!infile) 
        return false;

    K key;
    V value;
    while (infile >> key >> value) {
        insert(std::make_pair(key, value));
    }
    return true;
}

// Dump the hash table
template <typename K, typename V>
void HashTable<K, V>::dump() const {
    for (size_t i = 0; i < table.size(); ++i) {
            std::cout << "v[" << i << "]: ";
            for (auto & kv : table[i]) {
                std::cout << kv.first << ": " << kv.second << ".";
            }
            std::cout << std::endl;
        }
    }



// Return the number of elements
template <typename K, typename V>
size_t HashTable<K, V>::size() const {
    return current_size;
}

// Write to file
template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) const {
    std::ofstream outfile(filename);
    if (!outfile) 
        return false;

    for (const auto &list : table) {
        for (const auto &item : list) {
            outfile << item.first << " " << item.second << ::endl;
        }
    }
    return true;
}

// Make the table empty
template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
    for (auto &list : table) 
        list.clear();
    current_size = 0;
}

// Rehash the table
template <typename K, typename V>
void HashTable<K, V>::rehash() {
    auto oldTable = table;
    table.resize(prime_below(2 * table.size()));
    for (auto &list : table) 
        list.clear();

    current_size = 0;
    for (auto &list : oldTable) {
        for (auto &item : list) 
            insert(std::move(item));
    }
}

// Hash function
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const {
    static std::hash<K> hf;
    return hf(k) % table.size();
}


//below are given function
// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

