namespace EducationCourses;

public class EducationCourse
{ 
    public Guid Id { get; set; }
    public string CourseName { get; set; } 
    public List<Listener> Listener { get; set; } 
    public static int CoursesListeners { get;set; } 
    public EducationCourse(string courseName, List<Listener> listener)
    {
        Id = Guid.NewGuid();
        CourseName = courseName;
        Listener = new(listener);
    }

    public void AddListner(string courseName, Listener listener)
    {
        if (CourseName == courseName)
        {
            Listener.Add(listener);
        }
        else
        {
            Console.WriteLine("Doesn't exist");
        }
    }
    public void UpdateStatistics()
    {
        if (Listener.Count > 2)
        {
            CoursesListeners++;
        }
    }
    


   
}


public class Listener
{
    public string Name { get; set; }

}