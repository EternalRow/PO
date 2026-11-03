#include "pracownik.hpp"

Pracownik::Pracownik(const string& imie, const string& nazwisko, int id, int idPracownicze)
    : Osoba(imie, nazwisko, id), idPracownicze(idPracownicze) {}

Pracownik::~Pracownik() = default;


int Pracownik::zwrocIdPracownicze() const {
    return idPracownicze;
}

void Pracownik::ustawIdPracownicze(int val){
    idPracownicze = val;
}