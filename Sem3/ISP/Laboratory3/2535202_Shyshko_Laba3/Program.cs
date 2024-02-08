using System.Globalization;
using _2535202_Shyshko_Laba3.Entities;

namespace _2535202_Shyshko_Laba3;

class Program
{
    static void Main(string[] args)
    {

        
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
    
        Airport airport = new Airport();
        Journal journal = new Journal();
        
        airport.PassengerListChanged += journal.PassengerWasChanged;
        
        airport.TariffListChanged += journal.TariffWasChanged;
        
        airport.AddTariff("London", 1000);
        airport.AddTariff("Paris", 1500);
        airport.AddTariff("New York", 2000);

        airport.RegisterPassenger("Victor","123456");
        airport.RegisterPassenger("Polina","12345");
        airport.RegisterPassenger("Jenya","123451");

        airport.BuyAirportTicket("123456","Paris",DateInput());
        airport.BuyAirportTicket("12345","Paris",DateInput());
       

        Console.WriteLine(airport.CalculateTotalTicketCost("Victor"));
        
        Console.WriteLine(airport.CalculateTotalTicketCost());
        
        Console.WriteLine(airport.GetPassengerNameWithMaxPayment());

        airport.GetPaymentByDestination("Polina");
        
    }
}