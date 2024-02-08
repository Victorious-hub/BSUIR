#include<iostream>

template<class T>
struct Node 
{
	T data;

	Node* next;
	
	Node(T n) :data(n), next(nullptr) {}
};

template<class T>
class Stack 
{
private:
	Node<T>* top;
public:
	Stack() : top(nullptr) {}

	void push(T data);
	bool isEmpty();
	int peek();
	void pop();
	void display();
};

template<class T>
void Stack<T>::push(T data) 
{
    Node<T>* temp = new Node<T>(data);
    temp->next = top;
    top = temp;
}

template<class T>
bool Stack<T>::isEmpty() 
{
	return top == nullptr;
}

template<class T>
int Stack<T>::peek() 
{
    if (!isEmpty())
	{
        return top->data;
    } else 
	{
        exit(1);
    }
}

template<class T>
void Stack<T>::pop() 
{
    Node<T>*  temp = top;
    if (!temp) 
		return;

    top = top->next;
    delete temp;
}

template<class T>
void Stack<T>::display()
{
    Node<T>* temp = top;
    if (!temp) 
		return;
    while (temp) 
	{
        std::cout << temp->data << "\n";
        temp = temp->next;
    }
    
}

int main()
{
	Stack<int> s;
	s.push(11);
	s.push(22);
	s.push(33);
	s.push(44);


	s.display();
	std::cout << "some text" << "\n";
	s.pop();
	s.pop();	
	s.display();
	return 0;
}