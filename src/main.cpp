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

int main()
{
    Gra gra;
    while (gra.get_state())
    {
        try
        {
            gra.player_action();
            gra.tick();
        }
        catch (const exception& e)
        {
            cerr << "Wystąpił błąd: " << e.what() << endl;
            cin.clear(); // Czyści flagi błędów strumienia wejściowego
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruje resztę linii
        }
    }
    return 0;
}