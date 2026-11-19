#ifndef SYSTEMREZERWACJI_HPP
#define SYSTEMREZERWACJI_HPP

using namespace std;

#include "rezerwacja.hpp"
#include "klient.hpp"
#include "pojazd.hpp"
#include "platnosc.hpp"
#include "pracownik.hpp"
#include <vector>
#include <string>
#include <iostream>

class SystemRezerwacji{
    private:
        float stawkaDobowa;
        float kara;
        vector<Klient> klienci;
        vector<Platnosc> platnosci;
        vector<Pracownik> pracownicy;
        vector<Pojazd> pojazdy;
        vector<Rezerwacja> rezerwacje;
        
    public:
        SystemRezerwacji(float stawkaDobowa=200.0, float kara=350.0, const vector<Klient> klienci={}, const vector<Pracownik> pracownicy={}, const vector<Pojazd> pojazdy={}, const vector<Rezerwacja> rezerwacje={}, const vector<Platnosc> platnosci={});
        virtual ~SystemRezerwacji();

        void katalog();

        int zarezerwuj(string email, vector<Pojazd>& pojazdy, Data& data_wypozyczenia, int okres_wypozyczenia);
        void zarezerwujInteraktywnie(string email);
        
        void oplacRezerwacje(string email);
        void oplacDodatkowe(string email);

        void przedluz(string email);

        void zarejestrujZwrotPojazdu();
        bool walidujRezerwacje(int id);

        void zamknijRezerwacje();

        void zmienStatusPojazdu(int indeks, bool val);

        void zmienStatusRezerwacji(int id, int val);

        Rezerwacja& zwrocWybranaRezerwacje(int id);

        void dodajPojazd(string marka, string model, int rocznik, string nrRej, Data dataPrzegladu, int status);
        void dodajPojazdInteraktywnie();

        void dodajKlienta(string imie, string nazwisko, string email, int id);
        void dodajKlientaInteraktywnie();

        void dodajPracownika(string imie, string nazwisko, int id, int idPracownicze);

        bool walidujIdKlienta(int id);

        void wypiszKlienci();
        void wypiszPlatnosci();
        void wypiszPracownicy();
        void wypiszRezerwacje();


        void usunRezerwacje();
        void usunPojazd();
        void usunKlienta();

        void wypiszRezerwacjeKlienta(string email);

        int zwrocStatusDanegoPojazdu(int id_pojazdu);
        Pojazd& zwrocWybranyPojazd(int id);

        bool walidujEmail(string email);

        void zmienStawkeDobowa();
        void zmienKare();

};

#endif