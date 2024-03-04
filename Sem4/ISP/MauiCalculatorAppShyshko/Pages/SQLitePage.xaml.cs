using MauiCalculatorAppShyshko.Models;
using MauiCalculatorAppShyshko.Services;

namespace MauiCalculatorAppShyshko
{
    public partial class SQLitePage : ContentPage
    {
        IDbService _service;
        public SQLitePage(IDbService service)
        {
            InitializeComponent();
            _service = service;
            var authors = _service.GetAuthors().ToList();
            foreach (var author in authors)
            {
                authorPicker.Items.Add(author.FirstName + " " + author.LastName);
            }

            authorPicker.SelectedIndexChanged += (s, e) =>
            {
                if (authorPicker.SelectedIndex != -1)
                {
                    var selectedAuthor = authors[authorPicker.SelectedIndex];
                    var books = _service.GetAuthorBooks(selectedAuthor.Id);
                    booksCollectionView.ItemsSource = books;
                }
            };
        }
    }
}