//Party.cpp
//CSCI1300 Fall 2022
//Author: Chris Delisle
//Recitation: 104 - Christopher Ojukwu
//Project 3

#include <iostream>
#include <string>
#include "Party.h"

using namespace std;
//default constructor
Party::Party()
{
    for(int i = 0; i < 4; i ++)
    {
        party_fullness[i] = 50;
    }
}
//getters
int Party::getPartyFullness(int index) const
{
    return party_fullness[index];
}

string Party::getPartyName(int index) const
{
    return party_names[index];
}
//setters

void Party::setPartyFullness(int index, int num) 
{
    party_fullness[index] = num;
    if(party_fullness[index] < 0)
    {
        party_fullness[index] = 0;
    }
}   

void Party::setPartyName(int index, string name)
{
    party_names[index] = name;
}

//makes names
void Party::makeParty()
{

    for(int i = 0; i < 4; i ++)
    {
        cout << "Enter the " << (i + 1) << " player's name: " << endl;
        string name;
        cin >> name;
        party_names[i] = name;
        
    }
}