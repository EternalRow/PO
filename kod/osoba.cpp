#include "osoba.hpp"

Osoba::Osoba(const string& imie, const string& nazwisko, int id)
    : imie(imie), nazwisko(nazwisko), id(id) {}

Osoba::~Osoba() = default;

int Osoba::zwrocId() const{
    return id;
}
