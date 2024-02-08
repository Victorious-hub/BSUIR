using System.Diagnostics;
namespace IntegralCalculation
{
    public class IntegralCalculation
    {
        
        public class TimeElapsedEventArgs : EventArgs
        {
            public double Time { get; set; }

            public TimeElapsedEventArgs(double time)
            {
                Time = time;
            }
        }
        
        public class ProgressReportEventArgs : EventArgs
        {
            public double Time { get; set; }

            public ProgressReportEventArgs(double time)
            {
                Time = time;
            }
        }
        
        public delegate void TimeElapsedEventHandler(object sender, TimeElapsedEventArgs e);
        public event TimeElapsedEventHandler TimeElapsed = delegate{};
        
        public delegate void ProgressReportEventHandler(object sender, ProgressReportEventArgs e);
        public event ProgressReportEventHandler ProgressReported  = delegate{};

        private Semaphore _semaphore = new Semaphore(2, 2);

        public void CalculateIntegral()
        {
            _semaphore.WaitOne();
            try
            {
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                double a = 0;
                double b = 1;
                double step = 0.00001;

                double sum = 0;
                double x = a;

                while (x < b)
                {
                    sum += Math.Sin(x) * step;
                    x += step;
                    var progress = (x - a) / (b - a);
                    OnProgressReported(progress * 100);

                    for (int i = 0; i < 100000; i++)
                    {
                        int result = i * i;
                    }
                }

                stopwatch.Stop();
                OnTimeElapsed(stopwatch.Elapsed.TotalMilliseconds);
            }
            finally
            {
                _semaphore.Release();
            }
        }

        private void OnTimeElapsed(double timeElapsed)
        {
            TimeElapsed?.Invoke(this, new TimeElapsedEventArgs(timeElapsed));
        }

        private void OnProgressReported(double progress)
        {
            ProgressReported?.Invoke(this, new ProgressReportEventArgs(progress));
        }
    }
}