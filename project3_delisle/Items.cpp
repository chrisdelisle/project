//Items.cpp
//CSCI1300 Fall 2022
//Author: Chris Delisle
//Recitation: 104 - Christopher Ojukwu
//Project 3


#include <iostream>
#include <iomanip>
#include <string>
#include "Items.h"

using namespace std;
    //default constructor
    Items::Items()
    {
        gold_ = 100;
        ingredients_ = 0;
        pans_ = 0;
        pots_ = 0;
        cauldrons_ = 0;
        clubs_ = 0;
        spears_ = 0;
        rapiers_ = 0;
        axes_ = 0;
        longswords_ = 0;
        armor_ = 0;
        rings_ = 0;
        necklaces_ = 0;
        bracelets_ = 0;
        circlets_ = 0;
        goblets_ = 0;
    }

    //getters
    int Items::getGold() const
    {
        return gold_;
    }
    int Items::getIngredients() const
    {
        return ingredients_;
    }
    int Items::getPans() const
    {
        return pans_;
    }
    int Items::getPots() const
    {
        return pots_;
    }
    int Items::getCauldrons() const
    {
        return cauldrons_;
    }
    int Items::getClubs() const
    {
        return clubs_;
    }
    int Items::getSpears() const
    {
        return spears_;
    }
    int Items::getRapiers() const
    {
        return rapiers_;
    }
    int Items::getAxes() const
    {
        return axes_;
    }
    int Items::getLongswords() const
    {
        return longswords_;
    }
    int Items::getArmor() const
    {
        return armor_;
    }

    int Items::getRings() const
    {
        return rings_;
    }
    int Items::getNecklaces() const
    {
        return necklaces_;
    }
    int Items::getBracelets() const
    {
        return bracelets_;
    }
    int Items::getCirclets() const
    {
        return circlets_;
    }
    int Items::getGoblets() const
    {
        return goblets_;
    }



    //setters

    //if statements used to ensure no negative values
    void Items::setGold(int gold) 
    {
        gold_ = gold;
        if(gold_ < 0)
        {
            gold_ = 0;
        }
    }
    void Items::setIngredients(int ingredients)
    {
        ingredients_ = ingredients;
        if( ingredients_ < 0)
        {
            ingredients_ = 0;
        }
    }
    void Items::setPans(int pans) 
    {
        pans_ = pans;
        if( pans_ < 0)
        {
            pans_ = 0;
        }
    }
    void Items::setPots(int pots) 
    {
         pots_ = pots;
         if( pots_ < 0)
        {
            pots_ = 0;
        }
    }
    void Items::setCauldrons(int cauldrons) 
    {
         cauldrons_ = cauldrons;
         if( cauldrons_ < 0)
        {
            cauldrons_ = 0;
        }
    }
    void Items::setClubs(int clubs) 
    {
         clubs_ = clubs;
         if(clubs_ < 0)
        {
            clubs_ = 0;
        }
    }
    void Items::setSpears(int spears) 
    {
         spears_ = spears;
         if(spears_ < 0)
        {
            spears_ = 0;
        }
    }
    void Items::setRapiers(int rapiers) 
    {
         rapiers_ = rapiers;
         if(rapiers_ < 0)
        {
            rapiers_ = 0;
        }
    }
    void Items::setAxes(int axes) 
    {
         axes_ = axes;
         if(axes_ < 0)
        {
            axes_ = 0;
        }
    }
    void Items::setLongswords(int longswords) 
    {
         longswords_ = longswords;
         if(longswords_ < 0)
        {
            longswords_ = 0;
        }
    }
    void Items::setArmor(int armor) 
    {
         armor_ = armor;
         if(armor_ < 0)
        {
            armor_ = 0;
        }
    }
    void Items::setRings(int rings)
    {
        rings_ = rings;
        if(rings_ < 0)
        {
            rings_ = 0;
        }
    }
    void Items::setNecklaces(int necklaces)
    {
        necklaces_ = necklaces;
        if(necklaces < 0)
        {
            necklaces = 0;
        }
    }
    void Items::setBracelets(int bracelets)
    {
        bracelets_ = bracelets;
        if(bracelets_ < 0)
        {
            bracelets_ = 0;
        }
    }
    void Items::setCirclets(int circlets)
    {
        circlets_ = circlets;
        if(circlets_ < 0)
        {
            circlets_ = 0;
        }
    }
    void Items::setGoblets(int goblets)
    {
        goblets_ = goblets;
    }


