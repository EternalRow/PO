#ifndef POJAZD_HPP
#define POJAZD_HPP

using namespace std;

#include "data.hpp"
#include <string>

class Pojazd{
    private:
        string marka;
        string model;
        int rocznik;
        string nrRej;
        Data dataPrzegladu;
        bool status;
    
    public:
        Pojazd(const string& marka="", const string& model="", int rocznik=0, const string& nrRej="", const Data& dataPrzegladu=Data(), bool status=0);
        virtual ~Pojazd();

        const string& zwrocMarke() const;
        void ustawMarke(const string& val);
        
        const string& zwrocModel() const;
        void ustawModel(const string& val);
        
        int zwrocRocznik() const;
        void ustawRocznik(int val);
        
        const string& zwrocNrRej() const;
        void ustawNrRej(const string& val);

        const Data& zwrocDatePrzegladu() const;
        void ustawDatePrzegladu(int dzien, int miesiac, int rok);

        bool zwrocStatus() const;
        void ustawStatus(bool val);

        void wypisz() const;
};

#endif