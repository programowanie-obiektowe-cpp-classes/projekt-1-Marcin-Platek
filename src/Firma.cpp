#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include <iomanip> // Tabelki
#include "Firma.hpp"
#include "Pracownik.hpp"
#include "Kredyt.hpp"
#include "RandomNameGenerator.hpp"

using namespace std;

// Definicje globalnych zmiennych
std::default_random_engine random_generator;
std::uniform_real_distribution<double> complaints_distribution(0.0, 0.02);
std::uniform_real_distribution<double> defects_distribution(0.0, 0.01);
std::uniform_real_distribution<double> demand_distribution(0.9, 1.1);
std::uniform_real_distribution<double> price_distribution(0.9, 1.1);

const int CInz = 100;
const int CMag = 70;
const int CMkt = 80;
const int CRob = 120;
const int MAX_PAYOFF_TIME = 36;
const double M = 1.5;
const int Firma::N = 3;  // Liczba miesięcy do obliczenia wartości spółki

int id_next_engineer = 1;
int id_next_seller = 1;
int id_next_worker = 1;
int id_next_warehouseman = 1;

// Implementacja metod klasy Firma

Firma::Firma() : account_balance(100000), number_of_employees(0), number_of_credits(0), number_of_engineers(0), number_of_sellers(0), number_of_workers(0), number_of_warehousemen(0), warehouse_load(0), warehouse_capacity(0)
{
    // Zatrudnianie pracowników z domyślnymi wartościami
    hire(make_unique<Inzynier>(getRandomName(), "MEiL"));
    hire(make_unique<Handlowiec>(getRandomName(), 5000));
    hire(make_unique<Robotnik>(getRandomName(), 44.5));
    hire(make_unique<Magazynier>(getRandomName(), true));
}

double Firma::determine_company_value() const
{
    int number_of_months = min(static_cast<int>(list_of_recent_revenues.size()), N);
    if (number_of_months == 0)
        return 0;

    double sum_of_revenues = 0;
    for (int i = 0; i < number_of_months; i++)
    {
        sum_of_revenues += list_of_recent_revenues[i];
    }
    return sum_of_revenues / number_of_months;
}

void Firma::update_revenues(double revenue)
{
    if (list_of_recent_revenues.size() >= N)
    {
        list_of_recent_revenues.erase(list_of_recent_revenues.begin());
    }
    list_of_recent_revenues.push_back(revenue);
}

void Firma::hire(unique_ptr<Pracownik> employee) {
    // Przypisz losowe imię i nazwisko nowemu pracownikowi
    employee->setName(getRandomName());

    // Jeśli nie jest to pierwsza tura, pobierz szczegóły od użytkownika
    if (number_of_employees >= 4) { // Pierwsze 4 zatrudnienia mają domyślne wartości (widoczne powyżej w kodzie)
        employee->inputDetails();
    }

    if (dynamic_cast<Inzynier*>(employee.get()))
        number_of_engineers++;
    else if (dynamic_cast<Handlowiec*>(employee.get()))
        number_of_sellers++;
    else if (dynamic_cast<Robotnik*>(employee.get()))
        number_of_workers++;
    else if (dynamic_cast<Magazynier*>(employee.get()))
        number_of_warehousemen++;

    list_of_employees.push_back(move(employee));
    number_of_employees++;
}

void Firma::take_out_a_loan(double amount, int payoff_time)
{
    if (payoff_time > MAX_PAYOFF_TIME)
    {
        cout << " Okres splaty zbyt dlugi, niezgodnosc ze strategia firmy. Maksymalny dopuszczalny okres splaty kredytu wynosi " << MAX_PAYOFF_TIME << " miesiecy." << endl;
        return;
    }

    double company_value = determine_company_value();
    double max_debt = M * company_value;
    double current_debt = 0;

    for (const auto& credit : list_of_credits)
    {
        if (!credit->is_liquidated())
        {
            current_debt += credit->pay_installment() * credit->get_remaining_installments();
        }
    }

    if (current_debt + amount > max_debt)
    {
        cout << endl << "Zadluzenie przekracza maksymalny dopuszczalny limit! Odmowa wziecia kredytu." << endl;
        return;
    }

    list_of_credits.push_back(make_unique<Kredyt>(amount, payoff_time));
    number_of_credits++;
    account_balance += amount;
}

void Firma::pay_salaries()
{
    int total_salary_engineers = number_of_engineers * 5000;
    int total_salary_sellers = number_of_sellers * 4000;
    int total_salary_workers = number_of_workers * 3500;
    int total_salary_warehousemen = number_of_warehousemen * 3000;
    int total_salary_employees = total_salary_engineers + total_salary_sellers + total_salary_workers + total_salary_warehousemen;

    account_balance -= total_salary_employees;
}

