#include "pojazd.hpp"


Pojazd::Pojazd(int id, const string& marka, const string& model, int rocznik, const string& nrRej, const Data& dataPrzegladu, bool status)
    : id(id), marka(marka), model(model), rocznik(rocznik), nrRej(nrRej), dataPrzegladu(dataPrzegladu), status(status) {}

Pojazd::~Pojazd() = default;

int Pojazd::zwrocId() const{
    return id;
}

bool Pojazd::zwrocStatus() const{
    return status;
}

void Pojazd::ustawStatus(bool val){
    status = val;
}

void Pojazd::wypisz() const {
    cout << id << ". ";
    if (status == 0){
        cout << "[NIEDOSTĘPNY] ";
    }
    cout << "Marka: " << marka << " Model: " << model <<" Rocznik: " << rocznik << endl;
}