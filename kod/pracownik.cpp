#include "pracownik.hpp"

Pracownik::Pracownik(const string& imie, const string& nazwisko, int id, int idPracownicze)
    : Osoba(imie, nazwisko, id), idPracownicze(idPracownicze) {}

Pracownik::~Pracownik() = default;

void Pracownik::wypiszDane() const{
    cout << "ID pracownicze: " << idPracownicze
    << "; Imię: " << imie
    << "; Nazwisko: " << nazwisko << endl;
    return;
}