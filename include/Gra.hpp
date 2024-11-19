#ifndef GRA_HPP
#define GRA_HPP
#include <iostream>
#include <fstream>
#include <memory>
#include "Firma.hpp"

using namespace std;

// Stale dla wydajnosci pracownikow
extern const int CInz;
extern const int CMag;
extern const int CMkt;
extern const int CRob;
extern const int MAX_KREDYT;
extern const double M;

extern int id_next_engineer;
extern int id_next_seller;
extern int id_next_worker;
extern int id_next_warehouseman;

class Gra
{
    public:
        Gra();
        void player_action();
        bool get_state() const;
        void tick();

    private:
        unique_ptr<Firma> company;
        bool game_state;
        bool is_first_turn;  
        int turn_counter;    
};

#endif // GRA_HPP
