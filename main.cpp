#include <iostream>
using namespace std;

#include "equipment.hpp"
#include "player.hpp"

int main(void)
{
    Player player = Player("Player", 10);
    player.ShowStatus();

    Player enemy = Player("Enemy");
    enemy.EquipWeapon(0);
    enemy.ShowStatus();
    
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
            cout << "[Your turn]" << endl;
            unsigned int damage = player.CalculateGivingDamage();
            cout << "Your Giving Damage: " << damage << endl;
            unsigned int enemiesgiven = enemy.CalculateGivenDamage(damage);
            cout << "Enemie's given damage: " << enemiesgiven << endl << endl;
            enemy.addHP(-enemiesgiven);
            enemy.ShowStatus();

            cout << "[Enemie's turn]" << endl;
            unsigned int given = enemy.CalculateGivingDamage();
            cout << "Enemie's giving damage: " << given << endl;
            unsigned int playersgiven = player.CalculateGivenDamage(given);
            cout << "Your Given Damage: " << playersgiven << endl << endl;
            player.addHP(-playersgiven);
            player.ShowStatus();
        }

        cout << "Exit? (Y/N)" << endl;
        char s;
        cin >> s;
        if(s == 'y' || s == 'Y')
            break;
    }
    return 0;
}

