using System;
using SQLite;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics.Contracts;
using System.Net.Http.Headers;

namespace MauiCalculatorAppShyshko.Models
{
    public class SQLiteDBContext
    {
        [Table("Author")]
        public class Author
        {
            [PrimaryKey, AutoIncrement, Indexed]
            public int Id { get; set; }
            public string FirstName { get; set; }
            public string LastName { get; set; }
            public int Age { get; set; }
        }

        [Table("Book")]
        public class Book
        {
            [PrimaryKey, AutoIncrement, Indexed]
            [Column("Id")]
            public int BookId { get; set; }
            public string Title { get; set; }
            public string Description { get; set; }
            public DateTime DatePublished { get; set; }
            [Indexed]
            public int AuthorId { get; set; }
        }
    }
}
