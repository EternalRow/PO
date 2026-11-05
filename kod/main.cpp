#include "system_rezerwacji.hpp"
#include "klient.hpp"
#include "pojazd.hpp"
#include <iostream>
#include <string>
#include <clocale>
using namespace std;



int main(){
    setlocale(LC_ALL, "pl_PL.UTF-8");//kodowanie znakow
    
    SystemRezerwacji system = SystemRezerwacji();
    //system.dodajPojazd(Pojazd('Audi', 'A10', '2015', 'FZA8310', Data(12,10,2026), 1));
    system.dodajPojazd(Pojazd("Audi", "A10", 2015, "FZA8310", Data(12,10,2026), 1));
    system.dodajPojazd(Pojazd("Honda", "Civic", 2011, "FZG810", Data(12,10,2026), 1));
    system.dodajPojazd(Pojazd("Renault", "Clio", 2009, "POZ879", Data(12,10,2026), 1));
    
    vector<Klient> klientela = {Klient("Jan", "Kowalski", "email@example.com", 10), Klient("Anna", "Nowak", "anna@example.com", 11)};
    system.katalog();
    
}