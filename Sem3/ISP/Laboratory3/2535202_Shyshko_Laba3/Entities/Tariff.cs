namespace _2535202_Shyshko_Laba3.Entities;

public class Tariff
{
    public string Destination { get; set; }
    public decimal Price { get; set; }

    public Tariff(string destination, decimal price)
    {
        Destination = destination;
        Price = price;
    }
}