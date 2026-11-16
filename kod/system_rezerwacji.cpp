#include "system_rezerwacji.hpp"
#include <bits/stdc++.h> // do funkcji find
#include <iostream>

SystemRezerwacji::SystemRezerwacji(float stawkaDobowa, float kara, const vector<Klient> klienci, const vector<Pracownik> pracownicy, const vector<Pojazd> pojazdy, const vector<Rezerwacja> rezerwacje, const vector<Platnosc> platnosci)
    : stawkaDobowa(stawkaDobowa), kara(kara), klienci(klienci), platnosci(platnosci), pracownicy(pracownicy), pojazdy(pojazdy), rezerwacje(rezerwacje) {}

SystemRezerwacji::~SystemRezerwacji() = default;


float SystemRezerwacji::zwrocStawkeDobowa() const{
    return stawkaDobowa;
}
void SystemRezerwacji::ustawStawkeDobowa(float val){
    stawkaDobowa = val;
}

float SystemRezerwacji::zwrocKare() const{
    return kara;
}
void SystemRezerwacji::ustawKare(float val){
    kara = val;
}

const vector<Klient>& SystemRezerwacji::zwrocKlienci() const{
    return klienci;
}
void SystemRezerwacji::ustawKlienci(const vector<Klient>& val){
    klienci = val;
}

const vector<Platnosc>& SystemRezerwacji::zwrocPlatnosci() const{
    return platnosci;
}
void SystemRezerwacji::ustawPlatnosci(const vector<Platnosc>& val){
    platnosci = val;
}

const vector<Pracownik>& SystemRezerwacji::zwrocPracownicy() const{
    return pracownicy;
}
void SystemRezerwacji::ustawPracownicy(const vector<Pracownik>& val){
    pracownicy = val;
}

const vector<Pojazd>& SystemRezerwacji::zwrocPojazdy() const{
    return pojazdy;
}
void SystemRezerwacji::ustawPojazdy(const vector<Pojazd>& val){
    pojazdy = val;
}

const vector<Rezerwacja>& SystemRezerwacji::zwrocRezerwacje() const{
    return rezerwacje;
}
void SystemRezerwacji::ustawRezerwacje(const vector<Rezerwacja>& val){
    rezerwacje = val;
}

const Rezerwacja& SystemRezerwacji::zarezerwuj(Klient& klient, vector<Pojazd>& pojazdy, Data& data_wypozyczenia, int okres_wypozyczenia){
    int id_rez = rezerwacje.size()+1;
    int id_plat = platnosci.size()+1;
    vector<PozycjaRezerwacji> wektor_pozycji;
    for (int i=0;i<pojazdy.size();i++){
        wektor_pozycji.push_back(PozycjaRezerwacji(pojazdy[i]));
    }
    float kwota = stawkaDobowa*okres_wypozyczenia*wektor_pozycji.size();
    Platnosc oplata = Platnosc(kwota, 0, Data(0,0,0), id_plat);
    Rezerwacja rez = Rezerwacja(id_rez, wektor_pozycji,  data_wypozyczenia, 0, 0, okres_wypozyczenia, klient, oplata); //domyslnie platnosc dodatkowa?
    
    rezerwacje.push_back(rez);
    platnosci.push_back(oplata);

    return rezerwacje.back(); //ostatni element z listy rezerwacji (nowo dodany)

}

void SystemRezerwacji::katalog(){
    cout << "Pojazdy w ofercie:" << endl;
    for(int i =0; i<pojazdy.size(); i++){
        cout << i+1 << ". ";
        pojazdy[i].wypisz();
    }
    return;
}

void SystemRezerwacji::dodajPojazd(string marka, string model, int rocznik, string nrRej, Data dataPrzegladu, int status){  // dodaje instancję obiektu Pojazd do katalogu pojazdów w systemie
    Pojazd nowy_pojazd = Pojazd(marka, model, rocznik, nrRej, dataPrzegladu, status);
    pojazdy.push_back(nowy_pojazd);
    return;
}

bool SystemRezerwacji::oplacRezerwacje(Rezerwacja& rezerwacja){ ///jako argument data platnosci?????
    return rezerwacja.oplacRezerwacje(); //0-oplacono, 1-bylo juz wczesniej oplacone

}

bool SystemRezerwacji::oplacDodatkowe(Rezerwacja& rezerwacja){ ///jako argument data platnosci?????
    return rezerwacja.oplacDodatkowe();  //0-oplacono, 1-bylo juz wczesniej oplacone lub brak platnosci dodatkowej
    // co zwraca ta funkcja, skoro oplacDodatkowe w rezerwacji probuje ją zamknąć? -- > sprawdź
}

