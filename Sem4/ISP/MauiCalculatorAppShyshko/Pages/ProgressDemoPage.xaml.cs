using CommunityToolkit.Maui.Views;
using System;
using System.Diagnostics;
using System.Runtime.CompilerServices;
namespace MauiCalculatorAppShyshko;
public partial class ProgressDemoPage : ContentPage
{
    private CancellationTokenSource cts;
    private bool isStart = false;
    private bool isCompleted = false;

    private async Task AnimateButtonColorChange(Button button)
    {
        Color originalColor = button.BackgroundColor;

        await button.FadeTo(0.5, 300);
        button.BackgroundColor = button.BackgroundColor;
        await button.FadeTo(1, 200);
        button.BackgroundColor = originalColor;
    }
    private async Task OnStartCalculationAsync(Button button, CancellationToken token)
    {
        double a = 0;
        double b = 1;
        double progress = 0;
        double step = 0.000001;

        double sum = 0;
        double x = a;

        while (x < b)
        {
            if (progressBar.Progress == 1 && !isCompleted)
            {
                this.startText.Text = "Calculated!";
                this.ShowPopup(new PopupPage($"Calculation result: {sum}"));
                isCompleted = true;
                return;
            }

            sum += Math.Sin(x) * step;
            x += step;
            progress = (x - a) / (b - a);

            MainThread.BeginInvokeOnMainThread(() => progressBar.Progress += (progress * 1000));
            this.progressText.Text = (progressBar.Progress * 100).ToString("N0") + "%";
            await Task.Delay(1000);

            if (cts.IsCancellationRequested)
            {
                return;
            }
        }
    }

    public ProgressDemoPage()
	{
        InitializeComponent();
    }

    private async void OnStart(object sender, EventArgs e)
    {
        Button button = (Button)sender;
        cts = new CancellationTokenSource();
        isStart = true;
        if (progressBar.Progress == 1)
        {
            progressBar.Progress = 0;
            isCompleted = false;
        }
        this.startText.Text = "Calculating...";
        await AnimateButtonColorChange(button);
        await OnStartCalculationAsync(button, cts.Token);
    }

    private async void OnCancel(object sender, EventArgs e)
    {
        Button button = (Button)sender;
        if (progressBar.Progress == 1)
        {
            this.startText.Text = "Already calculated";
        }

        if (!isStart)
        {
            this.ShowPopup(new PopupPage());
        }

        if (cts != null)
        {
            cts.Cancel();
            this.startText.Text = "Task canceled";
        }

        await AnimateButtonColorChange(button);
    }

}
