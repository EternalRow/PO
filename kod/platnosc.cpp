#include "platnosc.hpp"


Platnosc::Platnosc(const Data& dataPrzelewu, float kwota, int status, int idRezerwacji, int id)
    : kwota(kwota), status(status), dataPrzelewu(dataPrzelewu), idRezerwacji(idRezerwacji), id(id)  {}

Platnosc::~Platnosc() = default;


const Data& Platnosc::zwrocDatePrzelewu() const{
    return dataPrzelewu;
}

void Platnosc::ustawDatePrzelewu(int dzien, int miesiac, int rok){
    dataPrzelewu.ustawDzien(dzien);
    dataPrzelewu.ustawMiesiac(miesiac);
    dataPrzelewu.ustawRok(rok);
}

float Platnosc::zwrocKwote() const {
    return kwota;
}

void Platnosc::ustawKwote(float val){
    kwota = val;
}

int Platnosc::zwrocStatus() const{
    return status;
}

void Platnosc::ustawStatus(int val){
    status = val;
}

int Platnosc::zwrocIdRezerwacji() const{
    return idRezerwacji;
}

void Platnosc::ustawIdRezerwacji(int val){
    idRezerwacji = val;
}

int Platnosc::zwrocId() const{
    return id;
}

void Platnosc::ustawId(int val){
    id = val;
}
