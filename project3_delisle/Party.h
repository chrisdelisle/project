//Party.h
//CSCI1300 Fall 2022
//Author: Chris Delisle
//Recitation: 104 - Christopher Ojukwu
//Project 3

#ifndef PARTY_H
#define PARTY_H
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


class Party{

    public:
    //default constructor
    Party();
    //getter
    int getPartyFullness(int index) const;
    string getPartyName(int index) const;



    //setter
    void setPartyFullness(int index, int num);
    void setPartyName(int index, string name);
    void makeParty();
    

    private:
    //variable
    string party_names[4];
    int party_fullness[4];
  

};

#endif