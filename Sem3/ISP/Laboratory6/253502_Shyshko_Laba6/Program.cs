using System;
using System.Collections.Generic;
using System.Linq;
using _253502_Shyshko_Laba6.Entities;
using System.Reflection;

var employees = new List<Employee>
{
    new() { Name = "John", Age = 30, Salary = 50000 },
    new() { Name = "Jane", Age = 25, Salary = 40000 },
    new() { Name = "Bob", Age = 40, Salary = 60000 }
};

Assembly asm = Assembly.LoadFrom("FileService.dll");
Type? t = asm.GetTypes().FirstOrDefault(type => type.Name.StartsWith("FileService`1"));

if (t is not null)
{
    Type closedType = t.MakeGenericType(typeof(Employee));

    MethodInfo? saveDataMethod = closedType.GetMethod("SaveData");
    object? fileServiceInstance = Activator.CreateInstance(closedType);

    saveDataMethod?.Invoke(fileServiceInstance, new object[] { employees, "employees.json" });
    
    MethodInfo? readDataMethod = closedType.GetMethod("ReadFile");
    IEnumerable<Employee>? employee = readDataMethod?.Invoke(fileServiceInstance, new object[] { "employees.json" }) as IEnumerable<Employee>;
    
    if (employee != null)
        foreach (var passenger in employee)
        {
            Console.WriteLine($"Passenger Name: {passenger.Name}");
            Console.WriteLine($"Passenger Age: {passenger.Age}");
            Console.WriteLine($"Passenger Salary: {passenger.Salary}");
        }
}
