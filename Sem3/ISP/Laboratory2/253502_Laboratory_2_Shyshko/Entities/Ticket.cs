namespace _253502_Laboratory_2_Shyshko.Entities;

public class Ticket
{
    public string Destination { get; set; }
    public DateTime FlightDate { get; set; }
    public Ticket(){}
    public Ticket(string destination, DateTime flightDate)
    {
        Destination = destination;
        FlightDate = flightDate;
    }
}