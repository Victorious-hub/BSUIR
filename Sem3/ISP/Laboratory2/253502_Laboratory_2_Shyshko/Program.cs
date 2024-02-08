using System.Globalization;
using _253502_Laboratory_2_Shyshko.Collections;
using _253502_Laboratory_2_Shyshko.Entities;
using _253502_Laboratory_2_Shyshko.Exceptions;

namespace _253502_Laboratory_2_Shyshko;

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
        
        Journal journal = new Journal();
        MyCustomCollection<Tariff> tariffs = new MyCustomCollection<Tariff>();
        MyCustomCollection<Passenger> passengers = new MyCustomCollection<Passenger>();
        Airport airport = new Airport(); 
        
        airport.PassengerListChanged += (sender, e) =>
        {
            journal.PassengerWasChanged(sender, e);
        };
        
        airport.TariffListChanged += (sender,e) =>
        {
            journal.TariffWasChanged(sender, e);
        };
        
        airport.TicketPurchasedChanged += (sender,e) =>
        {
            journal.TicketPurchased(sender,e);
        };

        airport.AddTariff("London", 1000);
        airport.AddTariff("Paris", 1500);
        airport.AddTariff("New York", 2000);
        
        airport.RegisterPassenger("Victor","123456");
        airport.RegisterPassenger("Polina","12345");
        airport.RegisterPassenger("Jenya","123451");
        
        
        tariffs.Add(new Tariff { Destination = "New York", Price = 1000 });
        tariffs.Add(new Tariff { Destination = "London", Price = 2000 });
        
        
        passengers.Add(new Passenger("John", "123"));
        passengers.Add(new Passenger("Alice", "456"));
        
       airport.BuyAirportTicket("123456", "New York",DateInput());
       
       journal.EventList();
        
        MyCustomCollection<int> collection = new MyCustomCollection<int>();
        try
        {
            Console.WriteLine(collection[3]); 
        }
        catch (IndexOutOfRangeException e)
        {
            Console.WriteLine("Exception caught: " + e.Message);
        }
        
        try
        {
            collection[3] = 4; 
        }
        catch (IndexOutOfRangeException e)
        {
            Console.WriteLine("Exception caught: " + e.Message); 
        }
        
        try
        {
            collection.Remove(5);
            ItemNotExists m;
            m = new ItemNotExists("Item doesn't exist");
            throw m;
        }
        
        catch (ItemNotExists e)
        {
            Console.WriteLine($"{e.StackTrace}\n{e.Message}");
        }
    }
}