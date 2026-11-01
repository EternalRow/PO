#ifndef DATE_HPP
#define DATE_HPP

class Data{
    private:
        int dzien;
        int miesiac;
        int rok;

    public:
        Data(int dzien=0, int miesiac=0, int rok=0);
        virtual ~Data();

        int zwrocDzien() const;
        void ustawDzien(int val);
        int zwrocMiesiac() const;
        void ustawMiesiac(int val);
        int zwrocRok() const;
        void ustawRok(int val);
};

#endif