void Firma::pay_installments()
{
    for (auto it = list_of_credits.begin(); it != list_of_credits.end();)
    {
        double installment_amount = (*it)->pay_installment();
        account_balance -= installment_amount;

        if ((*it)->is_liquidated())
        {
            it = list_of_credits.erase(it);
            number_of_credits--;
        }
        else
            ++it;
    }
}

double Firma::count_revenue()
{
    int assumed_warehouse_capacity = number_of_warehousemen * CMag;
    int assumed_product_price = number_of_engineers * CInz;
    int assumed_demand = number_of_sellers * CMkt;
    int assumed_production = number_of_workers * CRob;

    int product_price = assumed_product_price * price_distribution(random_generator);
    int demand = assumed_demand * demand_distribution(random_generator);

    int defects = static_cast<int>(assumed_production * defects_distribution(random_generator));
    int real_production = assumed_production - defects;

    int production = min(real_production, assumed_warehouse_capacity - warehouse_load);

    int available_products = warehouse_load + production;
    int sold_products = min(available_products, demand);

    int complaints = static_cast<int>(sold_products * complaints_distribution(random_generator));

    // Aktualizacja warehouse_load zgodnie z Twoimi wymaganiami
    warehouse_load = available_products - sold_products + complaints;

    int monthly_revenue = (sold_products - complaints) * product_price;

    return monthly_revenue;
}

void Firma::get_revenue()
{
    double revenue = count_revenue();
    update_revenues(revenue);
    account_balance += revenue;
}

void Firma::employment_summary() const
{
    cout << "\n** ** Podsumowanie zatrudnienia ** **" << endl;

    cout << "+----------------------------+---------------------------+" << endl;
    cout << "|          Stanowisko        |    Ilosc zatrudnionych    |" << endl;
    cout << "+----------------------------+---------------------------+" << endl;
    cout << "| Wszyscy pracownicy         | " << setw(25) << number_of_employees << " |" << endl;
    cout << "| Inzynierowie               | " << setw(25) << number_of_engineers << " |" << endl;
    cout << "| Handlowcy                  | " << setw(25) << number_of_sellers << " |" << endl;
    cout << "| Robotnicy                  | " << setw(25) << number_of_workers << " |" << endl;
    cout << "| Magazynierzy               | " << setw(25) << number_of_warehousemen << " |" << endl;
    cout << "+----------------------------+---------------------------+" << endl << endl;
}

void Firma::display_newest_employee() const {
    if (!list_of_employees.empty()) {
        cout << "** ** Szczegoly nowo zatrudnionego pracownika ** **" << endl;
        list_of_employees.back()->print();
    }
}

void Firma::display_employee_details() const {
    cout << "** ** Szczegolowe informacje o wszystkich zatrudnionych pracownikach ** **" << endl<<endl;
    for (const auto& employee : list_of_employees) {
        if (dynamic_cast<Inzynier*>(employee.get())) {
            employee->print();
        }
    }
    for (const auto& employee : list_of_employees) {
        if (dynamic_cast<Handlowiec*>(employee.get())) {
            employee->print();
        }
    }
    for (const auto& employee : list_of_employees) {
        if (dynamic_cast<Robotnik*>(employee.get())) {
            employee->print();
        }
    }
    for (const auto& employee : list_of_employees) {
        if (dynamic_cast<Magazynier*>(employee.get())) {
            employee->print();
        }
    }
}


double Firma::get_account_balance() const
{
    return account_balance;
}

void Firma::show_company_summary() const
{
    int product_price = number_of_engineers * CInz;
    int demand = number_of_sellers * CMkt;
    int production = number_of_workers * CRob;
    int warehouse_capacity = number_of_warehousemen * CMag;
    double company_value = determine_company_value();

    cout << endl << "       ** ** Informacje o statusie firmy ** **" << endl;

    cout << "+------------------------------+--------------------------+" << endl;
    cout << "|           Opis               |          Wartosc         |" << endl;
    cout << "+------------------------------+--------------------------+" << endl;
    cout << "| Sugerowana cena produktu     | " << setw(20) << product_price << " PLN |" << endl;
    cout << "| Oczekiwany popyt             | " << setw(18) << demand << " sztuk |" << endl;
    cout << "| Zakladana produkcja          | " << setw(18) << production << " sztuk |" << endl;
    cout << "| Zakladana pojemnosc magazynu | " << setw(18) << warehouse_capacity << " sztuk |" << endl;
    cout << "| Stany magazynowe             | " << setw(18) << warehouse_load << " sztuk |" << endl;
    cout << "| Stan finansowy               | " << setw(20) << get_account_balance() << " PLN |" << endl;
    cout << "| Obecna zdolnosc kredytowa    | " << setw(20) << company_value << " PLN |" << endl;
    cout << "+------------------------------+--------------------------+" << endl;
}
