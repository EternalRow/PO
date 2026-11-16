#include "system_rezerwacji.hpp"
#include "klient.hpp"
#include "pojazd.hpp"
#include "data.hpp"
#include "pracownik.hpp"
#include <iostream>
#include <string>
#include <clocale>
using namespace std;

int main(){
    setlocale(LC_ALL, "pl_PL.UTF-8");//kodowanie znakow
    
    SystemRezerwacji system = SystemRezerwacji();

    //DANE NA START:
    //można zrobić ustawPojazdy();
    system.dodajPojazd("Audi", "A10", 2015, "FZG8310", Data(12,10,2026), 1);
    system.dodajPojazd("Honda", "Civic", 2011, "FZG810", Data(12,10,2026), 1);
    system.dodajPojazd("Renault", "Clio", 2009, "FZG879", Data(12,10,2026), 1);
    system.dodajPojazd("Toyota", "Corolla", 2021, "FZG001", Data(12,10,2026), 1);
    system.dodajPojazd("Hyundai", "Tucson", 2018, "FZG245", Data(12,10,2026), 1);
    

    vector<Klient> klientela = {Klient("Jan", "Kowalski", "email@example.com", 10), Klient("Anna", "Nowak", "anna@example.com", 11)};
    system.ustawKlienci(klientela);
    vector<Pracownik> pracownicy = {Pracownik("Aleksandra", "Maj", 101, 1), Pracownik("Katarzyna", "Kowal", 102, 2)};
    system.ustawPracownicy(pracownicy);

    // MENU
    while(true){
        int rola = 0;
        cout << "\nWitamy w systemie rezerwacji pojazdów. Wybierz rolę." << endl;
        cout << "1-pracownik, 2-klient (dowolny inny znak aby wyjść z systemu)" << endl;
        cin >> rola;

        if(rola == 1){ // czy pracownik powinien zalogowac sie; podać id pracownicze?
            while(true){
                cout << endl << "Wybierz funkcjonalność, którą chcesz przetestować:" << endl
                << "1 - wyświetlanie informacji" << endl
                << "2 - dodawanie danych" << endl
                << "3 - zarejestruj zwrot pojazdu" << endl
                << "4 - usuń rezerwację z systemu" << endl // !!!!!!!!!dodaj poniżej (dekonstruktor)
                << "dowolna inna wartość, aby wrócić do wyboru roli" << endl;
                int funkcja = 0;
                int opcja = 0;
                cin >> funkcja;

                if (funkcja == 1){
                    cout << endl << "1 - wyświetl listę pojazdów" << endl
                    << "2 - wyświetl listę pracowników" << endl
                    << "3 - wyświetl listę klientów" << endl
                    << "4 - wyświetl listę płatności" << endl
                    << "5 - wyświetl listę rezerwacji" << endl
                    << "inna wartość - powrót do wyboru fukcjonalności" << endl;
                    cin >> opcja;
                    while (opcja < 1 || opcja > 5){
                        cout << "Podaj poprawną wartość." << endl;
                        cin >> opcja;
                    }
                    if (opcja == 1){
                        system.katalog();
                    }else if (opcja ==2){
                        system.wypiszPracownicy();
                    }else if (opcja == 3){
                        system.wypiszKlienci();
                    }else if (opcja == 4){
                        system.wypiszPlatnosci();
                    }else if (opcja == 5){
                        system.wypiszRezerwacje();
                    }
                }else if (funkcja==2){
                    cout << "1 - dodaj pojazd" << endl
                    << "2 - dodaj klienta" << endl;
                    cin >> opcja;
                    while (opcja < 0 || opcja > 2){
                        cout << "Podaj poprawną wartość." << endl;
                        cin >> opcja;
                    }
                    if (opcja == 1){
                        string marka, model, nrRej;
                        int rocznik, d, m, r;
                        char kropka;
                        cout << "Podaj markę: ";
                        cin >> marka;
                        cout << "Podaj model: ";
                        cin >> model;
                        cout << "Podaj numer rejestracyjny: ";
                        cin >> nrRej;
                        cout << "Podaj rocznik: ";
                        cin >> rocznik;
                        cout << "Podaj datę przeglądu w formacie DD.MM.RRRR (np. 31.04.2025): ";
                        cin >> d >> kropka >> m >> kropka >> r;
                        Data dataPrzeg = Data(d,m,r);
                        system.dodajPojazd(marka, model, rocznik, nrRej, dataPrzeg, 1);
                        cout << "Pomyślnie dodano pojazd." << endl;
                    }else if(opcja == 2){
                        string imie, nazwisko, email;
                        int id;
                        cout << "Podaj imię: ";
                        cin >> imie;
                        cout << "Podaj nazwisko: ";
                        cin >> nazwisko;
                        cout << "Podaj email: ";
                        cin >> email;
                        cout << "Podaj id: ";
                        cin >> id;  // !!!sprawdzic czy unikalne?
                        system.dodajKlienta(imie, nazwisko, email, id);
                        cout << "Klient dodany pomyślnie." << endl;
                    }
                }else if (funkcja==3){
                    cout << "Podaj numer id rezerwacji, jakiej dotyczy zwrot (0 by wyświetlić listę rezerwacji): ";
                    int nr;
                    cin >> nr;
                    if (nr==0){
                        system.wypiszRezerwacje();
                        cout << "Podaj nr rezerwacji: ";
                        cin >> nr; //zakładamy, że użytkownik poda prawidłowy numer ALE CHYBA NALEŻY SPRAWDZIĆ
                    }
                    Rezerwacja rez_do_zwrotu = system.zwrocWybranaRezerwacje(nr);
                    cout << "Podaj okres (w dniach), przez jaki korzystano z pojazdów: ";
                    int dni;
                    cin >> dni;
                    bool wyn = system.zarejestrujZwrotPojazdu(rez_do_zwrotu, dni);
                    cout << "Zakończono proces zwrotu pojazdów" << endl; //!!!!!!!dodaj sprawdzenie, czy jednoczesnie zamknieto rezerwacje, czy moze dodano platnosc dodatkowa
                }
                else{
                    break;
                }
            }
            
        }
        else if (rola==2){
            string email;
            Klient klient_rezerwujacy;
            vector<Klient> klienci_w_systemie = system.zwrocKlienci();
            while(true){
                cout << "Podaj email:" << endl;
                cin >> email;
                int liczba_iteracji=0;

                for(int i=0;i<klienci_w_systemie.size();i++){
                    if(klienci_w_systemie[i].zwrocEmail() == email){
                        klient_rezerwujacy = klienci_w_systemie[i];
                        break;
                    }
                    liczba_iteracji += 1;
                }
                if(liczba_iteracji==klienci_w_systemie.size()){
                    cout << "Niepoprawny email" << endl;
                }
                else{
                    cout << "Zalogowano." << endl;
                    
                    int funkcja;

                    while(true){
                        cout << "\nWybierz funkcjonalność:" << endl
                        << "1 - wyświetl listę pojazdów" << endl
                        << "2 - zarejestruj pojazd" << endl
                        << "3 - przedłuż rezerwację" << endl
                        << "4 - opłać rezerwację" << endl
                        << "5 - opłać płatności dodatkowe" << endl
                        << "inna wartość, aby powrócić do wyboru roli" << endl;

                        cin >> funkcja;

                        if(funkcja == 1){
                            system.katalog();
                        }else if(funkcja == 2){
                            int opcja;
                            cout << "Czy chcesz wyświetlić katalog przed wyborem pojazdu?" << endl
                            << "1-tak, inna wartość - nie" << endl;
                            cin >> opcja;

                            if (opcja==1){
                                system.katalog();
                            }
                            vector<Pojazd> pojazdy_w_systemie = system.zwrocPojazdy();
                            vector<Pojazd> pojazdy_do_rezerwacji;
                            int id_pojazdu;

                            while (true){
                                cout << "Podaj numer samochodu do rezerwacji lub wpisz 0, aby zakończyć: ";
                                cin >> id_pojazdu;
                                if (id_pojazdu == 0){
                                    break;
                                }else{
                                    if (pojazdy_w_systemie[id_pojazdu-1].zwrocStatus() == 0){
                                        cout << "Pojazd niedostępny." << endl;
                                    }else{
                                        pojazdy_do_rezerwacji.push_back(pojazdy_w_systemie[id_pojazdu-1]);
                                    }
                                }
                            }
                            if(pojazdy_do_rezerwacji.size() == 0){
                                cout << "Nie wybrano samochodów. Wyjście z procesu rezerwacji..." << endl;
                            }
                            else{

                                cout << "Podaj datę wypożyczenia (odbioru) w formacie DD.MM.RRRR, np. 01.04.2027" << endl;
                                int d, m, r;
                                char kropka;
                                cin >> d >> kropka >> m >> kropka >> r;
                                Data data = Data(d,m,r);

                                int okres;
                                cout << "Podaj okres wypożyczenia w dniach: ";
                                cin >> okres;

                                Rezerwacja nowa_rez = system.zarezerwuj(klient_rezerwujacy, pojazdy_do_rezerwacji, data, okres);
                                system.dodajRezerwacje(nowa_rez);
                                cout << "Zarezerwowano samochód. Dokonaj płatności, aby ją aktywować." << endl;
                            }
                        }else{
                            break;
                        }
                    }
                }
                break;
            }

        }else{
            break;
        }

    }
    return 0;
}