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

class Node 
{
public:
	std::string data;
	int key;
	Node* next;
	Node* prev;
	Node(int key, std::string data) : key(key), data(data), next(nullptr) {}
};

class ArrayStack 
{
private:
	Node* top;
public:
	ArrayStack() 
    {
        top = nullptr; 
    }
	void push(int key, std::string value); 
	std::string searchKey(int key);
	std::string searchValue(int key);
	void remove(int key);
};

void ArrayStack::push(int key, std::string value) 
{
    Node* newNode = new Node(key, value);
    newNode->next = NULL;
    newNode->prev = NULL;

    if (top == NULL) 
    {
        top = newNode;
    } else 
    {
        Node* temp = top;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }
}

std::string ArrayStack::searchKey(int key)
{
    if (top == nullptr) 
        return "Not Found";
    Node* node = top;

    while (node->key != key) 
    {
        if (node == nullptr) 
            return "0";
    }
    return std::to_string(node->key);
}

std::string ArrayStack::searchValue(int key)
{
    if (top == nullptr) 
        return "Not Found";
    Node* node = top;

    while (node->key != key) 
    {
        if (node == nullptr) 
            return "0";
    }
    return node->data;
}

void ArrayStack::remove(int key) 
{
    if (top != NULL) 
    {
        if (top->next == NULL) 
        {
            top = NULL;
        } else 
        {
            Node* temp = top;
            while (temp->next->next != NULL)
                temp = temp->next;
            Node* lastNode = temp->next;
            temp->next = NULL;
            free(lastNode);
        }
    }
}

class HashTableList : public ArrayStack 
{
private:
	int capacity;
	int size;
	ArrayStack* arr = new ArrayStack[capacity];
public:
	HashTableList(int capacity) :size(0), capacity(capacity) {}
	~HashTableList() 
    {
		delete[] arr;
	}
	int hashFunc(int key);
	void insert(int key, std::string value);
    void erase(int key);
	std::string getValue(int key);
	std::string getKey(int key);
};

int HashTableList::hashFunc(int key) 
{
    return abs(key % capacity);
}

void HashTableList::insert(int key, std::string value) 
{
    int index = hashFunc(key);
    ++size;
    return  arr[index].push(key, value);
}

std::string HashTableList::getValue(int key) 
{
    int index = hashFunc(key);
    return arr[index].searchValue(key);
}

void HashTableList::erase(int key) 
{
    int index = hashFunc(key);
    arr[index].remove(key);
    --size;
}

std::string HashTableList::getKey(int key) 
{
    int index = hashFunc(key);
    return arr[index].searchKey(key);
}

int main() {
    HashTableList hashTable(100);

    hashTable.insert(5, "Value 1");
    hashTable.insert(15, "Value 2");
    hashTable.insert(25, "Value 3");

    std::cout << "Value at key 25: " << hashTable.getValue(25) << std::endl;

    std::cout << "Key at index 5: " << hashTable.getKey(5) << std::endl;
    std::cout << "Key at index 15: " << hashTable.getKey(15) << std::endl;
    std::cout << "Key at index 25: " << hashTable.getKey(25) << std::endl;

    hashTable.erase(15);

    std::cout << "Value at key 15 after erasing: " << hashTable.getValue(15) << std::endl;
    std::cout << "Key at index 15 after erasing: " << hashTable.getKey(15) << std::endl;

    return 0;
}