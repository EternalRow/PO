/*
Oznaczenia statusu rezeerwacji:
0 - niezaplacone; nieaktywna
1 - aktywna, oplacona;
2 - zwrocono pojazdy, nieoplacono platnosci dodatkowej
3 - rezerwacja oczekuje na zamknięcie
4 - rezerwacja zamknięta;
*/

#include "rezerwacja.hpp"

Rezerwacja::Rezerwacja(int id, const vector<PozycjaRezerwacji> pojazdy, const Data& dataRezerwacji, int status, bool przedluzono, int okresWypozyczenia, const Klient& klient, const Platnosc& oplataRezerwacji, const Platnosc& oplataDodatkowa)
    : id(id), pojazdy(pojazdy), dataRezerwacji(dataRezerwacji), status(status), przedluzono(przedluzono), okresWypozyczenia(okresWypozyczenia), klient(klient), oplataRezerwacji(oplataRezerwacji), oplataDodatkowa(oplataDodatkowa) {}

Rezerwacja::~Rezerwacja() = default;

int Rezerwacja::zwrocId() const{
    return id;
}

void Rezerwacja::ustawId(int val){
    id = val;
}

const vector<PozycjaRezerwacji>& Rezerwacja::zwrocPojazdy() const{
    return pojazdy;
}

void Rezerwacja::ustawPojazdy(const vector<PozycjaRezerwacji>& val){
    pojazdy = val;
}

const Data& Rezerwacja::zwrocDateRezerwacji() const{
    return dataRezerwacji;
}

void Rezerwacja::ustawDateRezerwacji(const Data& val){
    dataRezerwacji = val;
}

int Rezerwacja::zwrocStatus() const{
    return status;
}

void Rezerwacja::ustawStatus(int val){
    status = val;
}

bool Rezerwacja::zwrocPrzedluzono() const{
    return przedluzono;
}

void Rezerwacja::ustawPrzedluzono(bool val){
    przedluzono = val;
}

int Rezerwacja::zwrocOkresWypozyczenia() const {
    return okresWypozyczenia;
}

void Rezerwacja::ustawOkresWypozyczenia(int val){
    okresWypozyczenia = val;
}

const Klient& Rezerwacja::zwrocKlienta() const{
    return klient;
}

void Rezerwacja::ustawKlienta(const Klient& val){
    klient = val;
}

const Platnosc& Rezerwacja::zwrocOplateRezerwacji() const{
    return oplataRezerwacji;
}

void Rezerwacja::ustawOplateRezerwacji(const Platnosc& val){
    oplataRezerwacji = val;
}
const Platnosc& Rezerwacja::zwrocOplateDodatkowa() const{
    return oplataDodatkowa;
}

void Rezerwacja::ustawOplateDodatkowa(const Platnosc& val){
    oplataDodatkowa = val;
}

bool Rezerwacja::oplacRezerwacje() {
    if (oplataRezerwacji.zwrocStatus() == 0){
        oplataRezerwacji.ustawStatus(1);
        status = 1;
        return 1;
    }
    return 0;  //oplata juz zostala oplacona wczesniej
}

bool Rezerwacja::oplacDodatkowe(){
    // status rezerwacji sprawdzic i probsa zamkniecia
    if (status != 2){
        return 0;  //rezerwacja zamknieta lub jeszcze nieaktywna
    }
    else if(oplataDodatkowa.zwrocStatus() == 0 && oplataDodatkowa.zwrocKwote() != 0.0){
        oplataDodatkowa.ustawStatus(1);
        status = 3;
        return 1;
    }
    return 0;
}

bool Rezerwacja::zakoncz(){
    if ((status==1 || status == 2) && (oplataDodatkowa.zwrocStatus() == 1 || (oplataDodatkowa.zwrocStatus()==0 && oplataDodatkowa.zwrocKwote()==0.0))){
        // jeśli problemy to dodaj warunek ze samochody muszą być oddane!!! (np dodaj status mowiacy ot ym ze samochody oddano i brak platnosci dodatkowej)
        status = 4;
        return 0;
    }
    return 1;
}

void Rezerwacja::wypiszDane(){
    cout << "ID rezerwacji: " << id << endl;
    cout << "ID klienta: " << klient.zwrocId() << endl;
    cout << "Ilość wypożyczonych pojazdów: " << pojazdy.size() << endl;
    cout << "Data rezerwacji: ";
    dataRezerwacji.wypisz();
    cout << endl << "Czy przedłużono: ";
    if (przedluzono==0){
        cout << "nie" << endl;
    }else{
        cout << "tak" << endl;
    }
    cout << "Okres wypożyczenia w dniach: " << okresWypozyczenia << endl;
    cout << "Status rezerwacji: ";
    if(status == 0){
        cout << " nieaktywna" << endl;
    }else if(status==1){
        cout << " aktywna" << endl;
    }else if(status==2){
        cout << " zwrócono pojazdy" << endl;
    }else if(status==3){
        cout << " oczekuje na zamknięcie" << endl;
    }else if (status==4){
        cout << " zamknięta" << endl;
    }
    return;
}