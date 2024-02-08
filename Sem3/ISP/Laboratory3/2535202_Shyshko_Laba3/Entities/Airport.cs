namespace _2535202_Shyshko_Laba3.Entities;
using Contracts;
using Collections;
using System;

public class Airport : IAirport
{
    public Journal Journal = new();
    public class TariffChangedEventArgs : EventArgs
    {
        public string Description { get; set; }

        public TariffChangedEventArgs(string description)
        {
            Description = description;
        }
    }
    
    public class PassengerChangedEventArgs : EventArgs
    {
        public string Description { get; set; }

        public PassengerChangedEventArgs(string description)
        {
            Description = description;
        }
    }
    
    public class PassengerTicketPurchaseEventArgs : EventArgs
    {
        public string Description { get; set; }

        public PassengerTicketPurchaseEventArgs(string description)
        {
            Description = description;
        }
    }

    public delegate void PassengerListAction(object sender, PassengerChangedEventArgs e);
    public event PassengerListAction PassengerListChanged = delegate{};

    public delegate void TariffListAction(object sender, TariffChangedEventArgs e);
    public event TariffListAction TariffListChanged = delegate{};
    
    public delegate void TicketPurchasedChangedAction(object sender, PassengerTicketPurchaseEventArgs e);
    public event TicketPurchasedChangedAction TicketPurchasedChanged = delegate{};

    public void OnPassengerListChanged(string description)
    {
        PassengerListChanged?.Invoke(this, new PassengerChangedEventArgs(description));
    }

    public void OnTariffListChanged(string description)
    {
        TariffListChanged?.Invoke(this, new TariffChangedEventArgs(description));
    }

    public void OnTicketPurchasedHappened(string description)
    {
        TicketPurchasedChanged?.Invoke(this, new PassengerTicketPurchaseEventArgs(description));
    }
    
    private Dictionary<string,Tariff> tariffs = new();
    private List<Passenger> passengers = new();
    
    public void AddTariff(string destination, decimal price)
    {
        if (tariffs.ContainsKey(destination))
        {
            Console.WriteLine("Tariff destination already exists. Tariff not added.");
            return;
        }
        tariffs.Add(destination,new Tariff(destination,price));
   
        OnTariffListChanged($"New tariff was added: {destination}");
    }
    
    public void RegisterPassenger(string name, string passportNumber)
    {
        if (passengers.Any(p => p.PassportNumber == passportNumber))
        {
            Console.WriteLine("Passport number already exists. Passenger not added.");
            return;
        }
        
        Passenger passenger = new Passenger(name, passportNumber);
        passengers.Add(passenger);
 
        OnPassengerListChanged($"New passenger has been registered: {name}");
    }

    
    public void OutputPassengerByDate(DateTime date)
    {
        Console.WriteLine($"Passengers for {date.ToShortDateString()}:");
        bool flag = false;
        foreach (var passenger in passengers)
        {
            foreach (var ticket in passenger.Tickets)
            {
                if (ticket.FlightDate.Date == date.Date)
                {
                    Console.WriteLine($"Name: {passenger.Name}, Passport Number: {passenger.PassportNumber}, Destination: {ticket.Tariffs.Destination}");
                    flag = true;
                }
            }
        }

        if (!flag)
        {
            Console.WriteLine("Nothing Found");
        }
    }

    public void BuyAirportTicket(string passportNumber, string destination, DateTime date)
    {
        bool flag = false;
        foreach (var t in passengers)
        {
            if (t.PassportNumber.Equals(passportNumber))
            {
                if (tariffs.TryGetValue(destination, out var tariff))
                {
                    Ticket ticket = new Ticket(new Tariff(destination,tariff.Price),date);
                    t.Tickets.Add(ticket);
          
                    OnTicketPurchasedHappened($"Passenger {t.Name} got a ticket for: {destination}");
                    flag = true;
                }
            }
            if (flag) break;
        }

        if (!flag)
        {
            Console.WriteLine("Event didn't happen");
        }
    }

    public decimal CalculateTotalTicketCost(string passengerName)
    {
        foreach (var t in passengers)
        {
            if (!t.Name.Equals(passengerName)) continue;
            MyNumeric<decimal> totalCost = new MyNumeric<decimal>();
            foreach (Ticket ticket in t.Tickets)
            {
                if (tariffs.TryGetValue(ticket.Tariffs.Destination, out var tariff))
                {
                    MyNumeric<decimal> ticketPrice = new MyNumeric<decimal>(tariff.Price);
                    totalCost += ticketPrice;
                }
            }
            return totalCost.Value;
        }

        return 0;
    }
    
    public decimal CalculateTotalTicketCost()
    {
        return passengers.Sum(t => t.Tickets.Sum(ticket => tariffs.TryGetValue(ticket.Tariffs.Destination, out var tariff) ? tariff.Price : 0));
    }
    
   
    public int GetPassengerCount(decimal amount)
    {
        Console.WriteLine("Passenger Count");
        return passengers.Aggregate(0, (count, passenger) => count + (CalculateTotalTicketCost(passenger.Name) > amount ? 1 : 0));
    }
    
    public string GetPassengerNameWithMaxPayment()
    {
        Console.WriteLine("Passenger Name With Max Payment");
        var passengerWithMaxPayment = passengers.MaxBy(p => CalculateTotalTicketCost(p.Name));
        return passengerWithMaxPayment?.Name;
    }
    
    public Dictionary<string, decimal> GetPaymentByDestination(string passengerName)
    {
        var passenger = passengers.FirstOrDefault(p => p.Name == passengerName);
        if (passenger == null)
        {
            return null;
        }

        var paymentByDestination = passenger.Tickets.GroupBy(t => t.Tariffs.Destination)
            .ToDictionary(g => g.Key, g =>
                g.Sum(t => tariffs.TryGetValue(t.Tariffs.Destination, out var tariff) ? tariff.Price : 0));

        return paymentByDestination;
    }

    public IEnumerable<KeyValuePair<string, decimal>> GetSortedTariffNames()
    {
        var sortedTariffs = tariffs.OrderBy(t => t.Value.Destination)
            .Select(t => new KeyValuePair<string, decimal>(t.Key, t.Value.Price));
        return sortedTariffs;
    }
    
}