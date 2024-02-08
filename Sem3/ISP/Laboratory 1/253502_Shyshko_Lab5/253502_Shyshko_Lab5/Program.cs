using System;
using System.Globalization;
using _253502_Shyshko_Lab5.Entities;

DateTime DateInput()
{
    while (true)
    {
        Console.WriteLine("Enter date (yyyy-MM-dd)");
        string inputDate = Console.ReadLine();
        
        DateTime date;
        if (!DateTime.TryParseExact(inputDate, "yyyy-MM-dd", CultureInfo.InvariantCulture, DateTimeStyles.None,
                out date))
        {
            Console.WriteLine("Invalid date format. Please enter a valid date in yyyy-MM-dd format.");
            continue;
        }

        return date;
    }
}

var airport = new Airport();
airport.AddTariff("London", 1000);
airport.AddTariff("Paris", 1500);
airport.AddTariff("Paris", 2000);

airport.RegisterPassenger("Victor","123456");
airport.RegisterPassenger("Polina","12345");
airport.RegisterPassenger("Jenya","12345");



    airport.BuyAirportTicket("123456","Paris",DateInput());
    airport.BuyAirportTicket("12345","Paris",DateInput());

    Console.WriteLine(airport.CalculateTotalTicketCost("Victor"));
    airport.OutputPassengerByDate(DateInput());



