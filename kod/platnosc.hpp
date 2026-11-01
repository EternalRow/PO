#ifndef PLATNOSC_HPP
#define PLATNOSC_HPP

#include "data.hpp"

class Platnosc{
    private:
        float kwota;
        int status;
        Data dataPrzelewu;
        int idRezerwacji;
        int id;
    
    public:
        Platnosc(const Data& dataPrzelewu=Data(), float kwota=0.0, int status=0, int idRezerwacji=0, int id=0);
        virtual ~Platnosc();

        int zwrocStatus() const;
        void ustawStatus(int val);

        float zwrocKwote() const;
        void ustawKwote(float val);

        const Data& zwrocDatePrzelewu() const;
        void ustawDatePrzelewu(const Data& val);

        int zwrocIdRezerwacji() const;
        void ustawIdRezerwacji(int val);

        int zwrocId() const;
        void ustawId(int val);
};

#endif