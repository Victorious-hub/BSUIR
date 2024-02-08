#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <type_traits>
#include <memory>
#include <algorithm>
#include <vector>

// Max binary heap
class BinaryHeap
{
private:
    int* heap;
    int capacity;
    int last;
public:
    BinaryHeap(int size) : 
        capacity(size), heap(new int[size]),last(-1){}
    BinaryHeap(){}
    void upHeapify(int v);
    void add(int value);
    void print();
    void downHeapify(int k);
    void remove();
};

void BinaryHeap::remove() 
{
    std::swap(heap[0], heap[last]);
    last--;
    downHeapify(0);
}

void BinaryHeap::print() 
{
    for (int i = 0; i <= last; ++i) 
    {
        std::cout<<heap[i] << " ";
    }
    std::cout<<"\n";
}

void BinaryHeap::add(int value) 
{
    heap[++last] = value;
    upHeapify(last);
}

void BinaryHeap::upHeapify(int v) 
{
    int parent = (v - 1)/2;
    if (parent >= 0 && heap[parent] < heap[v]) 
    {
        std::swap(heap[parent], heap[v]);
        upHeapify(parent);
    }
}

void BinaryHeap::downHeapify(int k) 
{
    int largest = k;

    int left = (k * 2) + 1;
    int right = (k * 2) + 2;

    if (left <= last && heap[left] > heap[largest]) 
    {
        largest = left;
    }

    if (right <= last && heap[right] > heap[largest]) 
    {
        largest = right;
    }

    if (largest != k) 
    {
        std::swap(heap[k], heap[largest]);
        downHeapify(largest);
    }
}


int main() {
    BinaryHeap heap(10);

    heap.add(5);
    heap.add(10);
    heap.add(3);
    heap.add(8);
    heap.add(1);

    heap.print();


    return 0;
}