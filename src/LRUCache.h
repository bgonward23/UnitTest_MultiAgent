#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <list>
#include <unordered_map>
#include <stdexcept>

class LRUCache {
private:
    size_t capacity;
    std::list<int> lru_list;
    std::unordered_map<int, std::pair<int, std::list<int>::iterator>> cache;

public:
    LRUCache(size_t cap) : capacity(cap) {
        if (cap == 0) throw std::invalid_argument("Capacity must be positive");
    }

    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end()) return -1;
        lru_list.erase(it->second.second);
        lru_list.push_front(key);
        it->second.second = lru_list.begin();
        return it->second.first;
    }

    void put(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            lru_list.erase(it->second.second);
            lru_list.push_front(key);
            cache[key] = {value, lru_list.begin()};
            return;
        }
        if (cache.size() >= capacity) {
            int lru_key = lru_list.back();
            lru_list.pop_back();
            cache.erase(lru_key);
        }
        lru_list.push_front(key);
        cache[key] = {value, lru_list.begin()};
    }
    
    size_t size() const { return cache.size(); }
};

#endif
