using EducationCourses;
using EducationCourses.StreamService;

namespace _253502_Shyshko_Laba8;

class Program
{
    static async Task Main(string[] args)
    {
        List<EducationCourse> courses = CreateCoursesCollection();

        Console.WriteLine($"Поток выполнения {Thread.CurrentThread.ManagedThreadId}: Начало работы");

        using (MemoryStream stream = new MemoryStream())
        {
            IProgress<string> progress = new Progress<string>(ReportProgress);
            StreamService<EducationCourse> streamService = new StreamService<EducationCourse>();

            Console.WriteLine($"Thread {Thread.CurrentThread.ManagedThreadId}: Starting WriteToStreamAsync");
            streamService.WriteToStreamAsync(stream,courses, progress);

            Thread.Sleep(2000);
            
            Console.WriteLine($"Thread {Thread.CurrentThread.ManagedThreadId}: Starting CopyFromStreamAsync");
            streamService.CopyFromStreamAsync(stream, "output.json", progress);
            
            ///
            
            int count = await streamService.GetStatisticsAsync("output.json", FilterCourse);

            Console.WriteLine($"Статистические данные: {count}");
        }
    }

    private static void ReportProgress(string message)
    {
        Console.WriteLine($"Поток выполнения {Thread.CurrentThread.ManagedThreadId}: {message}");
    }


    private static List<EducationCourse> CreateCoursesCollection()
    {
        int wwe = 10;
        List<EducationCourse> courses = new List<EducationCourse>();

        for (int i = 0; i < 1000; i++)
        {
            EducationCourse course = new EducationCourse($"Course {wwe}",
                new List<Listener> { new() { Name = $"Listener {i}" } });
            if (i % 2 == 0)
            {
                course.AddListner($"Course {wwe}", new Listener { Name = $"Listener {i * 120}" });
            }
            courses.Add(course);
        }

        return courses;
    }

    private static bool FilterCourse(EducationCourse course)
    {
        return course.Listener.Count > 1;
    }
}
