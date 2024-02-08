namespace _2535202_Shyshko_Laba3.Entities;

public class Ticket
{
    public Tariff Tariffs{ get; set; }
    public DateTime FlightDate { get; set; }
    public Ticket(Tariff d, DateTime flightDate)
    {
        Tariffs = d;
        FlightDate = flightDate;
    }
}