#ifndef REZERWACJA_HPP
#define REZERWACJA_HPP

using namespace std;

#include "data.hpp"
#include <vector>
using namespace std;
#include "pozycja_rezerwacji.hpp"

class Rezerwacja{
    private:
        int id;
        vector<PozycjaRezerwacji> pojazdy;
        Data dataRezerwacji;
        int status;
        bool przedluzono;
        Data terminZwrotu;
        int idKlienta;
    
    public:
        Rezerwacja(int id=0, const vector<PozycjaRezerwacji> pojazdy={}, const Data& dataRezerwacji=Data(), int status=0, bool przedluzono=false, const Data& terminZwrotu=Data(), int idKlienta=0);
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

        const Data& zwrocTerminZwrotu() const;
        void ustawTerminZwrotu(const Data& val);

        int zwrocIdKlienta() const;
        void ustawIdKlienta(int val);

};

#endif