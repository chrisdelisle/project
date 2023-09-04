//driver.cpp
//CSCI1300 Fall 2022
//Author: Chris Delisle
//Recitation: 104 - Christopher Ojukwu
//Project 3

#include <iostream>
#include <string>
#include "Items.h"
#include "Party.h"
#include "Player.h"
#include "Sorcerer.h"

using namespace std;

int main()
{
    //tests Player default constructor creates correct values, and getters work

    Player p1;
    assert(p1.getFullness() == 50);
    assert(p1.getKeys() == 0);
    assert(p1.getRooms() == 0);
    assert(p1.getName() == "");
    //uses setters
    p1.setFullness(10);
    p1.setKeys(10);
    p1.setRooms(5);
    p1.setName("chris");
    //checks setters work
    assert(p1.getFullness() == 10);
    assert(p1.getKeys() == 10);
    assert(p1.getRooms() == 5);
    assert(p1.getName() == "chris");

    p1.setFullness(-5);
    assert(p1.getFullness() == 0); //tests negative fullness become 0

    //tests Items dafualt constructor creates correct values, and getters work
    Items i1;
    assert(i1.getArmor() == 0);
    assert(i1.getAxes() == 0);
    assert(i1.getCauldrons() == 0);
    assert(i1.getClubs() == 0);
    assert(i1.getGold() == 100);
    assert(i1.getIngredients() == 0);
    assert(i1.getLongswords() == 0);
    assert(i1.getPans() == 0);
    assert(i1.getPots() == 0);
    assert(i1.getRapiers() == 0);
    assert(i1.getSpears()== 0);
    assert(i1.getRings() == 0);
    assert(i1.getBracelets() == 0);
    assert(i1.getNecklaces() == 0);
    assert(i1.getCirclets() == 0);
    assert(i1.getGoblets() == 0);

    //uses setters
    i1.setArmor(5);
    i1.setAxes(5);
    i1.setCauldrons(5);
    i1.setClubs(5);
    i1.setGold(5);
    i1.setIngredients(5);
    i1.setLongswords(5);
    i1.setPans(5);
    i1.setPots(5);
    i1.setRapiers(5);
    i1.setSpears(5);
    i1.setRings(5);
    i1.setNecklaces(5);
    i1.setBracelets(5);
    i1.setCirclets(5);
    i1.setGoblets(5);
    //tests setters worked properly
    assert(i1.getArmor() == 5);
    assert(i1.getAxes() == 5);
    assert(i1.getCauldrons() == 5);
    assert(i1.getClubs() == 5);
    assert(i1.getGold() == 5);
    assert(i1.getIngredients() == 5);
    assert(i1.getLongswords() == 5);
    assert(i1.getPans() == 5);
    assert(i1.getPots() == 5);
    assert(i1.getRapiers() == 5);
    assert(i1.getSpears()== 5);
    assert(i1.getRings() == 5);
    assert(i1.getBracelets() == 5);
    assert(i1.getNecklaces() == 5);
    assert(i1.getCirclets() == 5);
    assert(i1.getGoblets() == 5);


    //tests Party dafault constructor creates correct values
    Party party1; 
    assert(party1.getPartyFullness(0) == 50); //test getter and that dafault contructor makes proper fullness value
    //uses setter
    party1.setPartyFullness(0, -5); //test negative fullness resets to 0;
    assert(party1.getPartyFullness(0) == 0); //tests setter worked properly

    //tests Sorcerer default constructor creates right values
    Sorcerer s1;
    assert(s1.getAnger() == 0); //test getter and that default constructor makes proper anger value
    assert(s1.getHealth() == 100);

    //uses setter
    s1.setAnger(80); 
    s1.setHealth(15);
    assert(s1.getAnger() == 80); //tests setter worked properly
    assert(s1.getHealth() == 15);
    s1.increaseAnger();
    assert(s1.getAnger() == 81); //tests increaseAnger() increases anger by 1

    

    return 0;
}