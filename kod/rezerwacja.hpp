#ifndef REZERWACJA_HPP
#define REZERWACJA_HPP

using namespace std;

#include "data.hpp"
#include "platnosc.hpp"
#include "klient.hpp"
#include <vector>
#include "pozycja_rezerwacji.hpp"

class Rezerwacja{
    private:
        int id;
        vector<PozycjaRezerwacji> pojazdy;
        Data dataRezerwacji;
        int status;
        bool przedluzono;
        int okresWypozyczenia;
        Klient klient;
        Platnosc oplataRezerwacji;
        Platnosc oplataDodatkowa;
    
    public:
        Rezerwacja(int id=0, const vector<PozycjaRezerwacji> pojazdy={}, const Data& dataRezerwacji=Data(), int status=0, bool przedluzono=false, int okres_wypozyczenia=0, const Klient& klient=Klient(), const Platnosc& oplata_rezerwacji=Platnosc(), const Platnosc& oplata_dodatkowa=Platnosc());
        virtual ~Rezerwacja();

        int zwrocId() const;
        void ustawId(int val);

        const vector<PozycjaRezerwacji>& zwrocPojazdy() const;
        void ustawPojazdy(const vector<PozycjaRezerwacji>& val);

        const Data& zwrocDateRezerwacji() const;
        void ustawDateRezerwacji(const Data& val);

        int zwrocStatus() const;
        void ustawStatus(int val);

        bool zwrocPrzedluzono() const;
        void ustawPrzedluzono(bool val);

        int zwrocOkresWypozyczenia() const;
        void ustawOkresWypozyczenia(int val);

        const Klient& zwrocKlienta() const;
        void ustawKlienta(const Klient& val);

        const Platnosc& zwrocOplateRezerwacji() const;
        void ustawOplateRezerwacji(const Platnosc& val);

        const Platnosc& zwrocOplateDodatkowa() const;
        void ustawOplateDodatkowa(const Platnosc& val);

        //funkcja do wyswietlenia rezerwacji i zarzadzania nią -> tu czy w systemie?

};

#endif