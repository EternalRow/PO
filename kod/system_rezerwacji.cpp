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
    /*int id_rezerwacji = rezerwacje.size()+1;
    
    vector<PozycjaRezerwacji> pozycja;
    pozycja.push_back(PozycjaRezerwacji(pojazd));
    Rezerwacja nowa_rezerwacja = Rezerwacja(id_rezerwacji, pozycja, data_wypozyczenia, 0, 0, data_zwrotu, id_osoby);
    rezerwacje.push_back(nowa_rezerwacja);

    float kwota = 200*okres_wypozyczenia;
    const Data data_przelewu = Data(0,0,0);
    int id_platnosci = platnosci.size()+1;
    Platnosc nowa_platnosc = Platnosc(data_przelewu, kwota, 0, id_rezerwacji, id_platnosci);
    platnosci.push_back(nowa_platnosc);

    //dostepne.erase(find(dostepne.begin(), dostepne.end(), pojazd)); // usuniecie pojazdu z dostepnych
    //czy nie powinno zwracac do maina platnosci i rezerwacji?
    return 0;*/
    return 0;

}

void SystemRezerwacji::katalog(){
    cout << "Pojazdy w ofercie:" << endl;
    for(int i =0; i<pojazdy.size(); i++){
        cout << i+1 << ". ";
        pojazdy[i].wypisz();
    }

    int opcja;
    cout << "Wpisz 1 aby rozpocząć proces rezerwacji, lub cokolwiek aby wyjść." << endl;
    cin >> opcja;

    //przeniesc ponizsze opcje do zarezerwuj()?
    if (opcja == 1){
        string email;
        cout << "Podaj email:" << endl;
        cin >> email;
        Klient klient_rezerwujacy;
        for(int i=0;i<klienci.size();i++){
            if(klienci[i].zwrocEmail() == email){
                klient_rezerwujacy = klienci[i];
                break;
            }else if (i+1==klienci.size()){
                cout << "Niepoprawny email." << endl;
                return;
            }
        }

        vector<Pojazd> pojazdy_do_rezerwacji;
        int id_pojazdu;
        while (true){
            cout << "Podaj numer samochodu do rezerwacji lub wpisz 0, aby zakończyć: ";
            cin >> id_pojazdu;
            if (id_pojazdu == 0){
                break;
            }else{
                if (pojazdy[id_pojazdu-1].zwrocStatus() == 0){  //dlaczego krzycyz błąd???
                    cout << "Pojazd niedostępny." << endl;
                }else{
                    pojazdy_do_rezerwacji.push_back(pojazdy[id_pojazdu-1]);
                }
            }
        }
        if(pojazdy_do_rezerwacji.size() == 0){
            cout << "Nie wybrano samochodów; zamknięto katalog." << endl;
            return;
        }
        cout << "Podaj datę wypożyczenia (odbioru) w formacie DD.MM.RRRR, np. 01.04.2027" << endl;
        int d, m, r;
        string kropka;
        cin >> d >> kropka >> m >> kropka >> r;
        Data data = Data(d,m,r);

        int okres;
        cout << "Podaj okres wypożyczenia w dniach:" << endl;
        cin >> okres;

        Rezerwacja nowa_rez = zarezerwuj(klient_rezerwujacy, pojazdy_do_rezerwacji, data, okres);

    }else{
        return;
    }
}

bool SystemRezerwacji::dodajPojazd(const Pojazd& val){
    pojazdy.push_back(val);
    return 0;
}

bool SystemRezerwacji::oplacRezerwacje(Rezerwacja& rezerwacja){
    Platnosc platnosc = rezerwacja.zwrocOplateRezerwacji();
    platnosc.ustawStatus(1);
    rezerwacja.ustawStatus(1); // automatyczne ustawienie statusu rezerwacji na aktywny
    return 0;

}

bool SystemRezerwacji::oplacDodatkowe(Rezerwacja& rezerwacja){
    Platnosc platnosc = rezerwacja.zwrocOplateDodatkowa();
    platnosc.ustawStatus(1);
    return zakonczRezerwacje(rezerwacja); // autoamtyczna proba zamknięcia rezerwacji
}

bool SystemRezerwacji::przedluz(Rezerwacja& rezerwacja){
    rezerwacja.ustawPrzedluzono(1);
    return 0;
}

bool SystemRezerwacji::zwrocPojazdy(Rezerwacja& rezerwacja, int iloscDni){
    int okres_planowo = rezerwacja.zwrocOkresWypozyczenia();
    if (rezerwacja.zwrocPrzedluzono() == 1){
        okres_planowo += 7;
    }
    
    if (iloscDni <= okres_planowo && rezerwacja.zwrocPrzedluzono() == 0){
        return zakonczRezerwacje(rezerwacja); // brak dodatkowych platnosci -> proba zakoczenia rezerwacji
    }else if(iloscDni <= okres_planowo && rezerwacja.zwrocPrzedluzono() == 1){
        float kwota_za_przedluzenie = 7*stawkaDobowa;
        int id = platnosci.size()+1;
        Platnosc dodatkowa = Platnosc(kwota_za_przedluzenie, 0, Data(0,0,0), id);
        return 0;
    }
    else{ // kara za przetrzymanie samochodu ponad termin zwrotu
        vector<PozycjaRezerwacji> lista_zwracanych = rezerwacja.zwrocPojazdy();
        float wysokosc = (iloscDni-okres_planowo) * lista_zwracanych.size() * kara;
        int id = platnosci.size()+1;
        Platnosc dodatkowa_kara = Platnosc(wysokosc, 0, Data(0,0,0), id);
        platnosci.push_back(dodatkowa_kara);
        return 0;
    }
}

bool SystemRezerwacji::zakonczRezerwacje(Rezerwacja& rezerwacja){
    //todo
    return 0;
}

void SystemRezerwacji::dodajKlienta(Klient& val){
    klienci.push_back(val);
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