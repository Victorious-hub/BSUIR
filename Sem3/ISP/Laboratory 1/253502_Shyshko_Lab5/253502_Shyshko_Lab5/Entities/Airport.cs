using System.Linq;

namespace _253502_Shyshko_Lab5.Entities;
using Contracts;
using Collections;
using System;

public class Airport : IAirport
{
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
                foreach (var t1 in tariffs)
                {
                    if (destination != t1.Destination) continue;
                    Ticket ticket = new Ticket(destination, date);
                    t.Tickets.Add(ticket);
                    flag = true;
                    break;
                }
            }
            if (flag) break;
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













