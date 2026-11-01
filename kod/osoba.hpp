#ifndef PLATNOSC_HPP
#define PLATNOSC_HPP
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

        const string& wezImie() const;
        void ustawImie(const string& val);
        const string& wezNazwisko() const;
        void ustawNazwisko(const string& val);
        int wezId() const;
        void ustawId(int val);
};

#endif