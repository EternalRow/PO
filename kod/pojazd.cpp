/*
Status pojazdu
0 - niedostepny
1 - dostepny
*/

#include "pojazd.hpp"
#include <iostream>


Pojazd::Pojazd(const string& marka, const string& model, int rocznik, const string& nrRej, const Data& dataPrzegladu, bool status)
    : marka(marka), model(model), rocznik(rocznik), nrRej(nrRej), dataPrzegladu(dataPrzegladu), status(status) {}

Pojazd::~Pojazd() = default;


const string& Pojazd::zwrocMarke() const {
    return marka;
}

void Pojazd::ustawMarke(const string& val){
    marka = val;
}

const string& Pojazd::zwrocModel() const{
    return model;
}

void Pojazd::ustawModel(const string& val){
    model = val;
}

int Pojazd::zwrocRocznik() const{
    return rocznik;
}

void Pojazd::ustawRocznik(int val){
    rocznik = val;
}

const string& Pojazd::zwrocNrRej() const{
    return nrRej;
}

void Pojazd::ustawNrRej(const string& val){
    nrRej = val;
}

const Data& Pojazd::zwrocDatePrzegladu() const{
    return dataPrzegladu;
}

bool Pojazd::zwrocStatus() const{
    return status;
}

void Pojazd::ustawStatus(bool val){
    status = val;
}

void Pojazd::ustawDatePrzegladu(int dzien, int miesiac, int rok){
    dataPrzegladu.ustawDzien(dzien);
    dataPrzegladu.ustawMiesiac(miesiac);
    dataPrzegladu.ustawRok(rok);
}

void Pojazd::wypisz() const {
    if (status == 0){
        cout << "[NIEDOSTĘPNY] ";
    }
    cout << "Marka: " << marka << "; model: " << model <<"; rocznik: " << rocznik << endl;
}