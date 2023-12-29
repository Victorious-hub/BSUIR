#include <iostream>
#include <string>
#include <vector>
#include <chrono>

class Node {
public:
    std::string value;
    int key;
    Node(int key, std::string value):key(key),value(value){}
};

class HashTable {
    Node** arr;//it has two pointers for using index and ->
    int capacity;
    int size;
    std::vector<std::string> elems;
    Node* deleted;//mark it when we delete any item from hash-table
public:
    std::vector<double> getTime;
    std::string colAmount;
    //basic constructor with basic capacity storage
    HashTable(int capacity) : capacity(capacity), size(0) {
        arr = new Node*[capacity];
        for (int i = 0; i < capacity; i++)
            arr[i] = NULL;
        deleted = new Node(-1, "None");
    }
    int hashFunc(int key);
    void insertNode(int key, std::string value);
    std::string deleteNode(int key);
    std::string get(int key);
    std::vector<std::string>& display();
    void show();
    void resize();

};

int HashTable::hashFunc(int key) {
    return key % capacity;
}

void HashTable::insertNode(int key, std::string value) {
    bool fl = false;
    if (size == capacity) {
        resize(); fl = true;
    }

    Node* temp = new Node(key, value);
    int index = hashFunc(key);
    
    while (arr[index] != NULL && arr[index]->key != key && arr[index]->key != -1) {
        index++;
        index%= capacity;
    }

    if (arr[index] == NULL || arr[index]->key == -1)
        size++;
    arr[index] = temp;
}

std::string HashTable::deleteNode(int key) {
    int index= hashFunc(key);
    int get_cap = capacity;
    while (get_cap--) {
        if (arr[index]->key == key) {
            Node* temp = arr[index];
            arr[index] = deleted;
            size--;
            return temp->value;
        }
        
        index++;
        index%= capacity;
    }
    
    return NULL;
}

std::string HashTable::get(int key) {
    auto start = std::chrono::high_resolution_clock::now();
    int index= hashFunc(key);
    int counter = 0;

    while (arr[index] != NULL) {

        if (counter++ > capacity)
            return NULL;

        if (arr[index]->key == key) {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;

            getTime.push_back(duration.count());
            return arr[index]->value;
        }
        
        colAmount += std::to_string(index) + " ";
        index++;
        index%= capacity;
    }
}

std::vector<std::string>& HashTable::display() {
    for (int i = 0; i < capacity; i++) {
        if (arr[i] != NULL && arr[i]->key != -1) {
            elems.push_back(std::to_string(arr[i]->key));
            elems.push_back(arr[i]->value);
        }
    }
    return elems;
}

void HashTable::show() {
    for (int i = 0; i < capacity; i++) {
        if (arr[i] != NULL && arr[i]->key != -1) {
            std::cout << arr[i]->key << " " << arr[i]->value << "\n";
        }
    }
}

void HashTable::resize() {
    std::vector<std::string> elems1 = display();
    capacity = capacity * 2;
    delete[] arr;

    arr = new Node*[capacity];
    for (int i = 0; i < capacity; i++)
        arr[i] = NULL;

    int count = 0;
    int get_ind = 0;
    size = 0;

    while (count != capacity / 2) {
        insertNode(atoi(elems1[get_ind].c_str()), elems1[get_ind + 1]);
        ++count;
        get_ind += 2;
    }
}


int main() {
    HashTable HashTable(10);

    // Inserting key-value pairs
    HashTable.insertNode(5, "Value 1");
    HashTable.insertNode(15, "Value 2");
    HashTable.insertNode(25, "Value 3");

    // Displaying all key-value pairs
    HashTable.show();

    // Retrieving values by key
    std::string value1 = HashTable.get(5);
    std::string value2 = HashTable.get(15);
    std::string value3 = HashTable.get(25);

    std::cout << "Value at key 5: " << value1 << std::endl;
    std::cout << "Value at key 15: " << value2 << std::endl;
    std::cout << "Value at key 25: " << value3 << std::endl;

    // Deleting a key-value pair
    std::string deletedValue = HashTable.deleteNode(15);
    std::cout << "Deleted value at key 15: " << deletedValue << std::endl;
    
    return 0;
}