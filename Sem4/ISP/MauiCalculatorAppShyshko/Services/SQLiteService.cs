using MauiCalculatorAppShyshko.Models;
using SQLite;
using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using static MauiCalculatorAppShyshko.Models.SQLiteDBContext;

namespace MauiCalculatorAppShyshko.Services
{
    public class SQLiteService : IDbService
    {
        const string DbName = "database.db";
        public static string DbPath => Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), DbName);
        private SQLiteConnection _database;

        const SQLite.SQLiteOpenFlags Flags =
                SQLite.SQLiteOpenFlags.ReadWrite |
                SQLite.SQLiteOpenFlags.Create |
                SQLite.SQLiteOpenFlags.SharedCache;

        public SQLiteService()
        {
            Init();
        }

        public void Init()
        {
            _database = new SQLiteConnection(DbPath, Flags);
            _database.CreateTable<Author>();
            _database.CreateTable<Book>();

            var authors = new List<Author>
            {
                new Author { FirstName = "Author", LastName = "LastName1", Age = 30 },
                new Author { FirstName = "Authorkhuohuo2", LastName = "LastName2", Age = 40 },
                new Author { FirstName = "Authorfugyihoj3", LastName = "LastName3", Age = 50 },
            };

            foreach (var author in authors)
            {
                _database.Insert(author);
            }

            var books = new List<Book>
            {
                new Book { Title = "Book1", Description = "Description1", DatePublished = DateTime.Now, AuthorId = 1 },
                new Book { Title = "Book2", Description = "Description2", DatePublished = DateTime.Now, AuthorId = 2 },
                new Book { Title = "Book3", Description = "Description3", DatePublished = DateTime.Now, AuthorId = 3 },
            };

            foreach (var book in books)
            {
                _database.Insert(book);
            }
        }
        public IEnumerable<Author> GetAuthors()
        {
            return _database.Table<Author>().ToList();
        }

        public IEnumerable<Book> GetAuthorBooks(int id)
        {
            return _database.Table<Book>().Where(b => b.AuthorId == id).ToList();
        }
    }
}
