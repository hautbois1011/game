#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <algorithm>
using namespace std;

#include "equipment.hpp"

class Player
{
private:
    unsigned int LV_;
    unsigned int HP_;
    unsigned int MAXHP_;
    unsigned int MP_;
    unsigned int MAXMP_;

    unsigned int STR_; // Strength
    unsigned int EDR_; // Endurance
    unsigned int DEX_; // Dexterity
    unsigned int VIT_; // Vitality
    unsigned int SPD_; // Speed
    unsigned int FRT_; // Fortune

    unsigned int WEIGHT_;
    unsigned int MAX_WEIGHT_;

    vector<Weapon> weapons_;

public:
    Player()
    {
        LV_ = 1;
        HP_ = 20;
        MAXHP_ = 100;
        MP_ = 20;
        MAXMP_ = 100;
        STR_ = 10;
        EDR_ = 10;
        DEX_ = 10;
        VIT_ = 10;
        SPD_ = 10;
        FRT_ = 5;
        WEIGHT_ = 0;
        MAX_WEIGHT_ = 20;

        weapons_ = vector<Weapon>();
    }

    ~Player()
    {
    }

    void EquipWeapon(unsigned int id)
    {
        if(WEIGHT_ + WEAPON_TABLE[id][3] > MAX_WEIGHT_)
        {
            cout << "You can't equip that weapon. Please throw away some weapons." << endl;
            return;
        }

        WEIGHT_ += WEAPON_TABLE[id][3];
        cout << "Weight: " << WEIGHT_ << "/" << MAX_WEIGHT_ << endl;
        weapons_.push_back(Weapon(id));
    }

    unsigned int CalculatePlayerGivingDamage()
    {
        unsigned int damage = STR_/10;
        unsigned hit = 50 + DEX_/2 + SPD_/5;

        for(auto it = weapons_.begin(); it != weapons_.end(); it++)
        {
            damage += it->CalculateDamage();
            hit += it->getHitCorrection();
        }

        cout << "Base damage: " << damage << endl;
        cout << "Hit Accuracy: " << hit << endl;

        unsigned int rnd = Rand(100);
        if(rnd > hit)
        {
            cout << "Miss!" << endl;
            damage *= 3;
            damage /= 5;
        }
        else if(rnd > hit/2)
        {
            damage *= 1;
        }
        else
        {
            if(Rand(100) < FRT_)
            {
                cout << "Blow of satisfaction!" << endl;
                damage *= 2;
            }
            else
            {
                cout << "Critical!" << endl;
                damage *= 5;
                damage /= 3;
            }
        }

        return damage;
    }

    unsigned int CalculatePlayerGivenDamage(unsigned int given)
    {
        unsigned int damage = given;
        damage -= VIT_/2;

        damage *= (100 - EDR_/5);
        damage /= 100;

        cout << "Base damage: " << damage << endl;

        unsigned int avoidance = DEX_ + SPD_/2;

        cout << "Avoidance acurracy: " << avoidance << endl;

        unsigned int rnd = Rand(100);
        if(rnd < avoidance)
        {
            if(Rand(100) < FRT_)
            {
                cout << "Avoided Brillantly!" << endl;
                damage = 0;
            }
            else
            {
                cout << "Avoided!" << endl;
                damage /= 7;
            }
        }
        else if(rnd < avoidance + 10)
        {
            cout << "Avoided a little." << endl;
            damage /= 3;
        }
        else
        {
            cout << "Direct hit!" << endl;
            if(Rand(100) < FRT_/2)
            {
                cout << "But a miracle happened!" << endl;
                damage = 0;
            }
            else
            {
                damage /= 1;
            }
        }

        return damage;
    }
};

#endif

