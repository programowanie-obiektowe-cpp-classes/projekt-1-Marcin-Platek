#ifndef KREDYT_HPP
#define KREDYT_HPP
#include <iostream>
#include <fstream>
using namespace std;

class Kredyt 
{
    private:
        double tmp_debt;
        int remaining_installments;

    public:
        int get_remaining_installments() const;
        Kredyt(double amount, int remaining_installments);
        double pay_installment();
        bool is_liquidated() const;
};

#endif // KREDYT_HPP