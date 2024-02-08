namespace _253502_Laboratory_2_Shyshko.Entities;

using Contracts;
using Collections;
using System;

public class Airport : IAirport
{
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
    
    private MyCustomCollection<Tariff> tariffs = new();
    private MyCustomCollection<Passenger> passengers = new();
    
    public void AddTariff(string destination, decimal price)
    {
        if (tariffs.Any(p => p.Destination == destination))
        {
            Console.WriteLine("Tariff destination already exists. Tariff not added.");
            return;
        }
        Tariff tariff = new Tariff { Destination = destination, Price = price };
        tariffs.Add(tariff);
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
                    Console.WriteLine($"Name: {passenger.Name}, Passport Number: {passenger.PassportNumber}, Destination: {ticket.Destination}");
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
                if (tariffs.Any(t1 => destination == t1.Destination))
                {
                    Ticket ticket = new Ticket(destination, DateTime.Today);
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
                foreach (var t1 in tariffs)
                {
                    if (!t1.Destination.Equals(ticket.Destination)) continue;
                    MyNumeric<decimal> ticketPrice = new MyNumeric<decimal>(t1.Price);
                    totalCost += ticketPrice;
                    break;
                }
            }
            return totalCost.Value;
        }

        return 0;
    }

    
}