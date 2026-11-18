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

int SystemRezerwacji::zarezerwuj(string email, vector<Pojazd>& wybrane_pojazdy, Data& data_wypozyczenia, int okres_wypozyczenia){
    int id_rez = rezerwacje.size()+1;
    int id_plat = platnosci.size()+1;

    Klient klient_rez;
    for (Klient& klient : klienci){
        if(klient.zwrocEmail()==email){
            klient_rez = klient;
        }
    }

    vector<PozycjaRezerwacji> wektor_pozycji;
    for (int i=0;i<wybrane_pojazdy.size();i++){
        wektor_pozycji.push_back(PozycjaRezerwacji(wybrane_pojazdy[i]));
    }
    float kwota = stawkaDobowa*okres_wypozyczenia*wektor_pozycji.size();
    Platnosc oplata = Platnosc(kwota, 0, Data(0,0,0), id_plat);
    Rezerwacja rez = Rezerwacja(id_rez, wektor_pozycji,  data_wypozyczenia, 0, 0, okres_wypozyczenia, klient_rez, oplata);
    
    rezerwacje.push_back(rez);
    platnosci.push_back(rez.zwrocOplateRezerwacji());

    return rez.zwrocId();
}

void SystemRezerwacji::zarezerwujInteraktywnie(string email){
    int opcja;
    cout << "Czy chcesz wyświetlić katalog przed wyborem pojazdu?" << endl
    << "1-tak, inna wartość - nie" << endl;
    cin >> opcja;

    if (opcja==1){
        katalog();
    }

    vector<Pojazd> pojazdy_do_rezerwacji;
    int id_pojazdu;

    while (true){
        cout << "Podaj numer samochodu do rezerwacji lub wpisz 0, aby zakończyć: ";
        cin >> id_pojazdu;
        if (id_pojazdu == 0){
            break;
        }

        int status = zwrocStatusDanegoPojazdu(id_pojazdu);

        if (status==-1){
            cout << "Nieprawidłowy numer pojazdu." << endl;
        }else if(status==0){
            cout << "Pojazd niedostępny." << endl;
        }
        else{
            zmienStatusPojazdu(id_pojazdu, 0);
            Pojazd pojazd_do_wypoz = zwrocWybranyPojazd(id_pojazdu);
            pojazdy_do_rezerwacji.push_back(pojazd_do_wypoz);
        }
        
    }
    if(pojazdy_do_rezerwacji.size() == 0){
        cout << "Nie wybrano samochodów. Wyjście z procesu rezerwacji..." << endl;
    }
    else{
        cout << "Podaj datę wypożyczenia (odbioru) w formacie DD.MM.RRRR, np. 01.04.2027" << endl;
        int d, m, r;
        char kropka;
        cin >> d >> kropka >> m >> kropka >> r;
        Data data = Data(d,m,r);

        int okres;
        cout << "Podaj okres wypożyczenia w dniach: ";
        cin >> okres;

        int id_rez = zarezerwuj(email, pojazdy_do_rezerwacji, data, okres);
        cout << "Zarezerwowano samochód. Numer ID rezerwacji: " << id_rez;
        cout << ". Dokonaj płatności, aby ją aktywować." << endl;
    
    }
    return;
}

void SystemRezerwacji::katalog(){
    cout << "Pojazdy w ofercie:" << endl;
    for(Pojazd& pojazd : pojazdy){
        pojazd.wypisz();
    }
    return;
}

