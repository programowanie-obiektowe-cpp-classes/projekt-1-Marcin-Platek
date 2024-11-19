#ifndef FIRMA_HPP
#define FIRMA_HPP
#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include "Pracownik.hpp"
#include "Kredyt.hpp"

using namespace std;

extern default_random_engine random_generator;
extern uniform_real_distribution<double> complaints_distribution;
extern uniform_real_distribution<double> defects_distribution;
extern uniform_real_distribution<double> demand_distribution;
extern uniform_real_distribution<double> price_distribution;

// stałe dla wydajności pracowników
extern const int CInz;
extern const int CMag;
extern const int CMkt;
extern const int CRob;
extern const int MAX_PAYOFF_TIME;
extern const double M;
extern const int N;  // Liczba miesięcy do obliczenia wartości spółki

extern int id_next_engineer;
extern int id_next_seller;
extern int id_next_worker;
extern int id_next_warehouseman;

class Firma
{
    public:
        Firma();
        double determine_company_value() const;
        void update_revenues(double revenue);
        static const int N; // Deklaracja liczby miesięcy wziętych pod uwagę przy obliczaniu wartości spółki, bez inicjalizacji konkretną wartością
        void hire(unique_ptr<Pracownik> employee);
        void take_out_a_loan(double amount, int payoff_time);
        void pay_salaries();
        void pay_installments();
        double count_revenue();
        void get_revenue();
        void employment_summary() const;
        void display_newest_employee() const;
        void display_employee_details() const; 
        double get_account_balance() const;
        void show_company_summary() const;

    private:
        double account_balance;
        int number_of_employees;
        int number_of_credits;
        int number_of_engineers;
        int number_of_sellers;
        int number_of_workers;
        int number_of_warehousemen;
        int warehouse_load;
        int warehouse_capacity;
        vector<unique_ptr<Pracownik>> list_of_employees;
        vector<unique_ptr<Kredyt>> list_of_credits;
        vector<double> list_of_recent_revenues;
};

#endif // FIRMA_HPP