#include "platnosc.hpp"


Platnosc::Platnosc(float kwota, int status, const Data& dataPrzelewu, int id)
    : kwota(kwota), status(status), dataPrzelewu(dataPrzelewu), id(id)  {}

Platnosc::~Platnosc() = default;


void Platnosc::ustawDatePrzelewu(int dzien, int miesiac, int rok) {
    dataPrzelewu.ustawDzien(dzien);
    dataPrzelewu.ustawMiesiac(miesiac);
    dataPrzelewu.ustawRok(rok);
}

float Platnosc::zwrocKwote() const {
    return kwota;
}

int Platnosc::zwrocStatus() const{
    return status;
}

void Platnosc::ustawStatus(int val){
    status = val;
}

int Platnosc::zwrocId() const{
    return id;
}

void Platnosc::ustawId(int val){
    id = val;
}

void Platnosc::wypiszDane() const{
    cout << "ID: " << id
    << " Kwota: " << kwota;
    if (status == 0){
        cout << " Status: nieopłacona";
    }
    else{
        cout << " Status: opłacona";
    }
    cout << " Data przelewu: ";
    dataPrzelewu.wypisz();
    cout << endl;
}