void SystemRezerwacji::oplacRezerwacje(string email){
    int id_rez;
    cout << "Podaj ID rezerwacji, którą chcesz opłacić: ";
    cin >> id_rez;

    //ponieważ platnosc przechowywana jest zarowno w instancji danej rezerwacji, jak i w wektorze platnosci w systemie,
    // a my uzywamy zwyklych wskaznikow, to nalezy zmienic jej status w obu miejsach
    
    for (Rezerwacja& rez : rezerwacje){
        if (rez.zwrocId()==id_rez && rez.zwrocOplateRezerwacji().zwrocStatus()==0 && rez.zwrocKlienta().zwrocEmail()==email){
            if (rez.oplacRezerwacje()==0){
                cout << "Nie udało się opłacić; rezerwacja jest już opłacona, lub podano błędne ID." << endl;
                return;
            }

            cout << "Podaj datę przelewu w formacie DD.MM.RRRR, np. 01.01.2026: ";
            int d,m,r;
            char kropka;
            cin >> d >> kropka >> m >> kropka >> r;

            int id_platnosci = rez.zwrocOplateRezerwacji().zwrocId();
            for (Platnosc& platnosc : platnosci){
                if (platnosc.zwrocId()==id_platnosci){
                    platnosc.ustawStatus(1);
                    platnosc.ustawDatePrzelewu(d,m,r);
                    cout << "Pomyślnie opłacono rezerwacje. Rezerwacja jest aktywna." << endl;
                    return;
                }
            }
        }
    }
    cout << "Nie udało się opłacić; rezerwacja jest już opłacona, lub podano błędne ID." << endl;
    return;

}

void SystemRezerwacji::oplacDodatkowe(string email){
    int id_rez;
    cout << "Podaj ID rezerwacji, dla której chcesz opłacić płatność dodatkową: ";
    cin >> id_rez;
    
    for (Rezerwacja& rez : rezerwacje){
        if (rez.zwrocId()==id_rez && rez.zwrocOplateDodatkowa().zwrocStatus()==0 && rez.zwrocKlienta().zwrocEmail()==email){
            if (rez.oplacDodatkowe()==0){
                cout << "Nie udało się opłacić; rezerwacja nie wymaga dodatkowej opłaty, lub podano błędne ID." << endl;
                return;
            }

            cout << "Podaj datę przelewu w formacie DD.MM.RRRR, np. 01.01.2026: ";
            int d,m,r;
            char kropka;
            cin >> d >> kropka >> m >> kropka >> r;

            int id_platnosci = rez.zwrocOplateDodatkowa().zwrocId();
            for (Platnosc& platnosc : platnosci){
                if (platnosc.zwrocId()==id_platnosci){
                    platnosc.ustawStatus(1);
                    platnosc.ustawDatePrzelewu(d,m,r);
                    cout << "Pomyślnie opłacono. Po weryfikacji przez pracownika rezerwacja zostanie zamknięta." << endl;
                    return;
                }
            }
        }
    }
    cout << "Nie udało się opłacić; rezerwacja nie wymaga dodatkowej opłaty, lub podano błędne ID." << endl;
    return;
}

void SystemRezerwacji::przedluz(string email){
    int id_rez;
    cout << "Podaj ID rezerwacji, którą chcesz przedłużyć: ";
    cin >> id_rez;
    
    for (Rezerwacja& rez : rezerwacje){
        if(rez.zwrocId()==id_rez && rez.zwrocStatus()==1 && rez.zwrocKlienta().zwrocEmail()==email && rez.zwrocPrzedluzono()==0){
            rez.ustawPrzedluzono(1);
            cout << "Przedłużono termin zwrotu pojazdów o 7 dni dla rezerwacji o podanym ID." << endl;
            return;
        }
    }
    cout << "Nie udało się przedłużyć." << endl;
    return;
}

