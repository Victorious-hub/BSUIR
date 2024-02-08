using System;

namespace _253502_Shyshko_Lab5.Entities;

public class Ticket
{
    public string Destination { get; set; }
    public DateTime FlightDate { get; set; }

    public Ticket(string destination, DateTime flightDate)
    {
        Destination = destination;
        FlightDate = flightDate;
    }
}