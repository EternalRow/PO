#ifndef PLATNOSC_HPP
#define PLATNOSC_HPP

using namespace std;

#include <string>
#include "osoba.hpp"

class Pracownik : public Osoba
{
    private:
        int idPracownicze;
    
    public:
        Pracownik(const string& imie="", const string& nazwisko="", const int id=0, const int idPracownicze=0);
        virtual ~Pracownik();

        int wezIdPracownicze() const;
        void ustawId(int val);
};

#endif