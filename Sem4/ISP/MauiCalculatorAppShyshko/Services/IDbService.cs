using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static MauiCalculatorAppShyshko.Models.SQLiteDBContext;

namespace MauiCalculatorAppShyshko.Services
{
    public interface IDbService
    {
        IEnumerable<Author> GetAuthors();
        IEnumerable<Book> GetAuthorBooks(int id);
        void Init();
    }
}
