#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include "Kredyt.hpp"

using namespace std;

// Implementacja metod klas zdefiniowanych w Kredyt.hpp

// Implementacja konstruktora klasy Kredyt
Kredyt::Kredyt(double amount, int remaining_installments) : remaining_installments(remaining_installments)
{
    // Dodanie oprocentowania 8% w skali roku
    double bank_rate = 0.08;
    double total_debt = amount * (1 + (bank_rate * (remaining_installments / 12.0)));
    tmp_debt = total_debt;
}

// Implementacja metody get_remaining_installments
int Kredyt::get_remaining_installments() const
{
    return remaining_installments;
}

// Implementacja metody pay_installment
double Kredyt::pay_installment()
{
    if (remaining_installments > 0)
    {
        double tmp_installment = tmp_debt / remaining_installments;
        remaining_installments--;
        return tmp_installment;
    }
    return 0;
}

// Implementacja metody is_liquidated
bool Kredyt::is_liquidated() const
{
    return remaining_installments == 0;
}




