namespace MauiCalculatorAppShyshko;

public partial class CalculatorPage : ContentPage
{
    private string currentEntry = "";
    private bool isFirst = false;
    private bool isPressed = false;
    private bool isEmpty = true;
    private bool IsChecked = false;
    private string mathOperator;
    private double firstNumber, secondNumber;
    private string decimalFormat = "N0";
    public CalculatorPage()
    {
        InitializeComponent();
        OnClear(this, null);
    }

    private async Task AnimateButtonColorChange(Button button)
    {
        Color originalColor = button.BackgroundColor;

        await button.FadeTo(0.5, 300);
        button.BackgroundColor = button.BackgroundColor;
        await button.FadeTo(1, 200);
        button.BackgroundColor = originalColor;
    }

    private void OnClear(object sender, EventArgs e)
    {
        firstNumber = 0;
        secondNumber = 0;
        decimalFormat = "N0";
        this.resultText.Text = "0";
        this.currentNumber.Text = "";
        currentEntry = string.Empty;
        isFirst = false;
        isEmpty = true;
        isPressed = false;
    }

    private async void Calculation(object sender, EventArgs e)
    {
        if (isFirst && !IsChecked)
        {
            this.resultText.Text = "";
            IsChecked = true;
        }

        Button button = (Button)sender;
        string pressed = button.Text;

        if (pressed == "." && this.resultText.Text.Contains("."))
        {
            return;
        }

        if (currentEntry.Length == 0 && pressed == ".")
        {
            currentEntry = "0";
            this.resultText.Text = "0";
        }

        currentEntry += pressed;

        if ((this.resultText.Text == "0" && pressed == "0") || (currentEntry.Length <= 1 && pressed != "0"))
        {
            this.resultText.Text = "";
        }

        if (isEmpty)
        {
            this.currentNumber.Text += "= ";
            isEmpty = false;
        }

        this.resultText.Text += pressed;
        this.currentNumber.Text += pressed;

        await AnimateButtonColorChange(button);
    }

    private async void OnSelectOperator(object sender, EventArgs e)
    {
        Button button = (Button)sender;
        string pressed = button.Text;
        isPressed = false;
        mathOperator = pressed;

        if (double.TryParse(this.resultText.Text, out firstNumber) && isFirst == false)
        {
            isFirst = true;
            if (decimalFormat == "N2")
            {
                decimalFormat = "N0";
            }
            this.currentNumber.Text += pressed;
            return;
        }

        if (this.currentNumber.Text.Contains("+")
            || (this.currentNumber.Text.Contains("-") && firstNumber >= 0)
            || this.currentNumber.Text.Contains("×")
            || this.currentNumber.Text.Contains("÷"))
        {
            this.currentNumber.Text = this.currentNumber.Text.Substring(0, this.currentNumber.Text.Length - 1);
            this.currentNumber.Text += pressed;
        }
        else
        {
            this.currentNumber.Text += pressed;
        }

        await AnimateButtonColorChange(button);
    }

    private async void OnDeleteSymbol(object sender, EventArgs e)
    {
        Button button = (Button)sender;
        
        if (!string.IsNullOrEmpty(this.resultText.Text))
        {
            this.resultText.Text = this.resultText.Text.Substring(0, this.resultText.Text.Length - 1);
        }

        if (!string.IsNullOrEmpty(this.currentNumber.Text))
        {
            this.currentNumber.Text = this.currentNumber.Text.Substring(0, this.currentNumber.Text.Length - 1);
            if (this.resultText.Text == "")
            {
                this.currentNumber.Text = "";
                isEmpty = true;
            }
        }

        await AnimateButtonColorChange(button);
    }

    private async void OnFraction(object sender, EventArgs e)
    {
        double result;
        Button button = (Button)sender;

        if (double.TryParse(this.resultText.Text, out result))
        {
            result = 1 / result;
            this.resultText.Text = result == (int)result ? result.ToString("N0") : result.ToString("N8");
            this.currentNumber.Text = "=" + " " + this.resultText.Text;
        }

        await AnimateButtonColorChange(button);
    }
    private async void OnSquareDegree(object sender, EventArgs e)
    {
        double result;
        Button button = (Button)sender;
     
        if (double.TryParse(this.resultText.Text, out result))
        {
            result = Math.Pow(result, 2);
            this.resultText.Text = result == (int)result ? result.ToString("N0") : result.ToString("N2");
            this.currentNumber.Text = "=" + " " + this.resultText.Text;
        }

        await AnimateButtonColorChange(button);
    }
    private async void OnSquareRoot(object sender, EventArgs e)
    {
        double result;
        Button button = (Button)sender;

        if (double.TryParse(this.resultText.Text, out result))
        {
            result = Math.Sqrt(result);
            this.resultText.Text = result == (int)result ? result.ToString("N0") : result.ToString("N8");
            this.currentNumber.Text = "=" + " " + this.resultText.Text;
        }

        await AnimateButtonColorChange(button);
    }
    private async void OnLogCalculation(object sender, EventArgs e)
    {
        double result;
        Button button = (Button)sender;

        if (double.TryParse(this.resultText.Text, out result))
        {
            result = Math.Log2(result);
            this.resultText.Text = result == (int)result ? result.ToString("N0") : result.ToString("N8");
            this.currentNumber.Text = "=" + " " + this.resultText.Text;
        }

        await AnimateButtonColorChange(button);
    }

    private async void OnPercentage(object sender, EventArgs e)
    {
        double result;
        Button button = (Button)sender;

        if (double.TryParse(this.resultText.Text, out result))
        {
            result /= 100;
            this.resultText.Text = result == (int)result ? result.ToString("N0") : result.ToString("N2");
            this.currentNumber.Text = "=" + " " + this.resultText.Text;
        }

        await AnimateButtonColorChange(button);
    }
    private async void OnCalculate(object sender, EventArgs e)
    {
        Button button = (Button)sender;


        if (!isPressed)
        {
            double result = 0;
            if (double.TryParse(this.resultText.Text, out secondNumber))
            {
                switch (mathOperator)
                {
                    case "÷":
                        result = firstNumber / secondNumber;
                        break;
                    case "-":
                        result = firstNumber - secondNumber;
                        break;
                    case "×":
                        result = firstNumber * secondNumber;
                        break;
                    case "+":
                        result = firstNumber + secondNumber;
                        break;
                    default:
                        break;
                }

                this.resultText.Text = result == (int)result ? result.ToString("N0") : result.ToString("N2");
                this.currentNumber.Text = "=" + " " + this.resultText.Text;
                isPressed = true;
                firstNumber = result;
                IsChecked = false;

                await AnimateButtonColorChange(button);
            }
        }

    }
}