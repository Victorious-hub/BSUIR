namespace _2535202_Shyshko_Laba3.Entities;

using _2535202_Shyshko_Laba3.Collections;

public class Passenger
{
    public string Name { get; set; }
    public string PassportNumber { get; set; }
    public List<Ticket> Tickets{ get; set; }
    public Passenger(){}
    public Passenger(string name, string passportNumber)
    {
        Name = name;
        PassportNumber = passportNumber;
        Tickets = new  List<Ticket>();
    }
    
}