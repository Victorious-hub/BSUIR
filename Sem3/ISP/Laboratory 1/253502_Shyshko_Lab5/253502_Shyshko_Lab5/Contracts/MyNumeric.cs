using System.Numerics;
namespace _253502_Shyshko_Lab5.Contracts;

public class MyNumeric<T> : IAdditionOperators<MyNumeric<T>, MyNumeric<T>, MyNumeric<T>>
{
    private T value;
    public MyNumeric(){}
    public MyNumeric(T value)
    {
        this.value = value;
    }

    public T Value
    {
        get { return value; }
        set { this.value = value; }
    }

    public override string ToString()
    {
        return value.ToString();
    }

    public static MyNumeric<T> operator +(MyNumeric<T> a, MyNumeric<T> b)
    {
        dynamic x = a.value;
        dynamic y = b.value;

        return new MyNumeric<T>(x + y);
    }
}