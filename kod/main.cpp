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
        cout << endl;
        if(rola == 1){ // czy pracownik powinien zalogowac sie; podać id pracownicze?
            while(true){
                cout << endl << "Wybierz funkcjonalność, którą chcesz przetestować:" << endl
                << "1 - wyświetlanie informacji" << endl
                << "2 - dodawanie danych" << endl
                << "3 - zarejestruj zwrot pojazdu" << endl
                << "4 - zamknij rezerwację" << endl
                << "5 - usuwanie danych z systemu" << endl
                << "dowolna inna wartość, aby wrócić do wyboru roli" << endl;
                int funkcja = 0;
                int opcja = 0;
                cin >> funkcja;
                cout << endl;

                if (funkcja == 1){
                    cout << endl << "1 - wyświetl listę pojazdów" << endl
                    << "2 - wyświetl listę pracowników" << endl
                    << "3 - wyświetl listę klientów" << endl
                    << "4 - wyświetl listę płatności" << endl
                    << "5 - wyświetl listę rezerwacji" << endl
                    << "inna wartość - powrót do wyboru fukcjonalności" << endl;
                    cin >> opcja;
                    cout << endl;
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
                    cout << endl;
                    while (opcja < 0 || opcja > 2){
                        cout << "Podaj poprawną wartość." << endl;
                        cin >> opcja;
                    }
                    if (opcja == 1){
                        system.dodajPojazdInteraktywnie();
                    }else if(opcja == 2){
                        system.dodajKlientaInteraktywnie();
                    }
                }else if (funkcja==3){
                    bool wyn = system.zarejestrujZwrotPojazdu();
                    if (wyn){
                        cout << "Zakończono proces zwrotu pojazdów. Po weryfikacji przez pracownika rezerwacja zostanie zamknięta." << endl;
                    }else{
                        cout << "Nałożono płatność dodatkową za przedłużenie lub przekroczenie terminu zwrotu." << endl;
                    }
                }else if (funkcja==4){
                    system.zamknijRezerwacje();
                }else if (funkcja==5){
                    while(true){
                        int opcja;
                        cout << "1 - usuń rezerwację" << endl
                        << "2 - usuń pojazd" << endl
                        << "3 - usuń klienta" << endl
                        << "inna wartość - powrót do wyboru funkcjonalności" << endl;
                        cin >> opcja;
                        if (opcja==1){
                            system.usunRezerwacje();
                        }else if (opcja==2){
                            system.usunPojazd();
                        }else if (opcja==3){
                            system.usunKlienta();
                        }else{
                            break;
                        }
                    }
                }
                else{
                    break;
                }
            }
        }
        else if (rola==2){
            string email;
            while(true){
                cout << "Podaj email:" << endl;
                cin >> email;
                
                if (system.walidujEmail(email)==false){
                    cout << "Niepoprawny email" << endl;
                }
                else{
                    cout << "Zalogowano." << endl;
                    
                    int funkcja;

                    while(true){
                        cout << "\nWybierz funkcjonalność:" << endl
                        << "1 - wyświetl listę pojazdów" << endl
                        << "2 - zarezerwuj pojazd" << endl
                        << "3 - przedłuż rezerwację" << endl
                        << "4 - opłać rezerwację" << endl
                        << "5 - opłać płatności dodatkowe" << endl
                        << "6 - wyświetl moje rezerwacje" << endl
                        << "inna wartość, aby powrócić do wyboru roli" << endl;

                        cin >> funkcja;
                        cout << endl;

                        if(funkcja == 1){
                            system.katalog();
                        }else if(funkcja == 2){
                            system.zarezerwujInteraktywnie(email);
                        }else if(funkcja==3){
                            bool wyn = system.przedluz(email);
                            if(wyn){
                                cout << "Przedłużono termin zwrotu pojazdów o 7 dni dla rezerwacji o podanym ID." << endl;
                            }
                            else{
                                cout << "Nie udało się przedłużyć." << endl;
                            }
                        }else if(funkcja==4){
                            bool wyn = system.oplacRezerwacje(email);
                            if (wyn){
                                cout << "Pomyślnie opłacono rezerwacje. Rezerwacja jest aktywna." << endl;
                            }else{
                                cout << "Nie udało się opłacić; rezerwacja jest już opłacona, lub podano błędne ID." << endl;
                            }
                        }else if(funkcja==5){ //wywalic couty do systemu?
                            bool wyn = system.oplacDodatkowe(email);
                            if (wyn){
                                cout << "Pomyślnie opłacono. Po weryfikacji przez pracownika rezerwacja zostanie zamknięta." << endl;
                            }else{
                                cout << "Nie udało się opłacić; rezerwacja nie wymaga dodatkowej opłaty, lub podano błędne ID." << endl;
                            }
                        }else if (funkcja==6){
                            system.wypiszRezerwacjeKlienta(email);
                        }
                        else{
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
}