void SystemRezerwacji::zarejestrujZwrotPojazdu(){
    cout << "Podaj numer id rezerwacji, jakiej dotyczy zwrot (0 by wyświetlić listę rezerwacji): ";
    int nr;
    cin >> nr;
    cout << endl;
    if (nr==0){
        wypiszRezerwacje();
        cout << "Podaj nr rezerwacji: ";
        cin >> nr;
        cout << endl;
    }

    Rezerwacja& rez_do_zwrotu = zwrocWybranaRezerwacje(nr);

    cout << "Podaj okres (w dniach), przez jaki korzystano z pojazdów: ";
    int ilosc_dni;
    cin >> ilosc_dni;

    int okres_planowo = rez_do_zwrotu.zwrocOkresWypozyczenia();

    vector<PozycjaRezerwacji> pozycje_rezerwacji = rez_do_zwrotu.zwrocPojazdy();

    for (int i=0;i<pozycje_rezerwacji.size();i++){
        zmienStatusPojazdu(pozycje_rezerwacji[i].zwrocPojazd().zwrocId(), 1);
    }

    if (rez_do_zwrotu.zwrocPrzedluzono() == 1){
        okres_planowo += 7;
    }
    
    if (ilosc_dni <= okres_planowo && rez_do_zwrotu.zwrocPrzedluzono() == 0){
        rez_do_zwrotu.ustawStatus(3);
        cout << "Zakończono proces zwrotu pojazdów. Po weryfikacji przez pracownika rezerwacja zostanie zamknięta." << endl;
        return;

    }else if(ilosc_dni <= okres_planowo && rez_do_zwrotu.zwrocPrzedluzono() == 1){
        float kwota_za_przedluzenie = 7*stawkaDobowa*pozycje_rezerwacji.size();
        int id = platnosci.size()+1;
        Platnosc dodatkowa = Platnosc(kwota_za_przedluzenie, 0, Data(0,0,0), id);
        rez_do_zwrotu.ustawOplateDodatkowa(dodatkowa);
        
        platnosci.push_back(dodatkowa);
        rez_do_zwrotu.ustawStatus(2);
        
        cout << "Nałożono płatność dodatkową za przedłużenie lub przekroczenie terminu zwrotu." << endl;
        return;
    }
    else{ // kara za przetrzymanie samochodu ponad termin zwrotu
        vector<PozycjaRezerwacji> lista_zwracanych = rez_do_zwrotu.zwrocPojazdy();
        float wysokosc_kary = (ilosc_dni-okres_planowo) * lista_zwracanych.size() * kara;
        int id = platnosci.size()+1;
        Platnosc dodatkowa_kara = Platnosc(wysokosc_kary, 0, Data(0,0,0), id);
        rez_do_zwrotu.ustawOplateDodatkowa(dodatkowa_kara);
        
        platnosci.push_back(rez_do_zwrotu.zwrocOplateDodatkowa());
        rez_do_zwrotu.ustawStatus(2);
        
        cout << "Nałożono płatność dodatkową za przedłużenie lub przekroczenie terminu zwrotu." << endl;
        return;
    }
}

void SystemRezerwacji::zamknijRezerwacje(){
    int id;
    cout << "Podaj ID rezerwacji do zamknięcia lub wciśnij 0, aby wyświetlić listę rezerwacji: ";
    cin >> id;
    cout << endl;
    if (id==0){
        wypiszRezerwacje();
        cout << "\nPodaj ID rezerwacji do zamknięcia: ";
        cin >> id;
        cout << endl;
    }
    Rezerwacja& rez_do_zamk = zwrocWybranaRezerwacje(id);
    if (rez_do_zamk.zwrocStatus()==3){
        rez_do_zamk.ustawStatus(4);
        cout << "Pomyślnie zamknięto rezerwację."<< endl;
        return;
    }
    cout << "Nie udało się zamknąć tej rezerwacji." << endl;
    return;
}

void SystemRezerwacji::dodajKlienta(string imie, string nazwisko, string email, int id){
    Klient nowy_klient = Klient(imie, nazwisko, email, id);
    klienci.push_back(nowy_klient);
}

void SystemRezerwacji::dodajKlientaInteraktywnie(){
    string imie, nazwisko, email;
    int id;
    cout << "Podaj imię: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj email: ";
    cin >> email;
    cout << "Podaj ID: ";
    cin >> id;

    while(!walidujIdKlienta(id)){
        cout << "Podane ID jest zajęte. Wybierz inne: ";
        cin >> id;
    }

    dodajKlienta(imie, nazwisko, email, id);
    cout << "Klient dodany pomyślnie." << endl;
}

bool SystemRezerwacji::walidujIdKlienta(int id){
    for(Klient& klient : klienci){
        if (klient.zwrocId()==id){
            return 0;
        }
    }
    return 1;
}

void SystemRezerwacji::dodajPojazd(string marka, string model, int rocznik, string nrRej, Data dataPrzegladu, int status){  // dodaje nowy Pojazd do katalogu pojazdów w systemie
    int id = pojazdy.size()+1;
    Pojazd nowy_pojazd = Pojazd(id, marka, model, rocznik, nrRej, dataPrzegladu, status);
    pojazdy.push_back(nowy_pojazd);
    return;
}

