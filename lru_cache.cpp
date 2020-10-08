#include <deque>

using namespace std;

struct key_value {
    int first, second;
};

bool operator==(const key_value& left, const key_value& right) {
    return left.first == right.first;
}


class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        cache = deque<key_value>();
    }
    
    int get(int key) {
        
        // O(N)
        
        for (deque<key_value>::iterator it = cache.begin(); it < cache.end(); ++it) {
            
            if (it->first == key) {
                int value = it->second;
                cache.erase(it);
                cache.push_front({key, value});
                return value;
            }
        }
        
        return -1;
    }
    
    void put(int key, int value) {
        
        // O(N)
        
        key_value kv = {key, value};
        
        auto it = find(cache.begin(), cache.end(), kv);
        
        // Found in cache (remove)
        if (it != cache.end()) cache.erase(it);
        
        // Not in a currently full cache (pop lru)
        else if (cache.size() >= capacity) cache.pop_back();

        cache.push_front(kv);
    }
    
private:
    int capacity;
    deque<key_value> cache;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */