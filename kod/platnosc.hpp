#ifndef PLATNOSC_HPP
#define PLATNOSC_HPP

#include "data.hpp"

class Platnosc{
    private:
        float kwota;
        int status;
        Data dataPrzelewu;
        int id;
    
    public:
        Platnosc(float kwota=0.0, int status=0, const Data& dataPrzelewu=Data(), int id=0);
        virtual ~Platnosc();

        int zwrocStatus() const;
        void ustawStatus(int val);

        float zwrocKwote() const;
        void ustawKwote(float val);

        const Data& zwrocDatePrzelewu() const;
        void ustawDatePrzelewu(int dzien, int miesiac, int rok);

        int zwrocId() const;
        void ustawId(int val);

};

#endif