void SystemRezerwacji::dodajPojazdInteraktywnie(){
    string marka, model, nrRej;
    int rocznik, d, m, r;
    char kropka;
    cout << "Podaj markę: ";
    cin >> marka;
    cout << "Podaj model: ";
    cin >> model;
    cout << "Podaj numer rejestracyjny: ";
    cin >> nrRej;
    cout << "Podaj rocznik: ";
    cin >> rocznik;
    cout << "Podaj datę przeglądu w formacie DD.MM.RRRR (np. 31.04.2025): ";
    cin >> d >> kropka >> m >> kropka >> r;
    Data dataPrzeg = Data(d,m,r);
    dodajPojazd(marka, model, rocznik, nrRej, dataPrzeg, 1);
    cout << "Pomyślnie dodano pojazd." << endl;
}

void SystemRezerwacji::wypiszKlienci(){
    if(klienci.size() == 0){
        cout << "Brak klientów w systemie." << endl;
        return;
    }
    for (Klient& klient : klienci){
        klient.wypiszDane();
    }
    return;
    
}

void SystemRezerwacji::wypiszPracownicy(){
    if (pracownicy.size() == 0){
        cout << "Brak pracowników w systemie." << endl;
        return;
    }
    for (Pracownik& pracownik : pracownicy){
        pracownik.wypiszDane();
    }
    return;
    
}

void SystemRezerwacji::wypiszPlatnosci(){
    if (platnosci.size() == 0){
        cout << "Brak płatności w systemie." << endl;
        return;
    }
    for (Platnosc& platnosc : platnosci){
        platnosc.wypiszDane();
    }
    return;
}

void SystemRezerwacji::wypiszRezerwacje(){
    if (rezerwacje.size()==0){
        cout << "Brak rezerwacji w systemie." << endl;
        return;
    }
    for (Rezerwacja& rez : rezerwacje){
        rez.wypiszDane();
    }
    return;
}

void SystemRezerwacji::usunRezerwacje(){
    int id;
    cout << "Podaj ID rezerwacji, którą chcesz usunąć, lub wpisz 0, aby wyświetlić listę rezerwacji: ";
    cin >> id;
    cout << endl;
    if (id==0){
        wypiszRezerwacje();
        cout << "Podaj ID rezerwacji do usunięcia: ";
        cin >> id;
        cout << endl;
    }

    for (int i=0;i<rezerwacje.size();i++){
        if (rezerwacje[i].zwrocStatus()==4){
            rezerwacje.erase(rezerwacje.begin()+i);
            cout << "\nRezerwacja została usunięta\n";
            return;
        }else{
            cout << "Nie można usunąć tej rezerwacji.\n";
            return;
        }
    }

    cout << "Nie udało się usunąć rezerwacji; niepoprawne ID.\n";
    return;

}

void SystemRezerwacji::usunPojazd(){
    int id;
    cout << "Podaj ID pojazdu, który chcesz usunąć, lub wpisz 0, aby wyświetlić listę pojazdów: ";
    cin >> id;
    cout << endl;
    if (id==0){
        katalog();
        cout << "Podaj numer pojazdu do usunięcia: ";
        cin >> id;
        cout << endl;
    }

    for (Pojazd& poj : pojazdy){
        if (poj.zwrocId()==id && poj.zwrocStatus()==0){ //przeszukanie w liście systemowej, aby dostać poprawną wartość statusu
            cout << "Pojazd jest obecnie wypożyczony; nie można go usunąć.\n\n";
            return;
        }
    }

    for (int i=0;i<pojazdy.size();i++){
        if (pojazdy[i].zwrocId()==id){
            pojazdy.erase(pojazdy.begin()+i);
            cout << "Usunięto pojazd o id " << id << ".\n";
            return;
        }
    }
    cout << "Nie udało się usunąć pojazdu; niepoprawne ID\n";
    return;
}

