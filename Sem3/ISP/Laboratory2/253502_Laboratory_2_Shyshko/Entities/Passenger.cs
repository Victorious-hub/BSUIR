using _253502_Laboratory_2_Shyshko.Collections;

namespace _253502_Laboratory_2_Shyshko.Entities;

public class Passenger
{
    public string Name { get; set; }
    public string PassportNumber { get; set; }
    public MyCustomCollection<Ticket> Tickets{ get; set; }
    public Passenger(){}
    public Passenger(string name, string passportNumber)
    {
        Name = name;
        PassportNumber = passportNumber;
        Tickets = new MyCustomCollection<Ticket>();
    }
    
}