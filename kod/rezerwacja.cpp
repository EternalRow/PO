#include "rezerwacja.hpp"

Rezerwacja::Rezerwacja(int id, const vector<PozycjaRezerwacji> pojazdy, const Data& dataRezerwacji, int status, bool przedluzono, int okresWypozyczenia, const Klient& klient, const Platnosc& oplataRezerwacji, const Platnosc& oplataDodatkowa)
    : id(id), pojazdy(pojazdy), dataRezerwacji(dataRezerwacji), status(status), przedluzono(przedluzono), okresWypozyczenia(okresWypozyczenia), klient(klient), oplataRezerwacji(oplataRezerwacji), oplataDodatkowa(oplataDodatkowa) {}

Rezerwacja::~Rezerwacja() = default;

int Rezerwacja::zwrocId() const{
    return id;
}

const vector<PozycjaRezerwacji>& Rezerwacja::zwrocPojazdy() const{
    return pojazdy;
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

const Klient& Rezerwacja::zwrocKlienta() const{
    return klient;
}


const Platnosc& Rezerwacja::zwrocOplateRezerwacji() const{
    return oplataRezerwacji;
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