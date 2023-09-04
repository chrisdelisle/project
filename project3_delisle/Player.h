//Player.h
//CSCI1300 Fall 2022
//Author: Chris Delisle
//Recitation: 104 - Christopher Ojukwu
//Project 3

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


class Player{

    public:
    //default constructor
    Player();
    //getters
    int getFullness() const;
    int getRooms() const;
    int getKeys() const;
    string getName() const;
    //setters
    void setFullness(int fullness);
    void setRooms(int rooms);
    void setKeys(int keys);
    void setName(string name);

    private:
    //variables
    int fullness_;

    int rooms_;
    int keys_;
    string name_;

};

#endif