using _253502_Shyshko_Laba4.Interfaces;

namespace _253502_Shyshko_Laba4.Entities;

using System.Collections.Generic;
using System.IO;

public class FileService : IFileService<CourseListeners>
{
    public IEnumerable<CourseListeners> ReadFile(string fileName)//yield нельзя всунуть в try/catch
    {

            using BinaryReader reader = new BinaryReader(File.Open(fileName, FileMode.Open));
            while (reader.BaseStream.Position != reader.BaseStream.Length)
            {
                string name = reader.ReadString();
                bool isListener = reader.ReadBoolean();
                string courseName = reader.ReadString();
                int listenerAge = reader.ReadInt32();


                yield return new CourseListeners(name, isListener, courseName, listenerAge);
            }
    }

    public void SaveData(IEnumerable<CourseListeners> data, string fileName)
    {
        try
        {
            if (File.Exists(fileName))
            {
                File.Delete(fileName);
            }

            using BinaryWriter writer = new BinaryWriter(File.Open(fileName, FileMode.Create));
            foreach (CourseListeners listener in data)
            {
                writer.Write(listener.Name);

                writer.Write(listener.IsListener);

                writer.Write(listener.CourseName);

                writer.Write(listener.ListenerAge);
            }
        }

        catch (IOException ex)
        {
            Console.WriteLine("Could not write in file {0}. Reason: {1}", fileName, ex.Message);
            throw;
        }
    }
}