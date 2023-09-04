//Player.cpp
//CSCI1300 Fall 2022
//Author: Chris Delisle
//Recitation: 104 - Christopher Ojukwu
//Project 3

#include <iostream>
#include <string>
#include <iomanip>
#include "Player.h"

using namespace std;

//default constructor
    Player::Player()
    {
        name_ = "";
        fullness_ = 50;
        keys_ = 0;
        rooms_ = 0;

    }
//getters
    int Player::getFullness() const
    {
        return fullness_;
    }
    int Player::getRooms() const
    {
        return rooms_;
    }
    int Player::getKeys() const
    {
        return keys_;
    }

    string Player::getName() const
    {
        return name_;
    }

//setters
    void Player::setFullness(int fullness)
    {
         fullness_ = fullness;
         if(fullness_ < 0)
         {
            fullness_ = 0;
         }
    }
    void Player::setRooms(int rooms)
    {
         rooms_ = rooms;
    }
    void Player::setKeys(int keys)
    {
         keys_ = keys;
    }

    void Player::setName(string name)
    {
        name_ = name;
    }