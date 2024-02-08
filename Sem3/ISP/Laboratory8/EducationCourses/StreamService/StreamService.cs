using Newtonsoft.Json;

namespace EducationCourses.StreamService;

public class StreamService<T>
{
    SemaphoreSlim _semaphore = new(2, 2);

    public async Task WriteToStreamAsync(Stream stream, IEnumerable<T> data, IProgress<string> progress)
    {
        await Task.Delay(3000);

        await _semaphore.WaitAsync();
        try
        {
            using (StreamWriter writer = new StreamWriter(stream, leaveOpen: true))
            using (JsonWriter jsonWriter = new JsonTextWriter(writer))
            {
                var enumerable = data as T[] ?? data.ToArray();
                int totalCount = enumerable.Count();
                int currentItem = 0;

                jsonWriter.WriteStartArray();

                foreach (T item in enumerable)
                {
                    string itemJson = JsonConvert.SerializeObject(item);
                    await jsonWriter.WriteRawValueAsync(itemJson);

                    currentItem++;

                    int progressPercentage = (int)((currentItem / (double)totalCount) * 100);

                    progress?.Report($"Thread {Thread.CurrentThread.ManagedThreadId}: {progressPercentage}% task execution");
                }

                jsonWriter.WriteEndArray();
                await jsonWriter.FlushAsync();
            }

            stream.Position = 0;

            progress?.Report($"Thread {Thread.CurrentThread.ManagedThreadId}: Writing completed");
        }
        finally
        {
            _semaphore.Release();
        }
    }


public async Task CopyFromStreamAsync(Stream stream, string filename, IProgress<string> progress)
{
    using (MemoryStream memoryStream = new MemoryStream())
    {
        await stream.CopyToAsync(memoryStream);
        memoryStream.Position = 0;

        await _semaphore.WaitAsync();
        try
        {
            using (StreamReader reader = new StreamReader(memoryStream))
            using (JsonWriter jsonWriter = new JsonTextWriter(new StreamWriter(filename)))
            {
                jsonWriter.WriteStartArray();

                while (reader.Peek() >= 0)
                {
                    string jsonLine = (await reader.ReadLineAsync())!;
                    await jsonWriter.WriteRawValueAsync(jsonLine);
                }

                jsonWriter.WriteEndArray();
                jsonWriter.Flush();
            }

            progress?.Report($"Thread {Thread.CurrentThread.ManagedThreadId}: 100% task execution (Copy completed)");
        }
        finally
        {
            _semaphore.Release();
        }
    }
}


    public async Task<int> GetStatisticsAsync(string fileName, Func<T, bool> filter)
    {
        int count = 0;

        using (StreamReader reader = new StreamReader(fileName))
        using (JsonReader jsonReader = new JsonTextReader(reader))
        {
            JsonSerializer serializer = new JsonSerializer();

            while (jsonReader.Read())
            {
                if (jsonReader.TokenType == JsonToken.StartObject)
                {
                    T? course = serializer.Deserialize<T>(jsonReader);
                    if (filter(course!))
                    {
                        count++;
                    }
                }
            }
        }

        return count;
    }
}

   

