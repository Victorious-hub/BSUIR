namespace _253502_Shyshko_Lab5.Interfaces;

public interface ICustomCollection<T>
{
    T this[int index]{get;set;}
    void Reset();
    void Next();
    T Current();
    
    int Count { get; }
    
    void Add(T item);
    void Remove(T item);
    T RemoveCurrent();
}