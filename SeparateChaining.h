#ifndef HASHING_SEPARATECHAINING_H
#define HASHING_SEPARATECHAINING_H

#include <functional>
#include <iostream>
#include <list>
#include <optional>
#include <string>
#include <vector>
using std::cout, std::endl, std::function, std::iterator, std::list, std::nullopt, std::optional, std::string, std::vector;

template<typename Keyable>
class SeparateChaining {
private:
    vector<list<Keyable>> table;
    function<string(Keyable)> getKey;
    mutable unsigned long readCount; // Counts reads (MUTABLE because it's modified inside a const method)

    unsigned long hornerHash(string key) const {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 37 + letter;
        }
        return hashVal % table.size();
    }

    // Find the next prime number
    int nextPrime(int n) {
        if (n % 2 == 0) {
            ++n;
        }
        bool prime = false;
        while (!prime) {
            prime = true;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    prime = false;
                }
            }
            n += 2;
        }
        return (n-2);
    }

public:
    // Constructor
    SeparateChaining(unsigned long tableSize, function<string(Keyable)> getKey) {
        // This will fill the table with empty lists
        table.resize(nextPrime(tableSize));
        this->getKey = getKey;
        readCount = 0; // Initialize reads to 0
    }

    // Used in main to reset reads when needed
    void resetReadCount(){
        readCount = 0;
    }

    // Get Read Count
    int getReadCount(){
        return readCount;
    }

    // Insert
    bool insert(Keyable item) {
        // Get the key from the item
        string key = getKey(item);
        // If the item is already in the table, do not insert it
        if (!find(key)) {
            // Hash the key to get an index
            unsigned long index = hornerHash(key);
            // Put the item at that index in the table
            table[index].push_back(item);
            return true;
        }
        return false;
    }

    // Find
    optional<Keyable> find(string key) const {
        // Hash the key to get an index
        unsigned long index = hornerHash(key);
        // Check each item in the list at the index to see if the key matches
        for (const Keyable& k : table[index]) {
            readCount++; // Increment reads when accessed
            if (getKey(k) == key) {
                // We found the item
                return k;
            }
        }
        // We didn't find the item
        return nullopt;
    }

    // Remove
    bool remove(string key) {
        // Hash the key to get an index
        unsigned long index = hornerHash(key);
        // Check each item in the list at the index to see if the key matches
        for (const Keyable& k : table[index]) {
            if (getKey(k) == key) {
                // We found the item
                // Remove the item
                table[index].remove(k);
                return true;
            }
        }
        // We didn't find the item
        return false;
    }

    // Print the table
    void printTable() const {
        cout << "Beginning of table" << endl;
        for (unsigned long i = 0; i < table.size(); ++i) {
            cout << i << ": ";
            for (const Keyable& k : table[i]) {
                if (k == *table[i].begin()) {
                    cout << k;
                } else {
                    cout << ", " << k;
                }
            }
            cout << endl;
        }
        cout << "End of table" << endl;
    }
};

#endif
