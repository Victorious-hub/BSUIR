namespace _253502_Shyshko_Lab5.Entities;
using Collections;
public class Passenger
{
    public string Name { get; set; }
    public string PassportNumber { get; set; }
    public MyCustomCollection<Ticket> Tickets{ get; set; }
    public Passenger(string name, string passportNumber)
    {
        Name = name;
        PassportNumber = passportNumber;
        Tickets = new MyCustomCollection<Ticket>();
    }
    
}