
//Items.h
//CSCI1300 Fall 2022
//Author: Chris Delisle
//Recitation: 104 - Christopher Ojukwu
//Project 3

#ifndef ITEMS_H
#define ITEMS_H
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Items{

    public:
    //default constuctor
    Items();
    //getters
    int getGold() const;
    int getIngredients() const;
    int getPans() const;
    int getPots() const;
    int getCauldrons() const;
    int getClubs() const;
    int getSpears() const;
    int getRapiers() const;
    int getAxes() const;
    int getLongswords() const;
    int getArmor() const;
    int getRings() const;
    int getNecklaces() const;
    int getBracelets() const;
    int getCirclets() const;
    int getGoblets() const;
    //setters
    void setGold(int gold);
    void setIngredients(int ingredients);
    void setPans(int pans);
    void setPots(int pots);
    void setCauldrons(int cauldrons);
    void setClubs(int clubs);
    void setSpears(int spears);
    void setRapiers(int rapiers);
    void setAxes(int axes);
    void setLongswords(int longswords);
    void setArmor(int armor);
    void setRings(int rings);
    void setNecklaces(int necklaces);
    void setBracelets(int bracelets);
    void setCirclets(int circlets);
    void setGoblets(int goblets);

   

    private:
    //varaibles
    int gold_;
    int ingredients_;
    int pans_;
    int pots_;
    int cauldrons_;
    int clubs_;
    int spears_;
    int rapiers_;
    int axes_;
    int longswords_;
    int armor_;
    int goblets_;
    int rings_;
    int necklaces_;
    int circlets_;
    int bracelets_;


};

#endif