# Project 5: Hash Tables and Password Server

**Course:** COP4530 – Data Structures  
**Student:** Ayah Halloum  
**Due Date:** 12/04/2024  
**Extra Credit:** Hidden password input (`sproj5.cpp`)

---

## Project Overview

This project implements a **generic hash table** in C++ using templates and STL containers, and builds a **secure password server** system that encrypts user passwords, simulating a real-world login system. 

It is divided into:
- A `HashTable` class template with separate chaining
- A `PassServer` class that acts as an adaptor
- A menu-driven client for managing users
- An extra credit version with hidden password input

---

##  Key Skills Demonstrated

- Implemented a `HashTable<K, V>` with separate chaining (`vector<list<pair<K, V>>>`)
- Developed an `PassServer` adaptor to manage usernames and encrypted passwords
- Used GNU `crypt()` for secure MD5-based password encryption
- Designed and built reusable class templates with STL
- Handled user sessions, I/O, password validation, and memory management
- Analyzed time complexity of `rehash()` and `removeUser()` operations

---

## Files Included

| File | Description |
|------|-------------|
| `hashtable.h` | HashTable class declaration |
| `hashtable.hpp` | HashTable implementation |
| `passserver.h` | PassServer class declaration |
| `passserver.cpp` | PassServer implementation |
| `proj5.cpp` | Standard user interface |
| `sproj5.cpp` | Extra credit – secure password input |
| `assignment6_p5.txt` | Big-O analysis |
| `makefile` | Compiles all targets |

---

## Compile and Run

From the `project5` directory:

```bash
make
