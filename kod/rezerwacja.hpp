#ifndef REZERWACJA_HPP
#define REZERWACJA_HPP

using namespace std;

#include "data.hpp"
#include "platnosc.hpp"
#include "klient.hpp"
#include <vector>
#include "pozycja_rezerwacji.hpp"

/*
Oznaczenia statusu rezeerwacji:
0 - niezaplacone; nieaktywna
1 - aktywna, oplacona;
2 - zwrocono pojazdy, nieoplacono platnosci dodatkowej
3 - rezerwacja oczekuje na zamknięcie
4 - rezerwacja zamknięta;
*/

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

        const vector<PozycjaRezerwacji>& zwrocPojazdy() const;

        int zwrocStatus() const;
        void ustawStatus(int val);

        bool zwrocPrzedluzono() const;
        void ustawPrzedluzono(bool val);

        int zwrocOkresWypozyczenia() const;

        const Klient& zwrocKlienta() const;

        const Platnosc& zwrocOplateRezerwacji() const;

        const Platnosc& zwrocOplateDodatkowa() const;
        void ustawOplateDodatkowa(const Platnosc& val);

        bool oplacRezerwacje(); 
        bool oplacDodatkowe();
        bool zakoncz();

        void wypiszDane();

};

#endif