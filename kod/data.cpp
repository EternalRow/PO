#include "data.hpp"

Data::Data(int dzien, int miesiac, int rok)
    : dzien(dzien), miesiac(miesiac), rok(rok) {}

Data::~Data() = default;

void Data::ustawDzien(int val){
    dzien = val;
}

void Data::ustawMiesiac(int val){
    miesiac = val;
}

void Data::ustawRok(int val){
    rok = val;
}

void Data::wypisz() const{
    cout << dzien << "." << miesiac << "." << rok;
    return;
}

