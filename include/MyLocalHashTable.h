#ifndef _MYLOCALHASHTABLE_H_
#define _MYLOCALHASHTABLE_H_

#include "Key.h"
#include <vector>
#include <list>

class MyLocalHashTable {
private:
    struct Node {
        Key key;
        Value value;

        Node(const Key &key, const Value &value) : key(key), value(value) {}
    };

    std::vector<std::list<Node>> buckets;
    // buckets size
    size_t capacity;
    // current number of elements
    size_t size = 0;
    // load factor
    float load_factor = 0.75;

    size_t get_hashcode(const Key &key, const size_t hash_size) const {
        uint64_t hash = 5381;
        for(auto &partial : key) {
            hash = ((hash << 5) + hash) + partial;
        }

        return hash % hash_size;
    }

public:
    explicit MyLocalHashTable(size_t capacity = 16) : capacity(capacity) {
        buckets.resize(capacity);
    }

    /// @return true if insert successfully, false if update the value
    bool insert(const Key &key, const Value &value) {
        if(size >= load_factor * buckets.size()) {
            rehash(buckets.size() * 2);
        }

        size_t index = get_hashcode(key, capacity);
        for(auto &node : buckets[index]) {
            if(node.key == key) {
                node.value = value;
                return false;
            }
        }

        buckets[index].emplace_back(key, value);
        size++;
        return true;
    }

    /// @return the value's ptr of the key, nullptr if not found
    Value* query(const Key &key){
        size_t index = get_hashcode(key, capacity);

        for(auto &node : buckets[index]) {
            if(node.key == key) {
                return &node.value;
            }
        }

        return nullptr;
    }

    /// @return true if erase successfully, false if not found
    bool erase(const Key &key) {
        size_t index = get_hashcode(key, capacity);

        for(auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if(it->key == key) {
                buckets[index].erase(it);
                size--;
                return true;
            }
        }

        return false;
    }

private:
    // rehash the table to new capacity
    void rehash(size_t new_capacity){
        std::vector<std::list<Node>> new_buckets(new_capacity);


        for(auto &bucket : buckets) {
            for(auto &node : bucket) {
                size_t index = get_hashcode(node.key, new_capacity);
                new_buckets[index].emplace_back(node);
            }
        }
        
        buckets = std::move(new_buckets);
        capacity = new_capacity;
    }

};


#endif // _MYLOCALHASHTABLE_H_
