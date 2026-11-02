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
using namespace std;

class SystemRezerwacji{
    private:
        vector<Klient> klienci;
        vector<Platnosc> platnosci;
        vector<Pracownik> pracownicy;
        vector<Pojazd> pojazdy;
        vector<Rezerwacja> rezerwacje;
        vector<Pojazd> dostepne;
        
    public:
        SystemRezerwacji(const vector<Klient> klienci={}, const vector<Pracownik> pracownicy={}, const vector<Pojazd> pojazdy={}, const vector<Rezerwacja> rezerwacje={}, const vector<Pojazd> dostepne={}, const vector<Platnosc> platnosci={});
        virtual ~SystemRezerwacji();

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

        const vector<Pojazd>& zwrocDostepne() const;
        void ustawDostepne(const vector<Pojazd>& val);

        bool zarezerwuj(int id_osoby, string nr_pojazdu, Data data, int okres);
        void katalog();
        bool dodajPojazd(Pojazd pojazd);
        void potwierdzRezerwacje(int id_platnosci);

        void zwrocPojazdy(int id_rezerwacji);
        void naliczKare(int id_rezerwacji);


};

#endif