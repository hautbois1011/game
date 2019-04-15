#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP

#include <iostream>
using namespace std;

#include "random.hpp"

short WEAPON_TABLE[][5] = {
    {2, 15, 17, 6, 6},
    {4, 12, 22, 7, 4}
};

class Weapon
{
private:
    unsigned int id_;

    short dice_num_;
    short dice_faces_;
    short base_damage_;
    short hit_correction_;

    short weight_;

public:
    Weapon(unsigned int id)
    {
        id_ = id;
        SetStatusById(id_);
    }

    ~Weapon()
    {
    }

    int CalculateDamage()
    {
        int sum = base_damage_;

        for(int i = 0; i < dice_num_; i++)
            sum += Rand(dice_faces_);

        return sum;
    }

    short getHitCorrection()
    {
        return hit_correction_;
    }

private:
    void SetStatusById(unsigned int id)
    {
        dice_num_       = WEAPON_TABLE[id][0];
        dice_faces_     = WEAPON_TABLE[id][1];
        base_damage_    = WEAPON_TABLE[id][2];
        weight_         = WEAPON_TABLE[id][3];
        hit_correction_ = WEAPON_TABLE[id][4];
    }
};

#endif

