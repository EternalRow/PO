#include "pozycja_rezerwacji.hpp"

PozycjaRezerwacji::PozycjaRezerwacji(const Pojazd& pojazd)
    : pojazd(pojazd) {}

PozycjaRezerwacji::~PozycjaRezerwacji() = default;

const Pojazd& PozycjaRezerwacji::zwrocPojazd() const{
    return pojazd;
}

void PozycjaRezerwacji::ustawPojazd(const Pojazd& val){
    pojazd=val;
}
