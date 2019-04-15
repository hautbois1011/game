#include <iostream>
using namespace std;

#include "equipment.hpp"
#include "player.hpp"

int main(void)
{
    Player player = Player();
    while(true)
    {
        cout << "What to do?(0:Equip some weapon 1:Battle)" << endl;
        int d;
        cin >> d;
        if(d == 0)
        {
            cout << "Choose the weapon(0:Dagger 1:Ninja Sword)" << endl;
            int w;
            cin >> w;

            if(w < 0 || w > 1)
            {
                cout << "Error: Invalid Equip.id" << endl;
                continue;
            }

            player.EquipWeapon(w);
        }
        else if(d == 1)
        {
            unsigned int damage = player.CalculatePlayerGivingDamage();
            cout << "Giving Damage: " << damage << endl;

            unsigned int given;
            cout << "Input given damage: ";
            cin >> given;

            damage = player.CalculatePlayerGivenDamage(given);
            cout << "Given Damage: " << damage << endl;
        }

        cout << "Exit? (Y/N)" << endl;
        char s;
        cin >> s;
        if(s == 'y' || s == 'Y')
            break;
    }
    return 0;
}

