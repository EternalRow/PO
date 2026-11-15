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

    int opcja;
    cout << "Wpisz 1 aby rozpocząć proces rezerwacji, lub cokolwiek aby wyjść." << endl;
    cin >> opcja;

    //przeniesc ponizsze opcje do MENU
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
                if (pojazdy[id_pojazdu-1].zwrocStatus() == 0){
                    cout << "Pojazd niedostępny." << endl;
                }else{
                    pojazdy_do_rezerwacji.push_back(pojazdy[id_pojazdu-1]);  //zamiast teog możemy uzyc dodajPojazd w menu
                }
            }
        }
        if(pojazdy_do_rezerwacji.size() == 0){
            cout << "Nie wybrano samochodów; zamknięto katalog." << endl;
            return;
        }
        cout << "Podaj datę wypożyczenia (odbioru) w formacie DD.MM.RRRR, np. 01.04.2027" << endl; //NAPRAW!!!!!!!!!!!!!!!!!
        int d, m, r;
        string kropka;
        cin >> d >> kropka >> m >> kropka >> r;
        Data data = Data(d,m,r);

        int okres;
        cout << "Podaj okres wypożyczenia w dniach:" << endl;
        cin >> okres;

        Rezerwacja nowa_rez = zarezerwuj(klient_rezerwujacy, pojazdy_do_rezerwacji, data, okres);
        dodajRezerwacje(nowa_rez);

    }else{
        return;
    }
}

bool SystemRezerwacji::dodajPojazd(const Pojazd& val){  // dodaje instancję obiektu Pojazd do katalogu pojazdów w systemie
    pojazdy.push_back(val);
    return 0;
}

bool SystemRezerwacji::oplacRezerwacje(Rezerwacja& rezerwacja){ ///jako argument data platnosci?????
    return rezerwacja.oplacRezerwacje(); //0-oplacono, 1-bylo juz wczesniej oplacone

}

bool SystemRezerwacji::oplacDodatkowe(Rezerwacja& rezerwacja){ ///jako argument data platnosci?????
    rezerwacja.oplacDodatkowe() == 0;  //0-oplacono, 1-bylo juz wczesniej oplacone lub brak platnosci dodatkowej
}

bool SystemRezerwacji::przedluz(Rezerwacja& rezerwacja){
    rezerwacja.ustawPrzedluzono(1);
    return 0;
}

bool SystemRezerwacji::zwrocPojazdy(Rezerwacja& rezerwacja, int iloscDni){
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