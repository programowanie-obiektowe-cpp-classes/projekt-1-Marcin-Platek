#ifndef PRACOWNIK_HPP
#define PRACOWNIK_HPP
#include <iostream>
#include <fstream>
using namespace std;

class Pracownik
{
    public:
        Pracownik(string name);
        virtual ~Pracownik() = default;
        virtual void print() const = 0;
        virtual void inputDetails() = 0;
        void setName(string new_name); 
    
    protected:
        string name;
};

// klasa pochodna Inzynier
class Inzynier : public Pracownik
{
    public:
        Inzynier(string name, string faculty);
        void print() const override;
        void inputDetails() override;

    private:
        string faculty;
};

// klasa pochodna Handlowiec
class Handlowiec : public Pracownik
{
    public:
        Handlowiec(string name, int followers);
        void print() const override;
        void inputDetails() override;

    private:
        int followers;
};

// klasa pochodna Robotnik
class Robotnik : public Pracownik
{
    public:
        Robotnik(string name, double shoe_size);
        void print() const override;
        void inputDetails() override;

    private:
        double shoe_size;
};

// klasa pochodna Magazynier
class Magazynier : public Pracownik
{
    public:
        Magazynier(string name, bool eligibility);
        void print() const override;
        void inputDetails() override;
    
    private:
        bool eligibility;
};

#endif // PRACOWNIK_HPP