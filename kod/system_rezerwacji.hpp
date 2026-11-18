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

        float zwrocStawkeDobowa() const;
        void ustawStawkeDobowa(float val);

        float zwrocKare() const;
        void ustawKare(float val);
        
        const vector<Klient>& zwrocKlienci() const;
        void ustawKlienci(const vector<Klient>& val);

        const vector<Platnosc>& zwrocPlatnosci() const;
        void ustawPlatnosci(const vector<Platnosc>& val);

        const vector<Pracownik>& zwrocPracownicy() const;
        void ustawPracownicy(const vector<Pracownik>& val);

        const vector<Pojazd>& zwrocPojazdy() const;
        void ustawPojazdy(const vector<Pojazd>& val);

        const vector<Rezerwacja>& zwrocRezerwacje() const;
        void ustawRezerwacje(const vector<Rezerwacja>& val);

        void katalog();

        int zarezerwuj(string email, vector<Pojazd>& pojazdy, Data& data_wypozyczenia, int okres_wypozyczenia);
        void zarezerwujInteraktywnie(string email);
        
        
        bool oplacRezerwacje(string email);
        bool oplacDodatkowe(string email);

        bool przedluz(string email);

        bool zarejestrujZwrotPojazdu();

        void zamknijRezerwacje();

        void zmienStatusPojazdu(int indeks, bool val);

        void zmienStatusRezerwacji(int id, int val);

        Rezerwacja& zwrocWybranaRezerwacje(int id);

        void dodajPojazd(string marka, string model, int rocznik, string nrRej, Data dataPrzegladu, int status);
        void dodajPojazdInteraktywnie();

        void dodajKlienta(string imie, string nazwisko, string email, int id);
        void dodajKlientaInteraktywnie();

        bool walidujIdKlienta(int id);
        
        void dodajPlatnosc(Platnosc& val);
        void dodajRezerwacje(Rezerwacja& val);
        void dodajPracownika(Pracownik& val);

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

};

#endif