#ifndef PRACOWNIK_HPP
#define PRACOWNIK_HPP

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

        int zwrocIdPracownicze() const;
        void ustawIdPracownicze(int val);
};

#endif