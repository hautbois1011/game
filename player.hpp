#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <cmath>
using namespace std;

#include "equipment.hpp"

class Player
{
private:
    string name_;

    unsigned int LV_;
    int HP_;
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
    Player(string name, unsigned int LV=1)
    {
        name_ = name;
        LV_ = LV;
        MAXHP_ = MAXHP(LV);
        HP_ = MAXHP_;
        MAXMP_ = MAXMP(LV);
        MP_ = MAXMP_;
        STR_ = STR(LV);
        EDR_ = EDR(LV);
        DEX_ = DEX(LV);
        VIT_ = VIT(LV);
        SPD_ = SPD(LV);
        FRT_ = 5;
        WEIGHT_ = 0;
        MAX_WEIGHT_ = MAX_WEIGHT(LV);

        weapons_ = vector<Weapon>();
    }

    ~Player()
    {
    }

    void ShowStatus()
    {
        cout << "[" << name_ << "]" << endl;
        cout << "HP: " << HP_ << "/" << MAXHP_ << endl;
        cout << "MP: " << MP_ << "/" << MAXMP_ << endl;
        cout << "STR: " << STR_ << endl;
        cout << "EDR: " << EDR_ << endl;
        cout << "DEX: " << DEX_ << endl;
        cout << "VIT: " << VIT_ << endl;
        cout << "SPD: " << SPD_ << endl;
        cout << "FRT: " << FRT_ << endl;
        cout << "WEIGHT: " << WEIGHT_ << "/" << MAX_WEIGHT_ << endl << endl;
    }

    void addHP(int HP)
    {
        HP_ += HP;
        cout << HP_ << endl;
        if(HP_ > (int)MAXHP_)
            HP_ = MAXHP_;
        if(HP_ < 0)
            HP_ = 0;
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

    unsigned int CalculateGivingDamage()
    {
        unsigned int damage = STR_/10;
        unsigned hit = 50 + DEX_/2 + SPD_/5 - 20*(MAXHP_ - HP_)/MAXHP_;

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

        damage -= damage*(MAXHP_ - HP_)/(MAXHP_ * 5);

        return damage;
    }

    unsigned int CalculateGivenDamage(unsigned int given)
    {
        unsigned int damage = given;
        if(VIT_/2 < given)
            damage -= VIT_/2;
        else
            damage = 0;

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

private:
    unsigned int MAXHP(unsigned int LV)
    {
        return 100 + ceil(10*sqrt(LV - 1));
    }
    unsigned int MAXMP(unsigned int LV)
    {
        return 100;
    }
    unsigned int STR(unsigned int LV)
    {
        return 10 + LV/10;
    }
    unsigned int EDR(unsigned int LV)
    {
        return 10 + LV/10;
    }
    unsigned int DEX(unsigned int LV)
    {
        return 10 + LV/5;
    }
    unsigned int VIT(unsigned int LV)
    {
        return 10 + LV/5;
    }
    unsigned int SPD(unsigned int LV)
    {
        return 10 + LV/5;
    }
    unsigned int MAX_WEIGHT(unsigned int LV)
    {
        return 20 + LV;
    }
};

#endif

