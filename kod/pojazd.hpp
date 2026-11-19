#ifndef POJAZD_HPP
#define POJAZD_HPP

using namespace std;

#include "data.hpp"
#include <string>
#include <iostream>

/*
Status pojazdu
0 - niedostepny
1 - dostepny
*/

class Pojazd{
    private:
        int id;
        string marka;
        string model;
        int rocznik;
        string nrRej;
        Data dataPrzegladu;
        bool status;
    
    public:
        Pojazd(int id=0, const string& marka="", const string& model="", int rocznik=0, const string& nrRej="", const Data& dataPrzegladu=Data(), bool status=0);
        virtual ~Pojazd();

        int zwrocId() const;

        bool zwrocStatus() const;
        void ustawStatus(bool val);

        void wypisz() const;
};

#endif