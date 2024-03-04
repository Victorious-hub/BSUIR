using NbrbAPI.Models;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MauiCalculatorAppShyshko.Services
{
    public class RateService : IRateService
    {
        HttpClient _client;
        public RateService(HttpClient client)
        {
            _client = client;
        }

        public async Task<IEnumerable<Rate>> GetRates(DateTime date)
        {
            var response = await _client.GetAsync($"https://api.nbrb.by/exrates/rates?ondate={date.ToString("yyyy-MM-dd")}&periodicity=0");

            response.EnsureSuccessStatusCode();

            return JsonConvert.DeserializeObject<IEnumerable<Rate>>(await response.Content.ReadAsStringAsync());
        }
    }

}
