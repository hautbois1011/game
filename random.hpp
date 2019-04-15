#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
using namespace std;

unsigned int Rand(unsigned int max)
{
    random_device rnd;
    mt19937 mt(rnd());
    uniform_int_distribution<> uf(1, max);
    return uf(mt);
}

#endif