void SystemRezerwacji::usunKlienta(){
    int id;
    cout << "Podaj ID klienta, którego chcesz usunąć, lub wpisz 0, aby wyświetlić listę klientów: ";
    cin >> id;
    cout << endl;
    if (id==0){
        wypiszKlienci();
        cout << "\nPodaj ID klienta do usunięcia: ";
        cin >> id;
        cout << endl;
    }

    for (int i=0;i<klienci.size();i++){
        if (klienci[i].zwrocId()==id){
            for(Rezerwacja& rez : rezerwacje){
                if (rez.zwrocKlienta().zwrocId()==id && rez.zwrocStatus() != 4){
                    cout << "Klient ma aktywne rezerwacje; nie można go usunąć.\n\n";
                    return;
                }
            }
            klienci.erase(klienci.begin()+i);
            cout << "Usunięto klienta o ID " << id << ".\n";
            return;
        }
    }
    cout << "Nie udało się usunąć klienta; niepoprawne ID\n";
    return;
}


void SystemRezerwacji::zmienStatusRezerwacji(int id, int val){
    for(int i=0;i<rezerwacje.size();i++){
        if (rezerwacje[i].zwrocId() == id){
            rezerwacje[i].ustawStatus(val);
            return;
        }
    }
}

void SystemRezerwacji::zmienStatusPojazdu(int id_pojazdu, bool val){
    for(Pojazd& pojazd : pojazdy){
        if (pojazd.zwrocId() == id_pojazdu){
            pojazd.ustawStatus(val);
            return;
        }
    }
}

Rezerwacja& SystemRezerwacji::zwrocWybranaRezerwacje(int id){
    for (Rezerwacja& rez : rezerwacje){
        if (rez.zwrocId() == id){
            return rez;
        }
    }
    throw out_of_range("Nie znaleziono rezerwacji o podanym ID.");
}

void SystemRezerwacji::wypiszRezerwacjeKlienta(string email){
    cout << "TWOJE REZERWACJE:\n\n";
    int id_klienta;
    for (Klient& klient : klienci){
        if (klient.zwrocEmail()==email){
            id_klienta = klient.zwrocId();
        }
    }
    int wypisano=0;
    if(rezerwacje.size()==0){
        cout << "Brak rezerwacji!" << endl;
        return;
    }
    for (Rezerwacja& rez : rezerwacje){
        if (rez.zwrocKlienta().zwrocId()==id_klienta){
            wypisano += 1;
            rez.wypiszDane();
        }
    }
    if (wypisano ==0){
        cout << "Brak rezerwacji!" << endl;
    }
    return;

}

int SystemRezerwacji::zwrocStatusDanegoPojazdu(int id_pojazdu){
    for(Pojazd& pojazd : pojazdy){
        if(pojazd.zwrocId() == id_pojazdu){
            return pojazd.zwrocStatus();
        }
    }
    return -1;
}

Pojazd& SystemRezerwacji::zwrocWybranyPojazd(int id){
    for(Pojazd& pojazd : pojazdy){
        if (pojazd.zwrocId()==id){
            return pojazd;
        }
    }
    throw out_of_range("Nie znaleziono pojazdu o podanym ID.");
}

bool SystemRezerwacji::walidujEmail(string email){
    for(Klient& klient : klienci){
        if(klient.zwrocEmail() == email){
            return 1;
        }
    }
    return 0;
}

void SystemRezerwacji::zmienStawkeDobowa(){
    float kwota;
    cout << "Obecnie stawka dobowa wynosi " << stawkaDobowa << " zł.\nPodaj nową wartość: ";
    cin >> kwota;

    while (kwota==0.0){
        cout << "\nWartość musi być większa od 0. Podaj nową wartość: ";
        cin >> kwota;
    }
    if (kwota == stawkaDobowa){
        cout << "\nPodałeś kwotę, która jest już ustawiona.\n";
        return;
    }
    ustawStawkeDobowa(kwota);
    cout << "\nPomyślnie zmieniono stawkę dobową na kwotę " << kwota << " zł.\n";
    return;
}

void SystemRezerwacji::zmienKare(){
    float kwota;
    cout << "Obecnie kara za dobę wynosi " << kara << " zł.\nPodaj nową wartość: ";
    cin >> kwota;

    while (kwota==0.0){
        cout << "\nWartość musi być większa od 0. Podaj nową wartość: ";
        cin >> kwota;
    }
    if (kwota == kara){
        cout << "\nPodałeś kwotę, która jest już ustawiona.\n";
        return;
    }
    ustawKare(kwota);
    cout << "\nPomyślnie zmieniono stawkę kary na kwotę " << kwota << " zł.\n";
    return;
}