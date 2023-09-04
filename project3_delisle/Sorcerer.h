//Sorcerer.h
//CSCI1300 Fall 2022
//Author: Chris Delisle
//Recitation: 104 - Christopher Ojukwu
//Project 3
#ifndef SORCERER_H
#define SORCERER_H
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


class Sorcerer{

    public:
    //default constructor
    Sorcerer();
    //getters
    int getAnger() const;

    int getHealth() const;
    //setters
    void setAnger(int anger);

    void increaseAnger();

    //bool isDead();

    void setHealth(int num);


    private:
    //setters
    int anger_;
    int health_;

};

#endif