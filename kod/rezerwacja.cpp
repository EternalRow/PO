#include "rezerwacja.hpp"

Rezerwacja::Rezerwacja(int id, const vector<PozycjaRezerwacji> pojazdy, const Data& dataRezerwacji, int status, bool przedluzono, const Data& terminZwrotu, int idKlienta)
    : id(id), pojazdy(pojazdy), dataRezerwacji(dataRezerwacji), status(status), przedluzono(przedluzono), terminZwrotu(terminZwrotu), idKlienta(idKlienta) {}

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

const Data& Rezerwacja::zwrocTerminZwrotu() const {
    return terminZwrotu;
}

void Rezerwacja::ustawTerminZwrotu(const Data& val){
    terminZwrotu = val;
}

int Rezerwacja::zwrocIdKlienta() const{
    return idKlienta;
}

void Rezerwacja::ustawIdKlienta(int val){
    idKlienta = val;
}

