using _253502_Laboratory_2_Shyshko.Collections;

namespace _253502_Laboratory_2_Shyshko.Entities;
public class Journal
{
    private MyCustomCollection<string> _events = new MyCustomCollection<string>();
    public void PassengerWasChanged(object sender, Airport.PassengerChangedEventArgs e)
    {
        string logEntry = $"PassengerChanged event has happened: {e.Description}";
        _events.Add(logEntry);
        Console.WriteLine(logEntry);
    }
    
    public void TariffWasChanged(object sender, Airport.TariffChangedEventArgs e)
    {
        string logEntry = $"TariffWasChanged event has happened: {e.Description}";
        _events.Add(logEntry);
        Console.WriteLine(logEntry);
    }
    
    public void TicketPurchased(object sender, Airport.PassengerTicketPurchaseEventArgs e)
    {
        string logEntry = $"TicketPurchased event has happened: {e.Description}";
        _events.Add(logEntry);
        Console.WriteLine(logEntry);
    }

    public void EventList()
    {
        Console.WriteLine("Registered events list");
        for (int i = 0; i < _events.Count; ++i)
        {
            Console.WriteLine(_events[i]);
        }
    }
    
}

