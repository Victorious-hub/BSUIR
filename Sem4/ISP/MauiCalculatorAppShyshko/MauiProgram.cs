using Microsoft.Extensions.Logging;
using MauiCalculatorAppShyshko;
using CommunityToolkit.Maui;
using MauiCalculatorAppShyshko.Services;

public static class MauiProgram
{
    public static MauiApp CreateMauiApp()
    {
        var builder = MauiApp.CreateBuilder();
        builder.UseMauiApp<App>().ConfigureFonts(fonts =>
        {
            fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
            fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
        }).UseMauiCommunityToolkit();
        
#if DEBUG
        builder.Logging.AddDebug();
#endif
        builder.Services.AddTransient<IDbService, SQLiteService>();
        builder.Services.AddSingleton<SQLitePage>();

        builder.Services.AddHttpClient<IRateService, RateService>(opt =>
            opt.BaseAddress = new Uri("https://www.nbrb.by/api/exrates/rates"));
        builder.Services.AddSingleton<CurrencyConverterPage>();
        return builder.Build();
    }
}