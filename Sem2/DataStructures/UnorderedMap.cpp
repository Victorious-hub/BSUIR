#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include <type_traits>
#include <iostream>
#include <exception>
#include <algorithm>
#include <functional>
#include <chrono>
#include <vector>
#include <algorithm>
#include <forward_list>

template<class KeyType, class ValueType, class Hash = std::hash<KeyType>>
class UnorderedMap 
{
private:
    std::vector<int> hashes;
    std::vector<std::forward_list<std::pair<KeyType, ValueType>>> container;
    int get_hash;
    int size_;
    int capacity;
    Hash hash_functor;
public:
    //UnorderedMap() :capacity(1),size(0){}
    UnorderedMap(int first_size) :capacity(first_size), container(first_size), size_(0) {}
    void insert(KeyType key, ValueType value);
    ValueType& operator[](const KeyType& key);
    bool contains(KeyType key);
    int size();
    int max_size();
    bool empty();
    void clear();
    void erase(KeyType key);
    void rehash(int new_capacity);
    void display();

};

template<class KeyType, class ValueType, class Hash>
void UnorderedMap<KeyType, ValueType, Hash>::display() 
{
    for (int i = 0; i < hashes.size(); ++i) 
    {
        auto iter = container[hashes[i]].begin();
        std::cout << "key:" << " " << iter->first << " " << "value:" << " " << iter->second << "\n";
    }
}

template<class KeyType, class ValueType, class Hash>
void UnorderedMap<KeyType, ValueType, Hash>::rehash(int new_capacity) 
{
    std::vector<std::forward_list<std::pair<KeyType, ValueType>>> buffer_container(new_capacity);

    container.swap(buffer_container);

    size_ = 0;
    std::vector<int> buffer_vector = hashes;

    hashes.clear();

    int var;
    if (new_capacity >= capacity) 
    {
        var = buffer_vector.size();
    } else
    {
        var = new_capacity;
    }

    capacity = new_capacity;

    for (int i = 0; i < var; ++i) 
    {
        auto iter = buffer_container[buffer_vector[i]].begin();
        insert(iter->first, iter->second);
    }

}

template<class KeyType, class ValueType, class Hash>
void UnorderedMap<KeyType, ValueType, Hash>::erase(KeyType key) 
{
    get_hash = hash_functor(key) % capacity;
    auto iterated_obj = container[get_hash].before_begin();
    auto before_iterated_obj = iterated_obj;
    container[get_hash].erase_after(before_iterated_obj);
    before_iterated_obj = iterated_obj;
    ++iterated_obj;
    size_--;

    for (int i = 0; i < hashes.size(); ++i) 
    {
        if (hashes[i] == get_hash) 
        {
            hashes.erase(hashes.begin() + i);
            break;
        }
    }

}


template<class KeyType, class ValueType, class Hash>
void UnorderedMap<KeyType, ValueType, Hash>::clear() 
{
    container.clear();
    size_ = 0;
    container.resize(capacity);
}

template<class KeyType, class ValueType, class Hash>
bool UnorderedMap<KeyType, ValueType, Hash>::empty() 
{
    return size_ == 0;
}

template<class KeyType, class ValueType, class Hash>
int UnorderedMap<KeyType, ValueType, Hash>::max_size() 
{
    return capacity;
}

template<class KeyType, class ValueType, class Hash>
int UnorderedMap<KeyType, ValueType, Hash>::size() 
{
    return size_;
}

template<class KeyType, class ValueType, class Hash>
void UnorderedMap<KeyType, ValueType, Hash>::insert(KeyType key, ValueType value) 
{
    if (size_ == capacity)rehash(capacity * 2);

    get_hash = hash_functor(key) % capacity;
    hashes.push_back(get_hash);
    container[get_hash].push_front(std::pair<KeyType, ValueType>(key, value));
    size_++;

}

template<class KeyType, class ValueType, class Hash>
ValueType& UnorderedMap<KeyType, ValueType, Hash>::operator[](const KeyType& key) 
{
    get_hash = hash_functor(key) % capacity;
    auto iterated_obj = container[get_hash].begin();
    while (iterated_obj != container[get_hash].end()) 
    {
        if (iterated_obj->first == key) 
            return iterated_obj->second;
        iterated_obj++;
    }

    ValueType value;

    insert(key, value);

    iterated_obj = container[get_hash].begin();
    while (iterated_obj != container[get_hash].end()) 
    {
        if (iterated_obj->first == key) 
            return iterated_obj->second;
        iterated_obj++;
    }
}


template<class KeyType, class ValueType, class Hash>
bool UnorderedMap<KeyType, ValueType, Hash>::contains(KeyType key) 
{
    auto iterated_obj = container[get_hash].begin();
    while (iterated_obj != container[get_hash].end()) 
    {
        if (iterated_obj->first == key) 
            return true;
        iterated_obj++;
    }
    return false;
}

int main() {
    UnorderedMap<std::string, int> map(5);

    map.insert("apple", 10);
    map.insert("banana", 5);
    map.insert("orange", 7);

    std::cout << "Map size: " << map.size() << std::endl;
    std::cout << "Max map size: " << map.max_size() << std::endl;
    std::cout << "Is map empty? " << (map.empty() ? "Yes" : "No") << std::endl;

    std::cout << "Map contains 'apple'? " << (map.contains("apple") ? "Yes" : "No") << std::endl;
    std::cout << "Map contains 'grape'? " << (map.contains("grape") ? "Yes" : "No") << std::endl;

    std::cout << "Value of 'apple': " << map["apple"] << std::endl;
    std::cout << "Value of 'banana': " << map["banana"] << std::endl;
    std::cout << "Value of 'orange': " << map["orange"] << std::endl;

    map["apple"] = 20;
    std::cout << "Updated value of 'apple': " << map["apple"] << std::endl;

    map.erase("banana");
    std::cout << "Map size after erasing 'banana': " << map.size() << std::endl;

    map.clear();
    std::cout << "Map size after clearing: " << map.size() << std::endl;

    return 0;
}