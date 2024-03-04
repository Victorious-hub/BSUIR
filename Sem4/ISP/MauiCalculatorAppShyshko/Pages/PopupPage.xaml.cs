using CommunityToolkit.Maui.Views;

namespace MauiCalculatorAppShyshko;

public partial class PopupPage : Popup
{ 
    private async Task AnimateButtonColorChange(Button button)
    {
        Color originalColor = button.BackgroundColor;

        await button.FadeTo(0.5, 300);
        button.BackgroundColor = button.BackgroundColor;
        await button.FadeTo(1, 200);
        button.BackgroundColor = originalColor;
    }
    public PopupPage(string text)
	{
		InitializeComponent();
		this.popupText.Text = text;
	}

    public PopupPage()
    {
        InitializeComponent();
    }

    private async void onClickClose(object sender, EventArgs e)
	{
        Button button = (Button)sender;
        this.Close();
        await AnimateButtonColorChange(button);
    }
}