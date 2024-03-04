using MauiCalculatorAppShyshko.Services;
using NbrbAPI.Models;

namespace MauiCalculatorAppShyshko;

public partial class CurrencyConverterPage : ContentPage
{
    private readonly IRateService _rate;
    private bool lowerPicked = false;
    private bool upperPicked = false;
    private string selectedCurrency;
    public CurrencyConverterPage(IRateService service)
    {
        InitializeComponent();
        _rate = service;
        OnClearCurrency(this, null);
    }

    private void OnPickerSelectedIndexChanged(object sender, EventArgs e)
    {
        selectedCurrency = (string)lowerPicker.SelectedItem;
        UpdateRate();
    }

    private void OnDateSelected(object sender, DateChangedEventArgs e)
    {
        datePicker.Date = e.NewDate;
        UpdateRate();
    }

    private void OnCheck(Button button, string pressed)
    {
        Button targetLabel = upperPicked ? this.upperText : this.lowerText;

        if (button.Text == "." && targetLabel.Text.Contains("."))
        {
            return;
        }

        if (targetLabel.Text == "0" && (pressed != "0" && pressed != "."))
        {
            targetLabel.Text = "";
        }

        targetLabel.Text += pressed;
    }

    private void OnClearCurrency(object sender, EventArgs e)
    {
        this.upperText.Text = "0";
        this.lowerText.Text = "0";
    }
    private void OnDeleteSymbol(object sender, EventArgs e)
    {
        Button targetLabel = upperPicked ? this.upperText : this.lowerText;

        if (targetLabel.Text.Length > 1)
        {
            targetLabel.Text = targetLabel.Text.Remove(targetLabel.Text.Length - 1, 1);
        }
        else
        {
            targetLabel.Text = "0";
        }

        UpdateRate();
    }


    private void OnUpperPriority(object sender, EventArgs e)
    {
        Button button = (Button)sender;
        if (lowerPicked)
        {
            this.upperText.Text = "1";
        }
        upperPicked = true;
        lowerPicked = false;
        button.TextColor = Color.FromRgb(255, 165, 0);
        this.lowerText.TextColor = Color.FromRgb(255, 255, 255);
        
        UpdateRate();
    }
    private void OnLowerPriority(object sender, EventArgs e)
    {
        Button button = (Button)sender;
        if (upperPicked)
        {
            this.lowerText.Text = "1";
        }
        lowerPicked = true;
        upperPicked = false;
        button.TextColor = Color.FromRgb(255, 165, 0);
        this.upperText.TextColor = Color.FromRgb(255, 255, 255);
        UpdateRate();
    }

    private void OnGetCurrency(object sender, EventArgs e)
    {
        Button button = (Button)sender;
        string pressed = button.Text;
        if (lowerPicked)
        {
            selectedCurrency = "BEL";
        }
        selectedCurrency = (string)lowerPicker.SelectedItem;

        OnCheck(button, pressed);
        UpdateRate();
    }

    private async void UpdateRate()
    {
        var rates = await _rate.GetRates(datePicker.Date) as List<Rate>;

        decimal number;
        decimal conversionRate = 0;
        int curScale = 0;
        decimal offRate = 0;

        foreach (var rate in rates)
        {
            if (rate.Cur_Abbreviation == selectedCurrency)
            {
                curScale = rate.Cur_Scale;
                offRate = rate.Cur_OfficialRate;
            }

            if (upperPicked && rate.Cur_Abbreviation == selectedCurrency && decimal.TryParse(this.upperText.Text, out number))
            {
                conversionRate = number / offRate * curScale;
                this.lowerText.Text = conversionRate.ToString("N5");
            }

            if (rate.Cur_Abbreviation == selectedCurrency && lowerPicked && decimal.TryParse(this.lowerText.Text, out number))
            {
                conversionRate = number * offRate / curScale;
                this.upperText.Text = conversionRate.ToString("N5");
            }
        }
    }
}