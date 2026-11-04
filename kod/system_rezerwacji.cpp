#include "system_rezerwacji.hpp"
#include <bits/stdc++.h> // do funkcji find
#include <iostream>

SystemRezerwacji::SystemRezerwacji(const vector<Klient> klienci, const vector<Pracownik> pracownicy, const vector<Pojazd> pojazdy, const vector<Rezerwacja> rezerwacje, const vector<Pojazd> dostepne, const vector<Platnosc> platnosci)
    : klienci(klienci), platnosci(platnosci), pracownicy(pracownicy), pojazdy(pojazdy), rezerwacje(rezerwacje), dostepne(dostepne) {}

SystemRezerwacji::~SystemRezerwacji() = default;

const vector<Klient>& SystemRezerwacji::zwrocKlienci() const{
    return klienci;
}
void SystemRezerwacji::ustawKlienci(const vector<Klient>& val){
    klienci = val;
}

const vector<Platnosc>& SystemRezerwacji::zwrocPlatnosci() const{
    return platnosci;
}
void SystemRezerwacji::ustawPlatnosci(const vector<Platnosc>& val){
    platnosci = val;
}

const vector<Pracownik>& SystemRezerwacji::zwrocPracownicy() const{
    return pracownicy;
}
void SystemRezerwacji::ustawPracownicy(const vector<Pracownik>& val){
    pracownicy = val;
}

const vector<Pojazd>& SystemRezerwacji::zwrocPojazdy() const{
    return pojazdy;
}
void SystemRezerwacji::ustawPojazdy(const vector<Pojazd>& val){
    pojazdy = val;
}

const vector<Rezerwacja>& SystemRezerwacji::zwrocRezerwacje() const{
    return rezerwacje;
}
void SystemRezerwacji::ustawRezerwacje(const vector<Rezerwacja>& val){
    rezerwacje = val;
}
const vector<Pojazd>& SystemRezerwacji::zwrocDostepne() const{
    return dostepne;
}
void SystemRezerwacji::ustawDostepne(const vector<Pojazd>& val){
    dostepne = val;
}

bool SystemRezerwacji::zarezerwuj(int id_osoby, Pojazd pojazd, Data data_wypozyczenia, Data data_zwrotu, int okres_wypozyczenia){
    int id_rezerwacji = rezerwacje.size()+1;
    
    vector<PozycjaRezerwacji> pozycja;
    pozycja.push_back(PozycjaRezerwacji(pojazd));
    Rezerwacja nowa_rezerwacja = Rezerwacja(id_rezerwacji, pozycja, data_wypozyczenia, 0, 0, data_zwrotu, id_osoby);
    rezerwacje.push_back(nowa_rezerwacja);

    float kwota = 200*okres_wypozyczenia;
    const Data data_przelewu = Data(0,0,0);
    int id_platnosci = platnosci.size()+1;
    Platnosc nowa_platnosc = Platnosc(data_przelewu, kwota, 0, id_rezerwacji, id_platnosci);
    platnosci.push_back(nowa_platnosc);

    dostepne.erase(find(dostepne.begin(), dostepne.end(), pojazd)); // usuniecie pojazdu z dostepnych
    //czy nie powinno zwracac do maina platnosci i rezerwacji?
    return 0;

}

void SystemRezerwacji::katalog() const{
    cout << "Dostępne pojazdy:" << endl;
    for(int i =0; i<dostepne.size(); i++){
        cout << i+1;
        dostepne[i].wypisz();
    }
}
