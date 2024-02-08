using _253502_Shyshko_Laba4.Entities;


namespace _253502_Shyshko_Laba4;
using System.Linq;
public class Program
{
    public static void Main()
    {

        FileService fileService = new FileService();


        string[] fileNames = GenerateFileNames(10);


        CreateEmptyFiles(fileNames);

        Console.WriteLine("Созданы следующие файлы:");

        foreach (string fileName in fileNames)
        {
            Console.WriteLine(fileName);
        }
        
        var folderPath = "C:/Users/Asus/RiderProjects/253502_Shyshko_Laba4/253502_Shyshko_Laba4/Shyshko_Files_Laba4/";

        var fileNames1 = Directory.EnumerateFiles(folderPath).Select(filePath => Path.GetFileName(filePath));

        foreach (var fileName in fileNames1)
        {
            Console.WriteLine($"File {fileName} has an extension {Path.GetExtension(Path.Combine(folderPath,fileName))}");
        }
        
        List<CourseListeners> listeners = new List<CourseListeners>
        {
            new CourseListeners("John", true, "Math", 25),
            new CourseListeners("Vitya", true, "Programming", 18),
            new CourseListeners("Igor", true, "Chemistry", 50),
            new CourseListeners("John1", true, "Math2", 16),
            new CourseListeners("John2", true, "Math3", 48),
        };

       
        fileService.SaveData(listeners, "listeners.bin");

        IEnumerable<CourseListeners> loadedListeners = fileService.ReadFile("listeners.bin");
        foreach (CourseListeners listener in loadedListeners)
        {
            Console.WriteLine($"Name: {listener.Name}, IsListener: {listener.IsListener}, CourseName: {listener.CourseName}, ListenerAge: {listener.ListenerAge}");
        }
        
        
        if (File.Exists("li.bin"))
        {
            File.Delete("li.bin");
        }
        File.Move("listeners.bin", "li.bin");


        IEnumerable<CourseListeners> NewListeners = fileService.ReadFile("li.bin");
        List<CourseListeners> newlisteners1 = new List<CourseListeners>();
        List<CourseListeners> newlisteners2 = new List<CourseListeners>();
        foreach (CourseListeners listener in NewListeners)
        {
            newlisteners1.Add(new CourseListeners(listener.Name,listener.IsListener,listener.CourseName,listener.ListenerAge));
            newlisteners2.Add(new CourseListeners(listener.Name,listener.IsListener,listener.CourseName,listener.ListenerAge));
        }
       
        MyCustomComparer<CourseListeners> comparer = new MyCustomComparer<CourseListeners>();


        var sortedList = newlisteners1.OrderBy(x => x, comparer);
        
        foreach (var listener in sortedList)
        {
            Console.WriteLine($"Name: {listener.Name}, IsListener: {listener.IsListener}, CourseName: {listener.CourseName}, ListenerAge: {listener.ListenerAge}");
        }
        
        var sortedList1 = newlisteners2.OrderBy(x => x.ListenerAge);


        foreach (var listener in sortedList1)
        {
            Console.WriteLine(listener.Name + " - " + listener.ListenerAge);
        }
    }


    private static string[] GenerateFileNames(int count)
    {
        string[] extensions = { ".txt", ".rtf", ".dat", ".inf" };
        Random random = new Random();
        string[] fileNames = new string[count];

        for (int i = 0; i < count; i++)
        {
            string fileName = Path.GetRandomFileName();
            string extension = extensions[random.Next(extensions.Length)];
            fileNames[i] = Path.ChangeExtension(fileName, extension);
        }
        

        return fileNames;
    }



    private static void CreateEmptyFiles(string[] fileNames)
    {
        string directoryPath = "C:/Users/Asus/RiderProjects/253502_Shyshko_Laba4/253502_Shyshko_Laba4/Shyshko_Files_Laba4/";

        foreach (string fileName in fileNames)
        {
            string filePath = Path.Combine(directoryPath, fileName);
            File.Create(filePath).Close();
        }
    }
}