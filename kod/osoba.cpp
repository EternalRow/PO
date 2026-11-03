#include "osoba.hpp"

Osoba::Osoba(const string& imie, const string& nazwisko, int d)
    : imie(imie), nazwisko(nazwisko), id(id) {}


Osoba::~Osoba() = default;

const string& Osoba::zwrocImie() const{
    return imie;
}

void Osoba::ustawImie(const string& val){
    imie = val;
}

const string& Osoba::zwrocNazwisko() const{
    return nazwisko;
}

void Osoba::ustawNazwisko(const string& val){
    nazwisko = val;
}

int Osoba::zwrocId() const{
    return id;
}

void Osoba::ustawId(int val){
    id = val;
}
