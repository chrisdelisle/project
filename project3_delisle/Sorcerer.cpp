//Sorcerer.cpp
//CSCI1300 Fall 2022
//Author: Chris Delisle
//Recitation: 104 - Christopher Ojukwu
//Project 3

#include <iostream>
#include <string>
#include <iomanip>
#include "Sorcerer.h"

using namespace std;

//default constructor
Sorcerer::Sorcerer()
{
    anger_ = 0;
    health_ = 100;
}
//getters
int Sorcerer::getAnger() const
{
    return anger_;
}

int Sorcerer::getHealth() const
{
    return health_;
}
//setters
void Sorcerer::setAnger(int anger)
{
    anger_ = anger;
}

void Sorcerer::increaseAnger()
{
        anger_++;
}

// bool Sorcerer::isDead()
// {
//     return true;
// }

void Sorcerer::setHealth(int num)
{
    health_ = num;
}

