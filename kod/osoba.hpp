#ifndef OSOBA_HPP
#define OSOBA_HPP
using namespace std;
#include <string>

class Osoba {
    protected:
        string imie;
        string nazwisko;
        int id;
    
    public:
        Osoba(const string& imie="", const string& nazwisko="", int id=0);
        virtual ~Osoba();

        const string& zwrocImie() const;
        void ustawImie(const string& val);
        const string& zwrocNazwisko() const;
        void ustawNazwisko(const string& val);
        int zwrocId() const;
        void ustawId(int val);
};

#endif