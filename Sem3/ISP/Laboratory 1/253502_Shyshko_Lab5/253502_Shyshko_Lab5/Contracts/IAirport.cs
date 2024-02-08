using System;
using _253502_Shyshko_Lab5.Entities;

namespace _253502_Shyshko_Lab5.Contracts;

public interface IAirport
{
    void AddTariff(string destination, decimal price);
    void RegisterPassenger(string name, string passportNumber);
    void OutputPassengerByDate(DateTime date);
    decimal CalculateTotalTicketCost(string passengerName);
    void BuyAirportTicket(string passportNumber, string destination, DateTime date);
}