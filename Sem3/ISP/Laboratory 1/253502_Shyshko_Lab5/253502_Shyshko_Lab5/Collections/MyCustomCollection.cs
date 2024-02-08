using System.Collections;
using System.Collections.Generic;
using _253502_Shyshko_Lab5.Interfaces;
namespace _253502_Shyshko_Lab5.Collections;

public class MyCustomCollection<T> : ICustomCollection<T>, IEnumerable<T>
{
    public class Node
    {
        public T Data { get; set; }
        public Node Next{ get; set; }

        public Node(T data)
        {
            Data = data;
            Next = null;
        }
    }

    private Node head;
    private Node current;
    

    public MyCustomCollection()
    {
        head = current = null;
    }
    
    public void Add(T item)
    {
        
        Node newNode = new Node(item);
        
        if (head == null) {
            head = newNode;
            current = head;
            return;
        }
        
        Node temp = head;
        while (temp.Next != null) {
            
            temp = temp.Next;
        }
        
        temp.Next = newNode;
    }
    
    public int Count
    {
        get
        {
            int counter = 0;
            Node temp = head;
            while (temp != null)
            {
                counter++;
                temp = temp.Next;
            }
            return counter;
        }
    }

    public T Current()
    {
        return current.Data;
    }


    public void Reset()
    {
        current = head;
    }

    public void Next()
    {
        Node temp = current;
        if (temp.Next != null)
        {
            temp = temp.Next;
            current = temp;
        }

        return;
    }

    public T this[int index]
    {
        get
        {
            int counter = 0;
            Node temp = head;
            while (temp != null)
            {
                if (counter == index)
                {
                    break;
                }
                counter++;
                temp = temp.Next;
            }
            return temp.Data;
        }
        set
        {
            int counter = 0;
            Node temp = head;
            while (temp != null)
            {
                if (counter == index)
                {
                    temp.Data = value;
                }
                counter++;
                temp = temp.Next;
            }
        }
    }
    public void Remove(T value)
    {
        Node previous = null;
        Node current = head;

        while (current != null)
        {
            if (current.Data.Equals(value))
            {
                if (previous != null)
                {
                    previous.Next = current.Next;
                    if (current == this.current)
                    {
                        this.current = current.Next;
                    }
                }
                else
                {
                    head = current.Next;
                    this.current = head;
                }
                return;
            }

            previous = current;
            current = current.Next;
        }
    }
    public void RemoveCurrent()
    {
        if (current == null)
        {
            return;
        }

        if (current == head)
        {
            head = current.Next;
            current = head;
            return;
        }
        Remove(current.Data);
        
    }
    public IEnumerator<T> GetEnumerator()
    {
        Node temp = head;
        while (temp != null)
        {
            yield return temp.Data;
            temp = temp.Next;
        }
    }
    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }
}
