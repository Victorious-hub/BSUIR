using System.Collections.Concurrent;
class Program
{
    
    static ConcurrentDictionary<int, double> _results = new ();
    static void Main(string[] args)
    {
                var obj = new IntegralCalculation.IntegralCalculation();

                obj.TimeElapsed += TimeElapsedHandler;
                obj.ProgressReported += ProgressReportedHandler;
                
                Thread threadHighest = new Thread(() =>
                {
                    Thread.CurrentThread.Priority = ThreadPriority.Highest;
                    obj.CalculateIntegral();
                });

                Thread threadLowest = new Thread(() =>
                {
                    Thread.CurrentThread.Priority = ThreadPriority.Lowest;
                    obj.CalculateIntegral();
                });

                Thread threadHighest1 = new Thread(() =>
                {
                    Thread.CurrentThread.Priority = ThreadPriority.Highest;
                    obj.CalculateIntegral();
                });

                Thread threadLowest1 = new Thread(() =>
                {
                    Thread.CurrentThread.Priority = ThreadPriority.Lowest;
                    obj.CalculateIntegral();
                });

                Thread threadHighest2 = new Thread(() =>
                {
                    Thread.CurrentThread.Priority = ThreadPriority.Highest;
                    obj.CalculateIntegral();
                });

                Thread threadLowest2 = new Thread(() =>
                {
                    Thread.CurrentThread.Priority = ThreadPriority.Lowest;
                    obj.CalculateIntegral();
                });


                threadHighest.Start();
                threadLowest.Start();
                threadHighest1.Start();
                threadLowest1.Start();
                threadHighest2.Start();
                threadLowest2.Start();
    }

    public static void TimeElapsedHandler(object sender, IntegralCalculation.IntegralCalculation.TimeElapsedEventArgs e)
    {
        _results.TryAdd(Thread.CurrentThread.ManagedThreadId, e.Time);
        foreach (var result in _results)
        {
            Console.WriteLine($"Thread {result.Key} was finished with the result: {result.Value} ms");
        }
    }

    public static void ProgressReportedHandler(object sender, IntegralCalculation.IntegralCalculation.ProgressReportEventArgs e)
    {
        int progress = (int)e.Time;
        int totalBlocks = 10;
        int filledBlocks = progress / 10;
        int emptyBlocks = totalBlocks - filledBlocks;

        string progressBar = $"[{new string('=', filledBlocks)}{new string('>', 1)}{new string(' ', emptyBlocks)}]";

        Console.WriteLine($"Thread {Thread.CurrentThread.ManagedThreadId}: {progressBar} {progress}%");
    }
}