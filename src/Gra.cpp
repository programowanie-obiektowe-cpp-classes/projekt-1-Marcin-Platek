#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include "Pracownik.hpp"
#include "Kredyt.hpp"
#include "Firma.hpp"
#include "Gra.hpp"

using namespace std;

// Implementacja metod klasy Gra

Gra::Gra() : company(make_unique<Firma>()), game_state(true), is_first_turn(true), turn_counter(1) {}

void Gra::player_action() 
{
    cout << endl << "** ** Aktualna tura: " << turn_counter << " ** **" << endl;
    int command = -1;

    if (is_first_turn)
    {
        cout << "\n** ** Witaj w symulacji piramidy finansowej ** **" << endl << endl;
        is_first_turn = false;
    }
    else
    {
        cout << "\n** ** Wykonaj nastepny ruch ** **" << endl << endl;
    }

    cout << "Wybierz jedna z dostepnych opcji: " << endl;
    cout << "1. Pokaz informacje o statusie firmy" << endl;
    cout << "2. Pokaz informacje o statusie zatrudnienia w firmie" << endl;
    cout << "3. Zatrudnij inzyniera (5000PLN)" << endl;
    cout << "4. Zatrudnij handlowca (4000PLN)" << endl;
    cout << "5. Zatrudnij robotnika (3500PLN)" << endl;
    cout << "6. Zatrudnij magazyniera (3000PLN)" << endl;
    cout << "7. Wez kredyt" << endl;
    cout << "8. Podsumuj i przejdz do nastepnej tury" << endl;
    cout << "0. Wyjdz z gry" << endl << endl;
    cout << "Wpisz odpowiednia cyfre: ";
    cin >> command;
    cout << endl;

    switch (command)
    {
    case 1:
        company->show_company_summary();
        break;
    case 2:
        company->employment_summary();
        int sub_command;
        cout << "\nWybierz jedna z opcji: " << endl;
        cout << "1. Wroc do menu glownego" << endl;
        cout << "2. Pokaz szczegolowe dane pracownikow" << endl << endl;
        cout << "Wpisz odpowiednia cyfre: ";
        cin >> sub_command;
        if (sub_command == 2) 
        {   
            cout << endl;
            company->display_employee_details();
        }
        break;
    case 3: {
        auto new_employee = make_unique<Inzynier>("Inzynier_" + to_string(id_next_engineer++), "Mechanika");
        new_employee->inputDetails();
        company->hire(move(new_employee));
        cout << "Zatrudniono nowego inzyniera." << endl;
        company->display_newest_employee();
        break;
    }
    case 4: {
        auto new_employee = make_unique<Handlowiec>("Handlowiec_" + to_string(id_next_seller++), true);
        new_employee->inputDetails();
        company->hire(move(new_employee));
        cout << "Zatrudniono nowego handlowca." << endl;
        company->display_newest_employee();
        break;
    }
    case 5: {
        auto new_employee = make_unique<Robotnik>("Robotnik_" + to_string(id_next_worker++), 10500);
        new_employee->inputDetails();
        company->hire(move(new_employee));
        cout << "Zatrudniono nowego robotnika." << endl;
        company->display_newest_employee();
        break;
    }
    case 6: {
        auto new_employee = make_unique<Magazynier>("Magazynier_" + to_string(id_next_warehouseman++), 44.5);
        new_employee->inputDetails();
        company->hire(move(new_employee));
        cout << "Zatrudniono nowego magazyniera." << endl;
        company->display_newest_employee();
        break;
    }
    case 7:
    {
        double loan_amount;
        int payoff_time;
        cout << "Podaj oczekiwana kwote kredytu: ";
        cin >> loan_amount;
        cout << "Podaj proponowany czas splaty (w miesiacach): ";
        cin >> payoff_time;
        company->take_out_a_loan(loan_amount, payoff_time);
        break;
    }
    case 8:
        company->get_revenue();
        company->pay_salaries();
        company->pay_installments();
        cout << endl << "Aktualna tura: " << turn_counter << endl;
        ++turn_counter;

        cout << endl << "Dokonano obliczen stanu finansowego firmy po oplaceniu rat oraz wynagrodzen." << endl;
        cout << "Stan konta na koniec tury wynosi: " << company->get_account_balance() << " PLN" << endl<<endl;
        break;
    case 0:
        game_state = false;
        cout << "Dziekujemy za gre! Do zobaczenia." << endl;
        break;
    default:
        cout << "Nieznana komenda. Wprowadz poprawna komende." << endl;
    }
}

bool Gra::get_state() const
{
    return game_state;
}

void Gra::tick() {
    if (company->get_account_balance() >= 2000000) {
        cout << "Zarobiles na nowe Porsche 911 GT3 RS, jestes zwyciezca, gratuluje!" << endl;
        game_state = false;
        return;
    }
    if (company->get_account_balance() < 0)
    {
        cout << "Firma zbankrutowala, koniec grania i do spania." << endl;
        game_state = false;
    }
}
