#include "pojazd.hpp"


Pojazd::Pojazd(const string& marka, const string& model, int rocznik, const string& nrRej, const Data& dataPrzegladu)
    : marka(marka), model(model), rocznik(rocznik), nrRej(nrRej), dataPrzegladu(dataPrzegladu) {}

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

void Pojazd::ustawDatePrzegladu(int dzien, int miesiac, int rok){
    dataPrzegladu.ustawDzien(dzien);
    dataPrzegladu.ustawMiesiac(miesiac);
    dataPrzegladu.ustawRok(rok);
}