namespace _253502_Shyshko_Laba4.Interfaces;

public interface IFileService<T>
{
    IEnumerable<T> ReadFile(string fileName);
    void SaveData(IEnumerable<T> data, string fileName);
}