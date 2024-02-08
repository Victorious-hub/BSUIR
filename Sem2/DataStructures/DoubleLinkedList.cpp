#include <iostream>

template<class T>
struct Node 
{
	Node<T>* next;
	Node<T>* prev;
	T data;

	Node() : next(nullptr), prev(nullptr) {}
	Node(T value) : next(nullptr), prev(nullptr), data(value){}
};

template<class T>
class  DoubleLinkedList 
{
	int size;
	Node<T>* head;
	Node<T>* tail;
public:
	DoubleLinkedList() : size(0), head(nullptr), tail(nullptr) {}
	void pushBack(T value);
	void pushFront(T value);
	void display();
	void popFront();
	void popBack();
	void insert(int pos, T value);
	void erase(int pos);
	Node<T>* front();
	Node<T>* back();
    Node<T>* at(int pos);

};

template<class T>
void DoubleLinkedList<T>::pushBack(T value) 
{
    Node<T>* newNode = new Node<T>(value);

    if (!tail) 
    {
        tail = newNode;
        head = tail;
    } else 
    {		
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    ++size;
}

template<class T>
void DoubleLinkedList<T>::pushFront(T value) 
{
    Node<T>* newNode = new Node<T>(value);
    
    if (!head) 
    {
        head = newNode;
        tail = head;
    } else 
    {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
    ++size;
}

template<class T>
void DoubleLinkedList<T>::display() 
{
    Node<T>* newNode = head;
    while (newNode) 
    {
        std::cout << newNode->data<<"\n";
        newNode = newNode->next;
    }
}

template<class T>
void DoubleLinkedList<T>::popFront() 
{
    if (!head)
        return;
    Node<T>* newNode = head;

    head = newNode->next;
    head->prev = nullptr;
    delete newNode;
    --size;
}

template<class T>
void DoubleLinkedList<T>::popBack() 
{
    if (!tail) 
        return;

    Node<T>* newNode = tail;
    tail = newNode->prev;
    tail->next = nullptr;
    delete newNode;
    --size;
}

template<class T>
Node<T>* DoubleLinkedList<T>::at(int pos) 
{
    Node<T>* newNode = head;
    int counter = 0;
    while (newNode) 
    {
        if (counter == pos) 
            return newNode;
        newNode = newNode->next;
        ++counter;
    }
    
    newNode == nullptr;
    return newNode;
}

template<class T>
void DoubleLinkedList<T>::insert(int pos, T value) 
{
    if (!pos || !head) 
    {
        pushFront(value);
    } else if (pos == size) 
    {
        pushBack(value);
    } else 
    {
        Node<T>* newNode = new Node<T>(value);
        Node<T>* leftNode = at(pos - 1);
        Node<T>* rightNode = at(pos);

        if (!leftNode || !rightNode) 
        {
            return;
        }

        newNode->next = rightNode;
        newNode->prev = leftNode;

        rightNode->prev = newNode;
        leftNode->next = newNode;
    }
    
}

template<class T>
void DoubleLinkedList<T>::erase(int pos) 
{
    if (!head) 
        return;

    if (!pos) 
        popFront();

    if (pos == size-1) 
    {
        popBack();
    } else 
    {
        Node<T>* leftNode = at(pos-1);
        Node<T>* rightNode = at(pos+1);
        Node<T>* newNode = at(pos);
    
        if (!leftNode || !rightNode || !newNode) 
            return;

        leftNode->next = rightNode;
        rightNode->prev = leftNode;

        delete newNode;
    }

}

template<class T>
Node<T>* DoubleLinkedList<T>::front() 
{
    if (!head) 
        return nullptr;
    return head->data;
}

template<class T>
Node<T>* DoubleLinkedList<T>::back()
{
    if (!tail) 
        return nullptr;
    return tail->data;
}

int main() 
{
	DoubleLinkedList<int> lvar;
	lvar.pushBack(10);
	lvar.pushBack(20);
	lvar.pushBack(30);

	lvar.pushFront(40);

	lvar.pushFront(50);

	lvar.pushBack(60);

	lvar.display();


	lvar.erase(3);

	lvar.insert(-30, 525225);

	lvar.display();
}