/*
Oznaczenia statusu rezeerwacji:
0 - niezaplacone; nieaktywna
1 - aktywna, oplacona;
2 - zwrocono pojazdy, nieoplacono platnosci dodatkowej
3 - rezerwacja zamknięta;
*/

#include "rezerwacja.hpp"

Rezerwacja::Rezerwacja(int id, const vector<PozycjaRezerwacji> pojazdy, const Data& dataRezerwacji, int status, bool przedluzono, int okresWypozyczenia, const Klient& klient, const Platnosc& oplataRezerwacji, const Platnosc& oplataDodatkowa)
    : id(id), pojazdy(pojazdy), dataRezerwacji(dataRezerwacji), status(status), przedluzono(przedluzono), okresWypozyczenia(okresWypozyczenia), klient(klient), oplataRezerwacji(oplataRezerwacji), oplataDodatkowa(oplataDodatkowa) {}

Rezerwacja::~Rezerwacja() = default;

int Rezerwacja::zwrocId() const{
    return id;
}

void Rezerwacja::ustawId(int val){
    id = val;
}

const vector<PozycjaRezerwacji>& Rezerwacja::zwrocPojazdy() const{
    return pojazdy;
}

void Rezerwacja::ustawPojazdy(const vector<PozycjaRezerwacji>& val){
    pojazdy = val;
}

const Data& Rezerwacja::zwrocDateRezerwacji() const{
    return dataRezerwacji;
}

void Rezerwacja::ustawDateRezerwacji(const Data& val){
    dataRezerwacji = val;
}

int Rezerwacja::zwrocStatus() const{
    return status;
}

void Rezerwacja::ustawStatus(int val){
    status = val;
}

bool Rezerwacja::zwrocPrzedluzono() const{
    return przedluzono;
}

void Rezerwacja::ustawPrzedluzono(bool val){
    przedluzono = val;
}

int Rezerwacja::zwrocOkresWypozyczenia() const {
    return okresWypozyczenia;
}

void Rezerwacja::ustawOkresWypozyczenia(int val){
    okresWypozyczenia = val;
}

const Klient& Rezerwacja::zwrocKlienta() const{
    return klient;
}

void Rezerwacja::ustawKlienta(const Klient& val){
    klient = val;
}

const Platnosc& Rezerwacja::zwrocOplateRezerwacji() const{
    return oplataRezerwacji;
}

void Rezerwacja::ustawOplateRezerwacji(const Platnosc& val){
    oplataRezerwacji = val;
}
const Platnosc& Rezerwacja::zwrocOplateDodatkowa() const{
    return oplataDodatkowa;
}

void Rezerwacja::ustawOplateDodatkowa(const Platnosc& val){
    oplataDodatkowa = val;
}


