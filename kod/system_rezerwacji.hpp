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

        const Rezerwacja& zarezerwuj(Klient& klient, vector<Pojazd>& pojazdy, Data& data_wypozyczenia, int okres_wypozyczenia);
        void katalog();
        bool dodajPojazd(const Pojazd& pojazd);

        bool oplacRezerwacje(Rezerwacja& rezerwacja);
        bool oplacDodatkowe(Rezerwacja& rezerwacja);

        bool przedluz(Rezerwacja& rezerwacja);

        bool zwrocPojazdy(Rezerwacja& rezerwacja, int iloscDni);
        bool zakonczRezerwacje(Rezerwacja& rezerwacja);

        void dodajKlienta(Klient& val);
        void dodajPlatnosc(Platnosc& val);
        void dodajRezerwacje(Rezerwacja& val);
        void dodajPracownika(Pracownik& val);
        



};

#endif