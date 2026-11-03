#include "klient.hpp"

Klient::Klient(const string& imie, const string& nazwisko, const string& email, int id)
    : Osoba(imie, nazwisko, id), email(email) {}

Klient::~Klient() = default;


const string& Klient::zwrocEmail() const {
    return email;
}

void Klient::ustawEmail(const string& val){
    email = val;
}