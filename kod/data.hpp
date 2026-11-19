#ifndef DATA_HPP
#define DATA_HPP

using namespace std;
#include <iostream>

class Data{
    private:
        int dzien;
        int miesiac;
        int rok;

    public:
        Data(int dzien=0, int miesiac=0, int rok=0);
        virtual ~Data();
        void ustawDzien(int val);
        void ustawMiesiac(int val);
        void ustawRok(int val);

        void wypisz() const;
};

#endif