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

        int zwrocId() const;
};

#endif