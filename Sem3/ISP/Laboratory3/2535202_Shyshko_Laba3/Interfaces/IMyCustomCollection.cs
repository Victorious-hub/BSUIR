namespace _2535202_Shyshko_Laba3.Interfaces;


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