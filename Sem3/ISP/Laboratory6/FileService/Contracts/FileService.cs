using FileService.Interfaces;
using Newtonsoft.Json;
namespace FileService.Contracts;

public class FileService<T> : IFileService<T> where T : class
{
    public IEnumerable<T>? ReadFile(string fileName)
    {
        var json = File.ReadAllText(fileName);
        return JsonConvert.DeserializeObject<IEnumerable<T>>(json);
    }

    public void SaveData(IEnumerable<T> data, string fileName)
    {
        var json = JsonConvert.SerializeObject(data);
        File.WriteAllText(fileName, json);
    }
}