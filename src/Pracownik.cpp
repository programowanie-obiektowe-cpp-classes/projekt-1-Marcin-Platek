#include "Pracownik.hpp"
#include <iostream>
using namespace std;

// Implementacja metod klas zdefiniowanych w Pracownik.hpp

// Implementacja konstruktora klasy Pracownik
Pracownik::Pracownik(string name) : name(name) {}

// Implementacja metody setName klasy Pracownik
void Pracownik::setName(string new_name) {
    name = new_name;
}

// Implementacja konstruktora, metody print i inputDetails klasy Inzynier
Inzynier::Inzynier(string name, string faculty) : Pracownik(name), faculty(faculty) {}
void Inzynier::print() const
{
    cout << "Inzynier " << name << ", ktory(a) ukonczyl(a) wydzial " << faculty << endl;
}
void Inzynier::inputDetails() 
{
    cout << "Podaj nazwe wydzialu, ktory ukonczyl inzynier: ";
    getline(cin, faculty);
}

// Implementacja konstruktora, metody print i inputDetails klasy Handlowiec
Handlowiec::Handlowiec(string name, int followers) : Pracownik(name), followers(followers) {}
void Handlowiec::print() const
{
    cout << "Handlowiec " << name << ", liczba obserwujacych w mediach spolecznosciowych: " << followers << endl;
}
void Handlowiec::inputDetails() 
{
    do {
        cout << "Podaj liczbe subskrybentww (z zakresu 5 - 200000): ";
        cin >> followers;
        if (followers < 5 || followers > 200000) {
            cout << "Bledna wartosc subskrybentow. Podaj z zakresu 5 - 200000." << endl;
        }
    } while (followers < 5 || followers > 200000);
}

// Implementacja konstruktora, metody print i inputDetails klasy Robotnik
Robotnik::Robotnik(string name, double shoe_size) : Pracownik(name), shoe_size(shoe_size) {}
void Robotnik::print() const
{
    cout << "Robotnik " << name << ", posiadajacy(a) rozmiar buta " << shoe_size << endl;
}
void Robotnik::inputDetails() 
{
    do {
        cout << "Podaj rozmiar buta (z zakresu 30 - 55): ";
        cin >> shoe_size;
        if (shoe_size < 30 || shoe_size > 55) {
            cout << "Niefizyczny rozmiar stopy. Podaj z zakresu 30 - 55." << endl;
        }
    } while (shoe_size < 30 || shoe_size > 55);
}

// Implementacja konstruktora, metody print i inputDetails klasy Magazynier
Magazynier::Magazynier(string name, bool eligibility) : Pracownik(name), eligibility(eligibility) {}
void Magazynier::print() const
{
    cout << "Magazynier " << name << " ";
    if (eligibility)
        cout << "posiadajacy(a) uprawnienia do jazdy wozkiem widlowym" << endl;
    else
        cout << "nie posiadajacy(a) uprawnien do jazdy wozkiem widlowym" << endl;
}
void Magazynier::inputDetails()
{
    string response;
    do {
        cout << "Czy magazynier posiada uprawnienia do jazdy wozkiem widlowym? (tak/nie): ";
        cin >> response;
        if (response == "tak") {
            eligibility = true;
        } else if (response == "nie") {
            eligibility = false;
        } else {
            cout << "Bledna wartosc. Wpisz 'tak' albo 'nie'." << endl;
        }
    } while (response != "tak" && response != "nie");
}