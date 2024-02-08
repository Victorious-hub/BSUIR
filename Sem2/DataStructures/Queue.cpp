#include <iostream>
#include <string>

template<class T>
struct Node 
{
	T data;
	Node<T>* next = nullptr;
	Node() {}
	Node(T data) :data(data) {}
};

template<class T>
class Queue {
	Node<T>* head;
	Node<T>* tail;
public:
	Queue() 
    {
		head = tail = nullptr;
	}

	void push(T data);
	void pop();
	void display();
	T back();
	T front();
	bool empty();
};

template<class T>
bool Queue<T>::empty() 
{
    return head == nullptr;
}

template<class T>
T Queue<T>::front() 
{
    if (!empty()) return head->data;
    std::cout << "Queue is empty" << '\n';
    return T();
}

template<class T>
T Queue<T>::back() 
{
    if (!empty()) return tail->data;
    std::cout << "Queue is empty" << '\n';
    return T();
}

template<class T>
void Queue<T>::display() 
{
    Node<T>* temp = head;
    while (temp) 
    {
        std::cout << temp->data << "\n";
        temp = temp->next;
    }
}

template<class T>
void Queue<T>::push(T data) 
{
    Node<T>*  newNode = new Node<T>(data);
    if (!head) 
    {
        head = tail = newNode;
        return;
    }

    tail->next = newNode;
    tail = newNode;
}

template<class T>
void Queue<T>::pop() 
{
    if (!head) 
        return;
    Node<T>* temp = head;
    head = head->next;

    if (!head) 
        tail = nullptr;
    delete temp;
}


int main() 
{
    // Create a queue of integers
    Queue<int> intQueue;

    // Push elements into the queue
    intQueue.push(10);
    intQueue.push(20);
    intQueue.push(30);

    // Display the elements in the queue
    std::cout << "Queue elements (int):" << '\n';
    intQueue.display();

    // Get the front and back elements
    std::cout << "Front element (int): " << intQueue.front() << '\n';
    std::cout << "Back element (int): " << intQueue.back() << '\n';

    // Pop an element from the queue
    intQueue.pop();

    // Display the updated queue
    std::cout << "Updated queue elements (int):" << '\n';
    intQueue.display();

    // Create a queue of strings
    Queue<std::string> stringQueue;

    // Push elements into the queue
    stringQueue.push("Hello");
    stringQueue.push("World");
    stringQueue.push("!");

    // Display the elements in the queue
    std::cout << "Queue elements (string):" << '\n';
    stringQueue.display();

    // Get the front and back elements
    std::cout << "Front element (string): " << stringQueue.front() << '\n';
    std::cout << "Back element (string): " << stringQueue.back() << '\n';

    // Pop an element from the queue
    stringQueue.pop();

    // Display the updated queue
    std::cout << "Updated queue elements (string):" << '\n';
    stringQueue.display();

    return 0;
}

