#include "data.hpp"
using namespace std;

Data::Data(int dzien, int miesiac, int rok)
    : dzien(dzien), miesiac(miesiac), rok(rok) {}

Data::~Data() = default;

int Data::zwrocDzien() const{
    return dzien;
}

void Data::ustawDzien(int val){
    dzien = val;
}

int Data::zwrocMiesiac() const{
    return miesiac;
}

void Data::ustawMiesiac(int val){
    miesiac = val;
}

int Data::zwrocRok() const{
    return rok;
}

void Data::ustawRok(int val){
    rok = val;
}

