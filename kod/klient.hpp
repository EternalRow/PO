#ifndef KLIENT_HPP
#define KLIENT_HPP

using namespace std;

#include <string>
#include "osoba.hpp"


class Klient : public Osoba {
    private:
        string email;
    
    public:
        Klient(const string& imie="", const string& nazwisko="", const string& email="", int id=0);
        virtual ~Klient();

        const string& wezEmail() const;
        void ustawEmail(const string& val);
};

#endif