bool SystemRezerwacji::przedluz(Rezerwacja& rezerwacja){
    rezerwacja.ustawPrzedluzono(1);
    return 0;
}

bool SystemRezerwacji::zarejestrujZwrotPojazdu(Rezerwacja& rezerwacja, int iloscDni){
    int okres_planowo = rezerwacja.zwrocOkresWypozyczenia();

    //zwrocenie pojazdom dostepnosci
    vector<PozycjaRezerwacji> pozycje_rezerwacji = rezerwacja.zwrocPojazdy();
    for (int i=0;i<pozycje_rezerwacji.size();i++){
        Pojazd oddany_pojazd = pozycje_rezerwacji[i].zwrocPojazd(); //!!!!!!!!!!!!!czy dziala czy robi to przez referencje
        oddany_pojazd.ustawStatus(0);
    }

    if (rezerwacja.zwrocPrzedluzono() == 1){
        okres_planowo += 7;
    }
    
    if (iloscDni <= okres_planowo && rezerwacja.zwrocPrzedluzono() == 0){
        return rezerwacja.zakoncz(); // brak dodatkowych platnosci -> proba zakonczenia (0-udana,1-nieudana)
        // jak rozroznic zwrocona wartosc funkcji na "pomyslnie oddano" i "oddano i zakonczono"? -> main?

    }else if(iloscDni <= okres_planowo && rezerwacja.zwrocPrzedluzono() == 1){
        float kwota_za_przedluzenie = 7*stawkaDobowa*pozycje_rezerwacji.size();
        int id = platnosci.size()+1; //!!!!!!!!+10 dla pewnosci?
        Platnosc dodatkowa = Platnosc(kwota_za_przedluzenie, 0, Data(0,0,0), id);
        rezerwacja.ustawOplateDodatkowa(dodatkowa);
        
        platnosci.push_back(dodatkowa);
        rezerwacja.ustawStatus(2);
        return 0;
    }
    else{ // kara za przetrzymanie samochodu ponad termin zwrotu
        vector<PozycjaRezerwacji> lista_zwracanych = rezerwacja.zwrocPojazdy();
        float wysokosc_kary = (iloscDni-okres_planowo) * lista_zwracanych.size() * kara;
        int id = platnosci.size()+1;
        Platnosc dodatkowa_kara = Platnosc(wysokosc_kary, 0, Data(0,0,0), id);
        rezerwacja.ustawOplateDodatkowa(dodatkowa_kara);
        
        platnosci.push_back(dodatkowa_kara);
        rezerwacja.ustawStatus(2);

        return 0;
    }
}

void SystemRezerwacji::dodajKlienta(string imie, string nazwisko, string email, int id){
    Klient nowy_klient = Klient(imie, nazwisko, email, id);
    klienci.push_back(nowy_klient);
}

void SystemRezerwacji::dodajPlatnosc(Platnosc& val){
    platnosci.push_back(val);
}
void SystemRezerwacji::dodajPracownika(Pracownik& val){
    pracownicy.push_back(val);
}
void SystemRezerwacji::dodajRezerwacje(Rezerwacja& val){
    rezerwacje.push_back(val);
}

void SystemRezerwacji::wypiszKlienci(){
    if(klienci.size() == 0){
        cout << "Brak klientów w systemie." << endl;
        return;
    }
    else{
        for (int i=0;i<klienci.size();i++){
            klienci[i].wypiszDane();
        }
        return;
    }
    
}

void SystemRezerwacji::wypiszPracownicy(){
    if (pracownicy.size() == 0){
        cout << "Brak pracowników w systemie." << endl;
        return;
    }
    else{
        for (int i=0;i<pracownicy.size();i++){
            pracownicy[i].wypiszDane();
        }
        return;
    }
    
}

void SystemRezerwacji::wypiszPlatnosci(){
    if (platnosci.size() == 0){
        cout << "Brak płatności w systemie." << endl;
        return;
    }
    else{
        for (int i=0;i<platnosci.size();i++){
            platnosci[i].wypiszDane();
        }
        return;
    }
}

void SystemRezerwacji::wypiszRezerwacje(){
    if (rezerwacje.size()==0){
        cout << "Brak rezerwacji w systemie." << endl;
        return;
    }else{
        for (int i=0;i<rezerwacje.size();i++){
            rezerwacje[i].wypiszDane();
        }
        return;
    }
}

Rezerwacja SystemRezerwacji::zwrocWybranaRezerwacje(int id){
    for (int i=0;i<rezerwacje.size();i++){
        if (rezerwacje[i].zwrocId() == id){
            return rezerwacje[i];
        }
    }
    return Rezerwacja();
    
}