#ifndef POZYCJAREZERWACJI_HPP
#define POZYCJAREZERWACJI_HPP

#include "pojazd.hpp"

class pozycjaRezerwacji{
    
    private:
        Pojazd pojazd;

    public:
        pozycjaRezerwacji(const Pojazd& pojazd=Pojazd());
        virtual ~pozycjaRezerwacji();

        const Pojazd& zwrocPojazd() const;
        void ustawPojazd(const Pojazd& val);

};



#endif