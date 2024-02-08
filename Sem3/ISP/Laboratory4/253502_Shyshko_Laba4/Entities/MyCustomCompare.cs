namespace _253502_Shyshko_Laba4.Entities;

public class MyCustomComparer<T> : IComparer<T>
{
    public int Compare(T? x, T? y)
    {
        CourseListeners? listener1 = x as CourseListeners;
        CourseListeners? listener2 = y as CourseListeners;
        return String.CompareOrdinal(listener1?.Name, listener2?.Name);
    }
}