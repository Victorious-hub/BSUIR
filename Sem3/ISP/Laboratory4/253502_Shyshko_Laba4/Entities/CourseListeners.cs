namespace _253502_Shyshko_Laba4.Entities;

public class CourseListeners
{
    public CourseListeners(string name,bool listener, string courseName, int listenerAge)
    {
        Name = name;
        IsListener = listener;
        CourseName = courseName;
        ListenerAge = listenerAge;
    }

    public string Name { get; set; }
    public  bool IsListener { get; set; }
    public  string CourseName { get; set; }
    public  int ListenerAge { get; set; }
}