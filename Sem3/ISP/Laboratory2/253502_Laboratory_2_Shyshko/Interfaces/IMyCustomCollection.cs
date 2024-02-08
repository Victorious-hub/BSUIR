namespace _253502_Laboratory_2_Shyshko.Interfaces;

public interface ICustomCollection<T>
{
    T this[int index]{get;set;}
    void Next();
    T Current();
    void Reset();
    int Count { get; }
    void Add(T item);
    void Remove(T value);
    void RemoveCurrent();
    void Display();

}