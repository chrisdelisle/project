//dungeon.cpp
//CSCI1300 Fall 2022
//Author: Chris Delisle
//Recitation: 104 - Christopher Ojukwu
//Project 3

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "Items.h"
#include "Party.h"
#include "Player.h"
#include "Sorcerer.h"
#include "Map.h"
//#include "Map.h"
using namespace std;

//split function splits line into array
int split(string input_string, char separator, string arr[], int arr_size){

    string temp_string = "";
    int string_start = 0;
    int count = 0;
    int arr_num = 0;


    if(input_string == "")
    {   
         return 0;
    }
    
    int size = input_string.length();
    
    for(int i = 0; i < size; i++)
    {
        if(input_string[i] == separator)
        {
            temp_string = input_string.substr(string_start, count);
            if(arr_num < arr_size)
            {
            arr[arr_num] = temp_string;
            string_start = i+1;
            count = 0;
            arr_num++;
            }
        }
        if(input_string[i] != separator)
        {
            count++;
        }
    }
    
    arr[arr_num] = input_string.substr(string_start, count);
    arr_num ++;
    if(arr_num > arr_size)
    {
        return -1;
    }
    
    return arr_num;
  }

//print status prints current status of player, sorcerer, items, party and the map after each turn
string printStatus(Player &player, Sorcerer &sorcerer, Items &items, Party &party, Map &map)
{
    //status menu
    //uses getters and setters as variables in classes are private
    cout << "" << endl;
    cout << "" << endl;
    cout << "+-------------+" << endl;
    cout << "| STATUS      |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Rooms Cleared: " << player.getRooms() <<" | Keys: " << player.getKeys() << " | Anger Level: " << sorcerer.getAnger() << endl;
    cout << "+-------------+" << endl;
    cout << "| INVENTORY   |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Gold        | " << items.getGold() << endl;
    cout << "| Ingredients | " << items.getIngredients() << " kg" << endl;
    cout << "| Cookware    | P: " << items.getPots() << " | F: " << items.getPans() << " | C: " << items.getCauldrons() << endl;
    cout << "| Weapons     | C: " << items.getClubs() << " | S: " << items.getSpears() << " | R: " << items.getRapiers() << " | B: " << items.getAxes() << "  | L: " << items.getLongswords() << endl;
    cout << "| Armor       | " << items.getArmor() << endl;
    cout << "| Treasures   | R: " <<  items.getRings() << " | N: " <<  items.getNecklaces() << " | B: " << items.getBracelets() << " | C: " << items.getCirclets() << " | G: "<< items.getGoblets() << endl;
    cout << "+-------------+" << endl;
    cout << "| PARTY       |" << endl;
    cout << "+-------------+" << endl;
    cout << "| " << player.getName() << " | Fullness: " << player.getFullness() << endl;
    cout << "| " << party.getPartyName(0) << " | Fullness: " << party.getPartyFullness(0) << endl;
    cout << "| " << party.getPartyName(1) << " | Fullness: " << party.getPartyFullness(1) << endl;
    cout << "| " << party.getPartyName(2) << " | Fullness: " << party.getPartyFullness(2) << endl;
    cout << "| " << party.getPartyName(3) << " | Fullness: " << party.getPartyFullness(3) << endl;
    cout << "+-------------+" << endl;
    cout << "" << endl;

    map.displayMap(); //displays updated map

    //gives user option
    cout << "Select one:" << endl;
    cout << "1. Move" << endl;
    cout << "2. Investigate" << endl;
    cout << "3. Pick a Fight" << endl;
    cout << "4. Cook and Eat" << endl;
    cout << "5. Give up" << endl; 
    string option; //uses string as it is more versitiles for this case
    cin >> option;
    while(option != "1" && option != "2" && option != "3" && option != "4" && option != "5") //runs until valid option is input
    {
        cout << "Enter a number 1 - 5. Try again:" << endl;
        cin >> option;
    }

  return option; //returns a string of the users next move


}

//see merchant function is only used at the start. Gives players the opportunity to buy things before beggining their journey
void seeMerchant(Player &player, Items &items, Party &party)
{
  cout << "Thank you for visiting. Let's buy something! Here is your current inventory:" << endl;
  bool run = true;
  while(run) //runs until false (user decides to exit)
  {
    //inventory menu
    cout << "+-------------+" << endl;
    cout << "| INVENTORY   |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Gold        | " << items.getGold() << endl;
    cout << "| Ingredients | " << items.getIngredients() << " kg" << endl;
    cout << "| Cookware    | P: " << items.getPots() << " | F: " << items.getPans() << " | C: " << items.getCauldrons() << endl;
    cout << "| Weapons     | C: " << items.getClubs() << " | S: " << items.getSpears() << " | R: " << items.getRapiers() << " | B: " << items.getAxes() << "  | L: " << items.getLongswords() << endl;
    cout << "| Armor       | " << items.getArmor() << endl;
    cout << "| Treasures   | R: " <<  items.getRings() << " | N: " <<  items.getNecklaces() << " | B: " << items.getBracelets() << " | C: "<< items.getCirclets() << " | G: "<< items.getGoblets() << endl;
    cout << "Choose one of the following:" << endl;
    cout << "1. Ingredients: To make food, you have to cook raw ingredients. " << endl;
    cout << "2. Cookware: You will need something to cook those ingredients." << endl;
    cout << "3. Weapons: It's dangerous to go alone, take this!" << endl; 
    cout << "4. Armor: If you want to survive monster attacks, you will need some armor." << endl;
    cout << "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl;
    cout << "6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;
    string select;
    cin >> select;
    while(select != "1" && select != "2" && select != "3" && select != "4" && select != "5" && select != "6") //runs until valid input
    {
        cout << "Enter a valid option (1-6)" << endl;
        cin >> select;
    }
    //user wants to buy cookware
    if(select == "2")
    {
        cout << "Which cookware would you like? Each has a different probability of breaking when used (marked XX%)." << endl;
        cout << "Choose 1:" << endl;
        cout << "1. (25%) Ceramic Pot [2 Gold]" << endl;
        cout << "2. (10%) Frying Pan [10 Gold]" << endl;
        cout << "3. ( 2%) Cauldron [20 Gold]" << endl;
        cout << "4. Cancel" << endl;  
        int option;
        cin >> option;
        while(option != 1 && option != 2 && option != 3 && option != 4) //runs until valid option is input
        {
            cout << "Enter a valid option (1-4)" << endl;
            cin >> option;
        } 
        if(option == 4) //user cancels purchase
        {
            cout << "Canceled." << endl;
        }
        else
        {
            string choice;
            int cost;
            //if-else's sets choice and cost to corresponding value of desired cookware
            if(option == 1) 
            {
                choice = "Ceramic Pot(s)";
                cost = 2;
            }
            else if(option == 2)
            {
                choice = "Frying Pan(s)";
                cost = 10;
            }
            else
            {
                choice = "Cauldron(s)";
                cost = 20;
            }
            cout << "How many would you like? (Enter a positive integer, or 0 to cancel" << endl;
            int count;
            cin >> count;
            while((count * cost > items.getGold()) || count < 0) //ensures player has enough to buy, runs until valid
            {
                cout << "You do not have enough for this purchase, or the input was invalid. Try again. How many do you want?" << endl;
                cin >> count;
            }
            if(count == 0) //cancel option
            {
                cout << "Canceled." << endl;
            }
            else
            {
                cout << "Do you want to buy " << count << " " << choice << " for " << cost * count << " Gold? (y/n)" << endl; //confirms user wants to buy
                string y;
                cin >> y;
                while(y != "y" && y != "n") //runs until valid
                {
                    cout << "Enter y/n" << endl;
                    cin >> y;
                }

                if(y == "y") //if confirmed
                {
                    //each is for which cookware is bought
                    if(option == 1)
                    {
                        items.setPots(items.getPots() + count);
                        cout << "Successfully purchased. What else can I get you?" << endl;
                    }
                    else if(option == 2)
                    {
                        items.setPans(items.getPans() + count);
                        cout << "Successfully purchased. What else can I get you?" << endl;
                    }
                    else
                    {
                        items.setCauldrons(items.getCauldrons() + count);
                        cout << "Successfully purchased. What else can I get you?" << endl;
                    }
                    items.setGold(items.getGold() - cost * count);
                }
                else
                {
                    cout << "You canceled." << endl; //if "n"
                }
            }

        }

    }

    //if user wants to buy ingredients
    if(select == "1")
    {
        cout << "How many kg of ingredients do you need [1 Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)" << endl;
        int num;
        cin >> num;
        while((num < 0 || num % 5 != 0) || items.getGold() < num) //runs until valid input
        {
            cout << "You do not have enough for this purchase, or you input was invalid. Enter a positive number that is a multiple of 5, or 0 to cancel:" << endl;
            cin >> num;
        }

        cout << "You want to buy " << num << " kg of ingredients for " << num << " gold? (y/n):" << endl; //confirms purchase
        string n;
        cin >> n;
        while(n != "y" && n != "y") //runs until valid input
        {
            cout << "Enter y/n, try again:" << endl;
            cin >> n;
        }
        if(n == "n") //if cancled
        {
            cout << "Canceled." << endl;
        }
        else //if yes
        {   //getters and setters for correct values
            items.setGold(items.getGold() - num);
            items.setIngredients(items.getIngredients() + num);
            cout << "Thank you for purchasing. What else can I get for you?" << endl;
        }


    }

    //if user wants to buy weaposn
    if(select == "3")
    {
        cout << "I have a plentiful collection of weapons to choose from, what would you like? Note that some of them provide you a special bonus in combat, marked by a (+X)." << endl;
        cout << "Choose one of the following:" << endl;
        cout << "1. Stone Club [2 Gold]" << endl;
        cout << "2. Iron Spear [2 Gold]" << endl;
        cout << "3. (+1) Mythril Rapier [5 Gold]" << endl;
        cout << "4. (+2) Flaming Battle-Axe [15 Gold]" << endl;
        cout << "5. (+3) Vorpal Longsword [50 Gold]" << endl;
        cout << "6. Cancel" << endl;
        int weapon;
        cin >> weapon;
        while(weapon != 1 && weapon != 2 && weapon != 3 && weapon != 4 && weapon != 5 && weapon != 6) //runs until valid weapon is input
        {
            cout << "Enter a number 1 - 6. Try again: " << endl;
            cin >> weapon;
        }
        cout << "How many would you like? Enter a postive integer, or 0 to cancel." << endl;
        int weapon_count;
        cin >> weapon_count;
        int weapon_cost = 0;
        string weapon_name;
        
                //makes weapon name and cost based on desired choice
                if(weapon == 1)
                {
                    weapon_cost = 2 * weapon_count;
                    weapon_name = "Stone Club";
                }
                else if(weapon == 2)
                {   
                    weapon_cost = 2 * weapon_count;
                    weapon_name = "Iron Spear";
                }
                else if(weapon == 3)
                {   
                    weapon_cost = 5 * weapon_count;
                    weapon_name = "Mythril Rapier";
                }
                else if(weapon == 4)
                {
                    weapon_cost = 15 * weapon_count;
                    weapon_name = "Flaming Battle-Axe";
                }
                else if(weapon == 5)
                {      
                    weapon_cost = 50 * weapon_count;
                    weapon_name = "Vorpal Longsword";
                }
                
        while(weapon_count < 0  || weapon_cost > items.getGold()) //ensures player has enough gold for purchase
        {
            //runs until player has enough for desired purchase
            cout << "You do not have enough, or you did not enter a positive integer. Try again" << endl;
            cin >> weapon_count;
            if(weapon_count == 0)
            {
                break;
            }
            else
            {
                //same as if-else above
                if(weapon == 1)
                {
                    weapon_cost = 2 * weapon_count;
                    weapon_name = "Stone Club";
                }
                else if(weapon == 2)
                {   
                    weapon_cost = 2 * weapon_count;
                    weapon_name = "Iron Spear";
                }
                else if(weapon == 3)
                {   
                    weapon_cost = 5 * weapon_count;
                    weapon_name = "Mythril Rapier";
                }
                else if(weapon == 4)
                {
                    weapon_cost = 15 * weapon_count;
                    weapon_name = "Flaming Battle-Axe";
                }
                else if(weapon == 5)
                {      
                    weapon_cost = 50 * weapon_count;
                    weapon_name = "Vorpal Longsword";
                }


            }
        }

        if(weapon_count == 0) //if canceled
        {
            cout << "Canceled." << endl;
        }
        else
        {
            //same if-else loop, but now that purhcase is confirmed to work
            if(weapon == 1)
            {
                weapon_cost = 2 * weapon_count;
                weapon_name = "Stone Club";
            }
            else if(weapon == 2)
            {   
                weapon_cost = 2 * weapon_count;
                weapon_name = "Iron Spear";
            }
            else if(weapon == 3)
            {
                weapon_cost = 5 * weapon_count;
                weapon_name = "Mythril Rapier";
            }
            else if(weapon == 4)
            {
                weapon_cost = 15 * weapon_count;
                weapon_name = "Flaming Battle-Axe";
            }
            else if(weapon == 5)
            {
                weapon_cost = 50 * weapon_count;
                weapon_name = "Vorpal Longsword";
            }
        }
      cout << "Do you want to purchase " << weapon_count << " " << weapon_name << "(s) for " << weapon_cost << " gold? (y/n):" << endl; //confirms purhcase
      string yn;
      cin >> yn;
      while(yn != "y" && yn!= "n") //runs until valid input
      {
        cout << "Enter y/n. Try again:" << endl;
        cin >> yn;
      }
      if(yn == "n")
      {
        cout << "Canceled purchase." << endl;
      }
      else
      {
        cout << "Purchase successful." << endl;
            //changes items based on purchase chocie. Uses setters and getters to update properly
            if(weapon == 1)
            {
                items.setClubs(items.getClubs() + weapon_count); 
                items.setGold(items.getGold() - weapon_cost);
            }
            else if(weapon == 2)
            {
                items.setSpears(items.getSpears() + weapon_count);
                items.setGold(items.getGold() - weapon_cost);
            }
            else if(weapon == 3)
            {
                items.setRapiers(items.getRapiers() + weapon_count);
                items.setGold(items.getGold() - weapon_cost);
            }
            else if(weapon == 4)
            {
                items.setAxes(items.getAxes() + weapon_count);
                items.setGold(items.getGold() - weapon_cost);
            }
            else
            {
                items.setLongswords(items.getLongswords() + weapon_count);
                items.setGold(items.getGold() - weapon_cost);
            }
      }

    }

    if(select == "4")
    {
        cout << "How many suits of armor can I get you (5 gold each)? Enter a positive integer, or 0 to cancel." << endl;
        int armor;
        cin >> armor;
        int armor_cost = 5 * armor;
        while(armor < 0 || armor_cost > items.getGold())
        {
            cout << "You can not purhcase this many, or you did not enter a positve number. Try again:" << endl;
            cin >> armor;
            armor_cost = armor * 5;
        }
        if(armor != 0)
        {
            cout << "You want to buy " << armor << " suit(s) of armor for " << armor_cost << " Gold? (y/n)" << endl;
            string confirm;
            cin >> confirm;
            while(confirm != "y" && confirm != "n")
            {
                cout << "Enter y/n. Try again:" << endl;
                cin >> confirm;
            }
            if(confirm == "n")
            {
                cout << "Canceled purchase." << endl;
            }
            else
            {
                cout << "Thank you for the purchase. What else can I get you?" << endl;
                items.setArmor(items.getArmor() + armor);
                items.setGold(items.getGold() - armor_cost);
            }
        }
        else
        {
            cout << "You canceled." << endl;
        }
    }
  
    //if user wants to sell treasures
    if(select == "5")
    {
        //options
        cout <<"Which treasure would you like to sell?" << endl; 
        cout <<"1). Ring (10 gold)" << endl;
        cout <<"2). Necklace (20 gold)" << endl;
        cout <<"3). Bracelet (30 gold)" << endl;
        cout <<"4). Circlet (40 gold)" << endl;
        cout <<"5). Goblet (50 gold)" << endl;
        string sell;
        cin >> sell;
        bool can_buy = true; 
        int number_to_sell;
        string confirm;
        while(can_buy) //runs until can_buy becomes false when purhcase is made
        {
            if(sell == "1" && items.getRings() >= 1)
            {
                cout << "How many do you want to sell?" << endl;
                cin >> number_to_sell;
                while(number_to_sell < items.getRings()) //checks user has enough of desired, runs until valid
                {
                    cout <<"You do not have that many to sell. Try again:" << endl;
                    cin >> number_to_sell;
                }
                can_buy = false;
                cout << "Sell " << number_to_sell << " rings? (y/n)" << endl; //confirms purchase
                cin >> confirm;
                while(confirm != "y" && confirm != "n") //runns until valid input
                {
                    cout << "Enter y/n. Try again:" << endl;
                    cin >> confirm;
                }
                if(confirm == "y") //if purchase is wanted
                {
                    //setters and getters to update as purchase was made
                    cout << "Thank you for your purchase." << endl;
                    items.setRings(items.getRings() - number_to_sell);
                    items.setGold(items.getGold() + 10 * number_to_sell);
                }
                else{
                    cout <<"Goodbye." << endl;
                }

                
            }

            //same process as with sell = 1 (rings) above
            else if(sell == "2" && items.getNecklaces() >= 1)
            {
                cout << "How many do you want to sell?" << endl;
                cin >> number_to_sell;
                while(number_to_sell < items.getNecklaces())
                {
                    cout <<"You do not have that many to sell. Try again:" << endl;
                    cin >> number_to_sell;
                }
                can_buy = false;
                cout << "Sell " << number_to_sell << " necklaces? (y/n)" << endl;
                cin >> confirm;
                while(confirm != "y" && confirm != "n")
                {
                    cout << "Enter y/n. Try again:" << endl;
                    cin >> confirm;
                }
                if(confirm == "y")
                {
                    cout << "Thank you for your purchase." << endl;
                    items.setNecklaces(items.getNecklaces() - number_to_sell);
                    items.setGold(items.getGold() + 20 * number_to_sell);
                }
                else{
                    cout <<"Goodbye." << endl;
                }
            }
            //same process as with sell = 1 (rings) above
            else if(sell == "3" && items.getBracelets() >= 1)
            {
                cout << "How many do you want to sell?" << endl;
                cin >> number_to_sell;
                while(number_to_sell < items.getBracelets())
                {
                    cout <<"You do not have that many to sell. Try again:" << endl;
                    cin >> number_to_sell;
                }
                can_buy = false;
                cout << "Sell " << number_to_sell << " bracelets? (y/n)" << endl;
                cin >> confirm;
                while(confirm != "y" && confirm != "n")
                {
                    cout << "Enter y/n. Try again:" << endl;
                    cin >> confirm;
                }
                if(confirm == "y")
                {
                    cout << "Thank you for your purchase." << endl;
                    items.setBracelets(items.getBracelets() - number_to_sell);
                    items.setGold(items.getGold() + 30 * number_to_sell);
                }
                else{
                    cout <<"Goodbye." << endl;
                }
            }
            //same process as with sell = 1 (rings) above
            else if(sell == "4" && items.getCirclets() >= 1)
            {
                cout << "How many do you want to sell?" << endl;
                cin >> number_to_sell;
                while(number_to_sell < items.getCirclets())
                {
                    cout <<"You do not have that many to sell. Try again:" << endl;
                    cin >> number_to_sell;
                }
                can_buy = false;
                cout << "Sell " << number_to_sell << " circlets? (y/n)" << endl;
                cin >> confirm;
                while(confirm != "y" && confirm != "n")
                {
                    cout << "Enter y/n. Try again:" << endl;
                    cin >> confirm;
                }
                if(confirm == "y")
                {
                    cout << "Thank you for your purchase." << endl;
                    items.setRings(items.getCirclets() - number_to_sell);
                    items.setGold(items.getGold() + 40 * number_to_sell);
                }
                else{
                    cout <<"Goodbye." << endl;
                }
            }
            //same process as with sell = 1 (rings) above
            else if(sell == "5" && items.getGoblets() >= 1)
            {
                cout << "How many do you want to sell?" << endl;
                cin >> number_to_sell;
                while(number_to_sell < items.getGoblets())
                {
                    cout <<"You do not have that many to sell. Try again:" << endl;
                    cin >> number_to_sell;
                }
                can_buy = false;
                cout << "Sell " << number_to_sell << " goblets? (y/n)" << endl;
                cin >> confirm;
                while(confirm != "y" && confirm != "n")
                {
                    cout << "Enter y/n. Try again:" << endl;
                    cin >> confirm;
                }
                if(confirm == "y")
                {
                    cout << "Thank you for your purchase." << endl;
                    items.setRings(items.getGoblets() - number_to_sell);
                    items.setGold(items.getGold() + 50 * number_to_sell);
                }
                else{
                    cout <<"Goodbye." << endl;
                }
            }
            else
            {
                cout << "Did not enter 1 - 5, or you do not have enough of that treasure to sell." << endl; //user did not enter valid option
                cin >> number_to_sell;
            }
        }

    }
    
    //if user wants to exit
    if(select == "6")
    {
        cout << "Are you sure you are done? You will not be able to buy anything else from me! (y/n)" << endl; //confirms
        string sure;
        cin >> sure;
        while(sure != "y" && sure != "n") //runs until valid input
        {
            cout << "Enter y/n. Try again:" << endl; 
            cin >> sure;
        }
        if(sure == "y")
        {
            cout << "Good luck and goodbye!" << endl; //quites
            run = false; //makes loop of menu stop
        }
        else
        {
            cout << "Glad you changed your mind!" << endl; //menu continues to loop
        }

    }
  
  }
}

//when player interacts with NPC for purchases
//functions exactly like seeMerchant, except for room cost factor, as commented in the function
void npcMenu(Player &player, Items &items, Party &party)
{
    //factor used to calculate cost change due to room count
    double factor = 1.0; 
    int rooms = player.getRooms();
    
        //creates factor based on room count
        if(rooms == 1)
        {
            factor = 1.25;
        }
        else if(rooms == 2)
        {
            factor = 1.5;
        }
        else if(rooms == 3)
        {
            factor = 1.75;
        }
        else if(rooms == 4)
        {
            factor = 2;
        }
        else if(rooms == 5)
        {
            factor = 2.25;
        }


    
   bool run = true;
  while(run) //runs until false/exit
  {
    //shows inventory
    cout << "+-------------+" << endl;
    cout << "| INVENTORY   |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Gold        | " << items.getGold() << endl;
    cout << "| Ingredients | " << items.getIngredients() << " kg" << endl;
    cout << "| Cookware    | P: " << items.getPots() << " | F: " << items.getPans() << " | C: " << items.getCauldrons() << endl;
    cout << "| Weapons     | C: " << items.getClubs() << " | S: " << items.getSpears() << " | R: " << items.getRapiers() << " | B: " << items.getAxes() << "  | L: " << items.getLongswords() << endl;
    cout << "| Armor       | " << items.getArmor() << endl;
    cout << "| Treasures   | R: " <<  items.getRings() << " | N: " <<  items.getNecklaces() << " | B: " << items.getBracelets() << " | C: "<< items.getCirclets() << " | G: "<< items.getGoblets() << endl;

    cout << "Choose one of the following:" << endl;
    cout << "1. Ingredients: To make food, you have to cook raw ingredients. " << endl;
    cout << "2. Cookware: You will need something to cook those ingredients." << endl;
    cout << "3. Weapons: It's dangerous to go alone, take this!" << endl; 
    cout << "4. Armor: If you want to survive monster attacks, you will need some armor." << endl;
    cout << "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl;
    cout << "6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;
    int select;
    cin >> select;
    while(select != 1 && select != 2 && select != 3 && select != 4 && select != 5 && select != 6) //runs until valid input
    {
        cout << "Enter a valid option (1-6)" << endl;
        cin >> select;
    }
    //cookware
    if(select == 2) //works like seeMerchant, but with room cost factor
    {
        cout << "Which cookware would you like? Each has a different probability of breaking when used (marked XX%)." << endl;
        cout << "Choose 1:" << endl;
        cout << "1. (25%) Ceramic Pot [" << (int) 2 * factor << " Gold]" << endl; 
        cout << "2. (10%) Frying Pan ["<<(int) factor * 10 <<" Gold]" << endl;
        cout << "3. ( 2%) Cauldron [" << (int) factor * 20 <<" Gold]" << endl;
        cout << "4. Cancel" << endl;  
        int option;
        cin >> option;
        while(option != 1 && option != 2 && option != 3 && option != 4) //runs until valid input
        {
            cout << "Enter a valid option (1-4)" << endl;
            cin >> option;
        } 
        if(option == 4) //if cancled
        {
            cout << "Canceled." << endl;
        }
        else
        {
            //works like seeMerchant, but with room cost factor
            string choice;
            int cost;
            if(option == 1)
            {
                choice = "Ceramic Pot(s)";
                cost = (int) 2 * factor;
            }
            else if(option == 2)
            {
                choice = "Frying Pan(s)";
                cost = (int) factor * 10;
            }
            else
            {
                choice = "Cauldron(s)";
                cost = (int) factor * 20;
            }
            cout << "How many would you like? (Enter a positive integer, or 0 to cancel" << endl;
            int count;
            cin >> count;
            while((count * cost > items.getGold()) || count < 0)
            {
                cout << "You do not have enough for this purchase, or the input was invalid. Try again. How many do you want?" << endl;
                cin >> count;
            }
            if(count == 0)
            {
                cout << "Canceled." << endl;
            }
            else
            {
                cout << "Do you want to buy " << count << " " << choice << " for " << cost * count << " Gold? (y/n)" << endl; //confirms purchase
                string y;
                cin >> y;
                while(y != "y" && y != "n")
                {
                    cout << "Enter y/n" << endl;
                    cin >> y;
                }

                if(y == "y")
                {
                    if(option == 1)
                    {
                        items.setPots(items.getPots() + count);
                        cout << "Successfully purchased. What else can I get you?" << endl;
                    }
                    else if(option == 2)
                    {
                        items.setPans(items.getPans() + count);
                        cout << "Successfully purchased. What else can I get you?" << endl;
                    }
                    else
                    {
                        items.setCauldrons(items.getCauldrons() + count);
                        cout << "Successfully purchased. What else can I get you?" << endl;
                    }
                    items.setGold(items.getGold() - cost * count);
                }
                else
                {
                    cout << "You canceled." << endl; //if purchase canceled
                }
            }

        }

    }

    //ingredients
    if(select == 1) //works like seeMerchant, but with room cost factor
    {
        cout << "How many kg of ingredients do you need [" << factor << " Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)" << endl;
        int num;
        cin >> num;
        while((num < 0 || num % 5 != 0) || items.getGold() < num)
        {
            cout << "You do not have enough for this purchase, or you input was invalid. Enter a positive number that is a multiple of 5, or 0 to cancel:" << endl;
            cin >> num;
        }

        cout << "You want to buy " << num << " kg of ingredients for " << (int) factor * num << " gold? (y/n):" << endl;
        string n;
        cin >> n;
        while(n != "y" && n != "y")
        {
            cout << "Enter y/n, try again:" << endl;
            cin >> n;
        }
        if(n == "n")
        {
            cout << "Canceled." << endl;
        }
        else
        {
            items.setGold(items.getGold() - (int) factor * num); //acounting for factor
            items.setIngredients(items.getIngredients() + num);
            cout << "Thank you for purchasing. What else can I get for you?" << endl;
        }


    }
    //weapons
    if(select == 3) //works like seeMerchant, but with room cost factor
    {
        cout << "I have a plentiful collection of weapons to choose from, what would you like? Note that some of them provide you a special bonus in combat, marked by a (+X)." << endl;
        cout << "Choose one of the following:" << endl;
        cout << "1. Stone Club [" << (int) factor * 2 << " Gold]" << endl;
        cout << "2. Iron Spear [" << (int) factor * 2 << " Gold]" << endl;
        cout << "3. (+1) Mythril Rapier [" << (int) factor * 5 << " Gold]" << endl;
        cout << "4. (+2) Flaming Battle-Axe [" << (int) factor * 15 << " Gold]" << endl;
        cout << "5. (+3) Vorpal Longsword [" << (int) factor * 50 << " Gold]" << endl;
        cout << "6. Cancel" << endl;
        int weapon;
        cin >> weapon;
        while(weapon != 1 && weapon != 2 && weapon != 3 && weapon != 4 && weapon != 5 && weapon != 6) //runs until input is valid
        {
            cout << "Enter a number 1 - 6. Try again: " << endl;
            cin >> weapon;
        }
        cout << "How many would you like? Enter a postive integer, or 0 to cancel." << endl;
        int weapon_count;
        cin >> weapon_count;
        int weapon_cost = 0;
        string weapon_name;
        
        if(weapon == 1)
                {
                    weapon_cost = (int) factor * 2 * weapon_count;
                    weapon_name = "Stone Club";
                }
                else if(weapon == 2)
                {   
                    weapon_cost = (int) factor * 2 * weapon_count;
                    weapon_name = "Iron Spear";
                }
                else if(weapon == 3)
                {   
                    weapon_cost = (int) factor * 5 * weapon_count;
                    weapon_name = "Mythril Rapier";
                }
                else if(weapon == 4)
                {
                    weapon_cost = (int) factor * 15 * weapon_count;
                    weapon_name = "Flaming Battle-Axe";
                }
                else if(weapon == 5)
                {      
                    weapon_cost = (int) factor * 50 * weapon_count;
                    weapon_name = "Vorpal Longsword";
                }
                
        while(weapon_count < 0  || weapon_cost > items.getGold()) //checks if avove costs are valid for purchase
        {
            //if purchase can not be made
            cout << "You do not have enough, or you did not enter a positive integer. Try again" << endl;
            cin >> weapon_count;
            if(weapon_count == 0)
            {
                break;
            }
            else
            {
                if(weapon == 1)
                {
                    weapon_cost = (int) factor * 2 * weapon_count;
                    weapon_name = "Stone Club";
                }
                else if(weapon == 2)
                {   
                    weapon_cost = (int) factor * 2 * weapon_count;
                    weapon_name = "Iron Spear";
                }
                else if(weapon == 3)
                {   
                    weapon_cost = (int) factor * 5 * weapon_count;
                    weapon_name = "Mythril Rapier";
                }
                else if(weapon == 4)
                {
                    weapon_cost = (int) factor * 15 * weapon_count;
                    weapon_name = "Flaming Battle-Axe";
                }
                else if(weapon == 5)
                {      
                    weapon_cost = (int) factor * 50 * weapon_count;
                    weapon_name = "Vorpal Longsword";
                }


            }
        }

        if(weapon_count == 0)
        {
            cout << "Canceled." << endl; //if canceled
        }
        else
        {
            //after confirming purchase is valid, calculates cose and names with factor
            if(weapon == 1)
            {
                weapon_cost = (int) factor * 2 * weapon_count;
                weapon_name = "Stone Club";
            }
            else if(weapon == 2)
            {   
                weapon_cost = (int) factor * 2 * weapon_count;
                weapon_name = "Iron Spear";
            }
            else if(weapon == 3)
            {
                weapon_cost = (int) factor * 5 * weapon_count;
                weapon_name = "Mythril Rapier";
            }
            else if(weapon == 4)
            {
                weapon_cost = (int) factor * 15 * weapon_count;
                weapon_name = "Flaming Battle-Axe";
            }
            else if(weapon == 5)
            {
                weapon_cost =(int) factor * 50 * weapon_count;
                weapon_name = "Vorpal Longsword";
            }
        }
      cout << "Do you want to purchase " << weapon_count << " " << weapon_name << "(s) for " << weapon_cost << " gold? (y/n):" << endl;
      string yn;
      cin >> yn;
      while(yn != "y" && yn!= "n") //runs until valid
      {
        cout << "Enter y/n. Try again:" << endl;
        cin >> yn;
      }
      if(yn == "n")
      {
        cout << "Canceled purchase." << endl;
      }
      else
      {
        cout << "Purchase successful." << endl;
            //edits items values for weapon purchase
            if(weapon == 1)
            {
                items.setClubs(items.getClubs() + weapon_count);
                items.setGold(items.getGold() - weapon_cost);
            }
            else if(weapon == 2)
            {
                items.setSpears(items.getSpears() + weapon_count);
                items.setGold(items.getGold() - weapon_cost);
            }
            else if(weapon == 3)
            {
                items.setRapiers(items.getRapiers() + weapon_count);
                items.setGold(items.getGold() - weapon_cost);
            }
            else if(weapon == 4)
            {
                items.setAxes(items.getAxes() + weapon_count);
                items.setGold(items.getGold() - weapon_cost);
            }
            else
            {
                items.setLongswords(items.getLongswords() + weapon_count);
                items.setGold(items.getGold() - weapon_cost);
            }
      }

    }

    //armor
    if(select == 4) //works like seeMerchant, but with room cost factor
    {
        cout << "How many suits of armor can I get you (5 gold each)? Enter a positive integer, or 0 to cancel." << endl;
        int armor;
        cin >> armor;
        int armor_cost = (int) factor * 5 * armor; //acounts for factor
        while(armor < 0 || armor_cost > items.getGold())
        {
            cout << "You can not purhcase this many, or you did not enter a positve number. Try again:" << endl;
            cin >> armor;
            armor_cost = armor * 5;
        }
        if(armor != 0)
        {
            cout << "You want to buy " << armor << " suit(s) of armor for " << armor_cost << " Gold? (y/n)" << endl;
            string confirm;
            cin >> confirm;
            while(confirm != "y" && confirm != "n")
            {
                cout << "Enter y/n. Try again:" << endl;
                cin >> confirm;
            }
            if(confirm == "n")
            {
                cout << "Canceled purchase." << endl;
            }
            else
            {
                //changes proper values with factor accounted for
                cout << "Thank you for the purchase. What else can I get you?" << endl;
                items.setArmor(items.getArmor() + armor);
                items.setGold(items.getGold() - armor_cost);
            }
        }
        else
        {
            cout << "You canceled." << endl;
        }
    }
  
    //treasures
    if(select == 5) //works like seeMerchant
    {
        cout <<"Which treasure would you like to sell?" << endl; 
        cout <<"1). Ring (10 gold)" << endl;
        cout <<"2). Necklace (20 gold)" << endl;
        cout <<"3). Bracelet (30 gold)" << endl;
        cout <<"4). Circlet (40 gold)" << endl;
        cout <<"5). Goblet (50 gold)" << endl;
        string sell;
        cin >> sell;
        bool can_buy = true; 
        int number_to_sell;
        string confirm;
        while(can_buy) //runs until can_buy becomes false when purhcase is made
        {
            if(sell == "1" && items.getRings() >= 1)
            {
                cout << "How many do you want to sell?" << endl;
                cin >> number_to_sell;
                while(number_to_sell < items.getRings()) //checks user has enough of desired, runs until valid
                {
                    cout <<"You do not have that many to sell. Try again:" << endl;
                    cin >> number_to_sell;
                }
                can_buy = false;
                cout << "Sell " << number_to_sell << " rings? (y/n)" << endl; //confirms purchase
                cin >> confirm;
                while(confirm != "y" && confirm != "n") //runns until valid input
                {
                    cout << "Enter y/n. Try again:" << endl;
                    cin >> confirm;
                }
                if(confirm == "y") //if purchase is wanted
                {
                    //setters and getters to update as purchase was made
                    cout << "Thank you for your purchase." << endl;
                    items.setRings(items.getRings() - number_to_sell);
                    items.setGold(items.getGold() + 10 * number_to_sell);
                }
                else{
                    cout <<"Goodbye." << endl;
                }

                
            }

            //same process as with sell = 1 (rings) above
            else if(sell == "2" && items.getNecklaces() >= 1)
            {
                cout << "How many do you want to sell?" << endl;
                cin >> number_to_sell;
                while(number_to_sell < items.getNecklaces())
                {
                    cout <<"You do not have that many to sell. Try again:" << endl;
                    cin >> number_to_sell;
                }
                can_buy = false;
                cout << "Sell " << number_to_sell << " necklaces? (y/n)" << endl;
                cin >> confirm;
                while(confirm != "y" && confirm != "n")
                {
                    cout << "Enter y/n. Try again:" << endl;
                    cin >> confirm;
                }
                if(confirm == "y")
                {
                    cout << "Thank you for your purchase." << endl;
                    items.setNecklaces(items.getNecklaces() - number_to_sell);
                    items.setGold(items.getGold() + 20 * number_to_sell);
                }
                else{
                    cout <<"Goodbye." << endl;
                }
            }
            //same process as with sell = 1 (rings) above
            else if(sell == "3" && items.getBracelets() >= 1)
            {
                cout << "How many do you want to sell?" << endl;
                cin >> number_to_sell;
                while(number_to_sell < items.getBracelets())
                {
                    cout <<"You do not have that many to sell. Try again:" << endl;
                    cin >> number_to_sell;
                }
                can_buy = false;
                cout << "Sell " << number_to_sell << " bracelets? (y/n)" << endl;
                cin >> confirm;
                while(confirm != "y" && confirm != "n")
                {
                    cout << "Enter y/n. Try again:" << endl;
                    cin >> confirm;
                }
                if(confirm == "y")
                {
                    cout << "Thank you for your purchase." << endl;
                    items.setBracelets(items.getBracelets() - number_to_sell);
                    items.setGold(items.getGold() + 30 * number_to_sell);
                }
                else{
                    cout <<"Goodbye." << endl;
                }
            }
            //same process as with sell = 1 (rings) above
            else if(sell == "4" && items.getCirclets() >= 1)
            {
                cout << "How many do you want to sell?" << endl;
                cin >> number_to_sell;
                while(number_to_sell < items.getCirclets())
                {
                    cout <<"You do not have that many to sell. Try again:" << endl;
                    cin >> number_to_sell;
                }
                can_buy = false;
                cout << "Sell " << number_to_sell << " circlets? (y/n)" << endl;
                cin >> confirm;
                while(confirm != "y" && confirm != "n")
                {
                    cout << "Enter y/n. Try again:" << endl;
                    cin >> confirm;
                }
                if(confirm == "y")
                {
                    cout << "Thank you for your purchase." << endl;
                    items.setRings(items.getCirclets() - number_to_sell);
                    items.setGold(items.getGold() + 40 * number_to_sell);
                }
                else{
                    cout <<"Goodbye." << endl;
                }
            }
            //same process as with sell = 1 (rings) above
            else if(sell == "5" && items.getGoblets() >= 1)
            {
                cout << "How many do you want to sell?" << endl;
                cin >> number_to_sell;
                while(number_to_sell < items.getGoblets())
                {
                    cout <<"You do not have that many to sell. Try again:" << endl;
                    cin >> number_to_sell;
                }
                can_buy = false;
                cout << "Sell " << number_to_sell << " goblets? (y/n)" << endl;
                cin >> confirm;
                while(confirm != "y" && confirm != "n")
                {
                    cout << "Enter y/n. Try again:" << endl;
                    cin >> confirm;
                }
                if(confirm == "y")
                {
                    cout << "Thank you for your purchase." << endl;
                    items.setRings(items.getGoblets() - number_to_sell);
                    items.setGold(items.getGold() + 50 * number_to_sell);
                }
                else{
                    cout <<"Goodbye." << endl;
                }
            }
            else
            {
                cout << "Did not enter 1 - 5, or you do not have enough of that treasure to sell." << endl; //user did not enter valid option
                cin >> number_to_sell;
            }
        }
    }
    //exit
    if(select == 6)
    {
        cout << "Are you sure you are done? You will not be able to buy anything else from me! (y/n)" << endl;
        string sure;
        cin >> sure;
        while(sure != "y" && sure != "n") //runs until valid input
        {
            cout << "Enter y/n. Try again:" << endl;
            cin >> sure;
        }
        if(sure == "y") 
        {
            cout << "Good luck and goodbye!" << endl;
            run = false; //ends menu loop
        }
        else
        {
            cout << "Glad you changed your mind!" << endl; //cancels exit
        }

    }
  
  } 
}

//fights monster. returns true if monster is beat
bool fightMonster(Player &player, Items &items, Party &party, string monsters_one[], string monsters_two[], string monsters_three[], string monsters_four[], string monsters_five[], string sorcerer_monster[], Sorcerer &sorcerer)
{
    srand(time(0));
    //below values are to canculate chance of winning formula
    int num_weapons = items.getAxes() + items.getClubs() + items.getLongswords() + items.getSpears() + items.getRapiers();
    int w = num_weapons + (items.getLongswords() * 3) + (items.getRapiers() * 1) + (2 * items.getAxes());
    int d = 0;
    int dead_member;
    string attack_surrender;
    int keydrop;
    if(items.getAxes() > 0)
    {
        d++;
    }
    if(items.getClubs() > 0)
    {
        d++;
    }
    if(items.getSpears() > 0)
    {
        d++;
    }
    if(items.getLongswords() > 0)
    {
        d++;
    }
    if(items.getRapiers() > 0)
    {
        d++;
    }
    int alive = 1;
    for(int i = 0; i < 4; i ++)
    {
        if(party.getPartyFullness(i) > 0)
        {
            alive ++;
        }
    }
    if(d / alive >= 1)
    {
        d = 4;
    }
    else
    {
        d = 0;
    }

    int a = items.getArmor();
    //random values calculated
    int r1 = (rand() % 6) + 1;
    int r2 = (rand() % 6) + 1;
    char separator = ',';
    double outcome;
    int death_chance;
    bool win = false; //current false, changes if win

    int count;
    if(player.getRooms() == 0) //if 0 rooms
    {
       int one_chance = (rand() % 3) + 0;
       while(monsters_one[one_chance].length() == 0) //picks random monster from monsters with level 1
       {
        one_chance = (rand() % 3) + 0;
       }
       cout << monsters_one[one_chance] << " ahead! Get ready to fight!" << endl;
       if(num_weapons <= 0)  //if no weapons
       {
        dead_member = (rand() % 3) + 0; //chance of dead party member
        while(party.getPartyFullness(dead_member) <= 0)
        {
            dead_member = (rand() % 3) + 0;
        }
        party.setPartyFullness(dead_member, 0); //kills member
        cout << party.getPartyName(dead_member) << " has been held captive. You must move on without them." << endl; //held captive
       }
       else
       {
        cout << "Attack or surrender? (a/s)" << endl;
        cin >> attack_surrender;
        while(attack_surrender != "a" && attack_surrender != "s") //until valid input
        {
            cout <<"Enter a valid input. (a/s)" << endl;
            cin >> attack_surrender;
        }
        if(attack_surrender == "s") //if surrrender
        {
           dead_member = (rand() % 3) + 0;
            while(party.getPartyFullness(dead_member) <= 0) //random member held captive
            {
                dead_member = (rand() % 3) + 0;
            }
            party.setPartyFullness(dead_member, 0);
            cout << party.getPartyName(dead_member) << " has been held captive. You must move on without them." << endl; 
        }
        else //if attack
        {
            outcome = (r1 * w + d) - ((r2 * 1) / a); //calculates chance of winning
            if(outcome > 0) //if win
            {
                win = true; //win = true, returns win
                cout << "You killed the monster! You gained:" << endl;
                //rewards for gold
                items.setGold(items.getGold() + (10));
                cout << "10 more gold" << endl;
                items.setIngredients(items.getIngredients() + 5);
                cout << "5 more ingredients!" << endl;
                keydrop = (rand() % 10) + 1;
                if(keydrop == 2) //chance of key drop
                {
                    player.setKeys(player.getKeys() + 1);
                    cout << "A key!" << endl;
                    
                }
                for(int i = 0; i < 4; i++) 
                {
                    if(monsters_one[i] == monsters_one[one_chance])
                    {
                        monsters_one[i] = ""; //removes monster's name ("dead")
                        break;
                    }
                } 
            }
            else // if loss
            {
                items.setGold(items.getGold() * 3 / 4); //loses gold
                items.setIngredients(items.getIngredients() - 30); //loses ingredients
                if(items.getArmor() >= 5)
                {
                    for(int i = 0; i < 4; i++)
                    {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl; //chance of party member death
                        }
                    }
                }
                else{
                    //calculates who dies/chance of death based off of different amounts of armor
                    switch(items.getArmor())
                    {
                        case 0: //if 0 armor
                        for(int i = 0; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }

                        case 1: //1 armor
                        for(int i = 1; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(0, 0);
                            cout << party.getPartyName(0) << " died." << endl;
                        }

                        case 2: //2 armor
                        for(int i = 2; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        for(int i = 0; i < 2; i++)
                        {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                        }
                        case 3: //3 armor
                        for(int i = 3; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        for(int i = 0; i < 3; i++)
                        {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                        }
                    }
                }
            }
        }


       }
    }

    if(player.getRooms() == 1) //repeats same process as above but with new sets of monsters (1 room cleared, so level two monsters)
    {
       int two_chance = (rand() % 3) + 0;
       while(monsters_two[two_chance].length() == 0) //uses level two monsters
       {
        two_chance = (rand() % 3) + 0;
       }
       cout << monsters_two[two_chance] << " ahead! Get ready to fight!" << endl;
       if(num_weapons <= 0)
       {
        dead_member = (rand() % 3) + 0;
        while(party.getPartyFullness(dead_member) <= 0)
        {
            dead_member = (rand() % 3) + 0;
        }
        party.setPartyFullness(dead_member, 0);
        cout << party.getPartyName(dead_member) << " has been held captive. You must move on without them." << endl;
       }
       else
       {
        cout << "Attack or surrender? (a/s)" << endl;
        cin >> attack_surrender;
        while(attack_surrender != "a" && attack_surrender != "s")
        {
            cout <<"Enter a valid input. (a/s)" << endl;
            cin >> attack_surrender;
        }
        if(attack_surrender == "s")
        {
           dead_member = (rand() % 3) + 0;
            while(party.getPartyFullness(dead_member) <= 0)
            {
                dead_member = (rand() % 3) + 0;
            }
            party.setPartyFullness(dead_member, 0);
            cout << party.getPartyName(dead_member) << " has been held captive. You must move on without them." << endl; 
        }
        else
        {
            outcome = (r1 * w + d) - ((r2 * 2) / a);
            if(outcome > 0)
            {
                win = true;
                cout << "You killed the monster! You gained:" << endl;
                items.setGold(items.getGold() + (20));
                cout << "20 more gold" << endl;
                items.setIngredients(items.getIngredients() + 10);
                cout << "10 more ingredients!" << endl;
                keydrop = (rand() % 10) + 1;
                if(keydrop == 2)
                {
                    player.setKeys(player.getKeys() + 1);
                    cout << "A key!" << endl;
                    
                }
                for(int i = 0; i < 4; i++)
                {
                    if(monsters_two[i] == monsters_two[two_chance])
                    {
                        monsters_two[i] = "";
                        break;
                    }
                } 
            }
            else
            {
                items.setGold(items.getGold() * 3 / 4);
                items.setIngredients(items.getIngredients() - 30);
                if(items.getArmor() >= 5)
                {
                    for(int i = 0; i < 4; i++)
                    {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                    }
                }
                else{
                    switch(items.getArmor())
                    {
                        case 0:
                        for(int i = 0; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }

                        case 1:
                        for(int i = 1; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(0, 0);
                            cout << party.getPartyName(0) << " died." << endl;
                        }

                        case 2:
                        for(int i = 2; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        for(int i = 0; i < 2; i++)
                        {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                        }
                        case 3:
                        for(int i = 3; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        for(int i = 0; i < 3; i++)
                        {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                        }
                    }
                }
            }
        }


       }
    }


    if(player.getRooms() == 2)//repeats same process as above but with new sets of monsters (2 rooms cleared, so level three monsters)
    {
       int three_chance = (rand() % 3) + 0;
       while(monsters_three[three_chance].length() == 0)
       {
        three_chance = (rand() % 3) + 0;
       }
       cout << monsters_one[three_chance] << " ahead! Get ready to fight!" << endl;
       if(num_weapons <= 0)
       {
        dead_member = (rand() % 3) + 0;
        while(party.getPartyFullness(dead_member) <= 0)
        {
            dead_member = (rand() % 3) + 0;
        }
        party.setPartyFullness(dead_member, 0);
        cout << party.getPartyName(dead_member) << " has been held captive. You must move on without them." << endl;
       }
       else
       {
        cout << "Attack or surrender? (a/s)" << endl;
        cin >> attack_surrender;
        while(attack_surrender != "a" && attack_surrender != "s")
        {
            cout <<"Enter a valid input. (a/s)" << endl;
            cin >> attack_surrender;
        }
        if(attack_surrender == "s")
        {
           dead_member = (rand() % 3) + 0;
            while(party.getPartyFullness(dead_member) <= 0)
            {
                dead_member = (rand() % 3) + 0;
            }
            party.setPartyFullness(dead_member, 0);
            cout << party.getPartyName(dead_member) << " has been held captive. You must move on without them." << endl; 
        }
        else
        {
            outcome = (r1 * w + d) - ((r2 * 3) / a);
            if(outcome > 0)
            {
                win = true;
                cout << "You killed the monster! You gained:" << endl;
                items.setGold(items.getGold() + (30));
                cout << "30 more gold" << endl;
                items.setIngredients(items.getIngredients() + 15);
                cout << "15 more ingredients!" << endl;
                keydrop = (rand() % 10) + 1;
                if(keydrop == 2)
                {
                    player.setKeys(player.getKeys() + 1);
                    cout << "A key!" << endl;
                    
                }
                for(int i = 0; i < 4; i++)
                {
                    if(monsters_three[i] == monsters_three[three_chance])
                    {
                        monsters_three[i] = "";
                        break;
                    }
                } 
            }
            else
            {
                items.setGold(items.getGold() * 3 / 4);
                items.setIngredients(items.getIngredients() - 30);
                if(items.getArmor() >= 5)
                {
                    for(int i = 0; i < 4; i++)
                    {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                    }
                }
                else{
                    switch(items.getArmor())
                    {
                        case 0:
                        for(int i = 0; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }

                        case 1:
                        for(int i = 1; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(0, 0);
                            cout << party.getPartyName(0) << " died." << endl;
                        }

                        case 2:
                        for(int i = 2; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        for(int i = 0; i < 2; i++)
                        {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                        }
                        case 3:
                        for(int i = 3; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        for(int i = 0; i < 3; i++)
                        {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                        }
                    }
                }
            }
        }


       }
    }


    if(player.getRooms() == 3)//repeats same process as above but with new sets of monsters (3 rooms cleared, so level four monsters)
    {
       int four_chance = (rand() % 3) + 0;
       while(monsters_four[four_chance].length() == 0)
       {
        four_chance = (rand() % 3) + 0;
       }
       cout << monsters_four[four_chance] << " ahead! Get ready to fight!" << endl;
       if(num_weapons <= 0)
       {
        dead_member = (rand() % 3) + 0;
        while(party.getPartyFullness(dead_member) <= 0)
        {
            dead_member = (rand() % 3) + 0;
        }
        party.setPartyFullness(dead_member, 0);
        cout << party.getPartyName(dead_member) << " has been held captive. You must move on without them." << endl;
       }
       else
       {
        cout << "Attack or surrender? (a/s)" << endl;
        cin >> attack_surrender;
        while(attack_surrender != "a" && attack_surrender != "s")
        {
            cout <<"Enter a valid input. (a/s)" << endl;
            cin >> attack_surrender;
        }
        if(attack_surrender == "s")
        {
           dead_member = (rand() % 3) + 0;
            while(party.getPartyFullness(dead_member) <= 0)
            {
                dead_member = (rand() % 3) + 0;
            }
            party.setPartyFullness(dead_member, 0);
            cout << party.getPartyName(dead_member) << " has been held captive. You must move on without them." << endl; 
        }
        else
        {
            outcome = (r1 * w + d) - ((r2 * 4) / a);
            if(outcome > 0)
            {
                win = true;
                cout << "You killed the monster! You gained:" << endl;
                items.setGold(items.getGold() + (40));
                cout << "40 more gold" << endl;
                items.setIngredients(items.getIngredients() + 20);
                cout << "20 more ingredients!" << endl;
                keydrop = (rand() % 10) + 1;
                if(keydrop == 2)
                {
                    player.setKeys(player.getKeys() + 1);
                    cout << "A key!" << endl;
                    
                }
                for(int i = 0; i < 4; i++)
                {
                    if(monsters_four[i] == monsters_four[four_chance])
                    {
                        monsters_four[i] = "";
                        break;
                    }
                } 
            }
            else
            {
                items.setGold(items.getGold() * 3 / 4);
                items.setIngredients(items.getIngredients() - 30);
                if(items.getArmor() >= 5)
                {
                    for(int i = 0; i < 4; i++)
                    {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                    }
                }
                else{
                    switch(items.getArmor())
                    {
                        case 0:
                        for(int i = 0; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }

                        case 1:
                        for(int i = 1; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(0, 0);
                            cout << party.getPartyName(0) << " died." << endl;
                        }

                        case 2:
                        for(int i = 2; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        for(int i = 0; i < 2; i++)
                        {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                        }
                        case 3:
                        for(int i = 3; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        for(int i = 0; i < 3; i++)
                        {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                        }
                    }
                }
            }
        }


       }
    }

    if(player.getRooms() == 4)//repeats same process as above but with new sets of monsters (4 room cleared, so level five monsters)
    {
       int five_chance = (rand() % 3) + 0;
       while(monsters_five[five_chance].length() == 0)
       {
        five_chance = (rand() % 3) + 0;
       }
       cout << monsters_five[five_chance] << " ahead! Get ready to fight!" << endl;
       if(num_weapons <= 0)
       {
        dead_member = (rand() % 3) + 0;
        while(party.getPartyFullness(dead_member) <= 0)
        {
            dead_member = (rand() % 3) + 0;
        }
        party.setPartyFullness(dead_member, 0);
        cout << party.getPartyName(dead_member) << " has been held captive. You must move on without them." << endl;
       }
       else
       {
        cout << "Attack or surrender? (a/s)" << endl;
        cin >> attack_surrender;
        while(attack_surrender != "a" && attack_surrender != "s")
        {
            cout <<"Enter a valid input. (a/s)" << endl;
            cin >> attack_surrender;
        }
        if(attack_surrender == "s")
        {
           dead_member = (rand() % 3) + 0;
            while(party.getPartyFullness(dead_member) <= 0)
            {
                dead_member = (rand() % 3) + 0;
            }
            party.setPartyFullness(dead_member, 0);
            cout << party.getPartyName(dead_member) << " has been held captive. You must move on without them." << endl; 
        }
        else
        {
            outcome = (r1 * w + d) - ((r2 * 5) / a);
            if(outcome > 0)
            {
                win = true;
                cout << "You killed the monster! You gained:" << endl;
                items.setGold(items.getGold() + (50));
                cout << "50 more gold" << endl;
                items.setIngredients(items.getIngredients() + 25);
                cout << "25 more ingredients!" << endl;
                keydrop = (rand() % 10) + 1;
                if(keydrop == 2)
                {
                    player.setKeys(player.getKeys() + 1);
                    cout << "A key!" << endl;
                    
                }
                for(int i = 0; i < 4; i++)
                {
                    if(monsters_five[i] == monsters_five[five_chance])
                    {
                        monsters_five[i] = "";
                        break;
                    }
                } 
            }
            else
            {
                items.setGold(items.getGold() * 3 / 4);
                items.setIngredients(items.getIngredients() - 30);
                if(items.getArmor() >= 5)
                {
                    for(int i = 0; i < 4; i++)
                    {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                    }
                }
                else{
                    switch(items.getArmor())
                    {
                        case 0:
                        for(int i = 0; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }

                        case 1:
                        for(int i = 1; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(0, 0);
                            cout << party.getPartyName(0) << " died." << endl;
                        }

                        case 2:
                        for(int i = 2; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        for(int i = 0; i < 2; i++)
                        {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                        }
                        case 3:
                        for(int i = 3; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        for(int i = 0; i < 3; i++)
                        {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                        }
                    }
                }
            }
        }


       }
    }

    if(player.getRooms() == 5) //repeats same process as above but with sorcerer (5 rooms cleared)
    {
       cout << sorcerer_monster[0] << " ahead! Get ready to fight!" << endl; //uses sorcerer array
       if(num_weapons <= 0)
       {
        dead_member = (rand() % 3) + 0;
        while(party.getPartyFullness(dead_member) <= 0)
        {
            dead_member = (rand() % 3) + 0;
        }
        party.setPartyFullness(dead_member, 0);
        cout << party.getPartyName(dead_member) << " has been held captive. You must move on without them." << endl;
       }
       else
       {
        cout << "Attack or surrender? (a/s)" << endl;
        cin >> attack_surrender;
        while(attack_surrender != "a" && attack_surrender != "s")
        {
            cout <<"Enter a valid input. (a/s)" << endl;
            cin >> attack_surrender;
        }
        if(attack_surrender == "s")
        {
           dead_member = (rand() % 3) + 0;
            while(party.getPartyFullness(dead_member) <= 0)
            {
                dead_member = (rand() % 3) + 0;
            }
            party.setPartyFullness(dead_member, 0);
            cout << party.getPartyName(dead_member) << " has been held captive. You must move on without them." << endl; 
        }
        else
        {
            outcome = (r1 * w + d) - ((r2 * 6) / a); //sorcerer level 6 accounted for
            if(outcome > 0)
            {
                win = true; //if killed
                cout << "You killed the Sorcerer! You gained:" << endl; //if sorcerer killed
                items.setGold(items.getGold() + (10));
                cout << "10 more gold" << endl;
                items.setIngredients(items.getIngredients() + 5);
                cout << "5 more ingredients!" << endl;
                keydrop = (rand() % 10) + 1;
                if(keydrop == 2)
                {
                    player.setKeys(player.getKeys() + 1);
                    cout << "A key!" << endl;
                    
                }
                
                    if(sorcerer_monster[0] == sorcerer_monster[0])
                    {
                        sorcerer_monster[0] = "";
                        sorcerer.setHealth(0);
                    }
                
            }
            else
            {
                //consequences for loss
                items.setGold(items.getGold() * 3 / 4);
                items.setIngredients(items.getIngredients() - 30);
                if(items.getArmor() >= 5)
                {
                    for(int i = 0; i < 4; i++)
                    {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                    }
                }
                else{
                    switch(items.getArmor())
                    {
                        case 0:
                        for(int i = 0; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }

                        case 1:
                        for(int i = 1; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(0, 0);
                            cout << party.getPartyName(0) << " died." << endl;
                        }

                        case 2:
                        for(int i = 2; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        for(int i = 0; i < 2; i++)
                        {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                        }
                        case 3:
                        for(int i = 3; i < 4; i++)
                        {
                            death_chance = (rand() % 10) + 1;
                            if(death_chance == 2)
                            {
                                party.setPartyFullness(i, 0);
                                cout << party.getPartyName(i) << " died." << endl;
                            }
                        }
                        for(int i = 0; i < 3; i++)
                        {
                        death_chance = (rand() % 20) + 1;
                        if(death_chance == 2)
                        {
                            party.setPartyFullness(i, 0);
                            cout << party.getPartyName(i) << " died." << endl;
                        }
                        }
                    }
                }
            }
        }


       }
    }
    return win; //returns if monster is beat
}


//if NPC is found
void encounterNPC(Map &map, Player &player, Items &items, Party &party, int &option, string riddles[], string answers[], string monsters_one[], string monsters_two[], string monsters_three[], string monsters_four[], string monsters_five[], string sorcerer_monster[], Sorcerer &sorcerer)
{
    cout << "You found an NPC! Would you like to speak to the NPC (y/n)? If not, you will be prompted to move." << endl;
    string see_npc;
    cin >> see_npc;
    while(see_npc != "y" && see_npc != "n") //runs until input is valid
    {
        cout <<"Enter y/n. Try again:" << endl;
        cin >> see_npc;
    }
    
    

    if(see_npc == "n")
    {
        cout << "Where would you like to move?" << endl; //prompts player to move if they do not want to speak to npc
        option = 1;
    }
    else
    {
        map.removeNPC(map.getPlayerRow(), map.getPlayerCol()); //removes NPC off of the map
        string response;
        cout <<"Hello! I am an NPC, and I have a riddle for you. You must answer it correct like, and I will see you items! If not, I will summon a random monster." << endl;
        cout <<"Here is your riddle:" << endl;
        cout <<"" << endl;
        int riddle = (rand() % 19) + 0; //random number to pick riddle
        cout << riddles[19] << endl; //takes riddle at index of random number from array of riddles
        cout <<"" << endl;
        cout << "Enter your answer below. Be very careful, you have one chance!" << endl;
        cin >> response; //user enters response
        if(response != answers[riddle]) //checks if input equals riddle answer at the random index. If incorrect:
        {
            cout << "Incorrect! The answer was '" << answers[riddle] << ".' Time to fight a monster!" << endl;
            fightMonster(player, items, party, monsters_one, monsters_two, monsters_three, monsters_four, monsters_five, sorcerer_monster, sorcerer); //player fights monster if incorrect
        }
        else//if correct
        {
            cout << "Correct! Do you want to buy goods? (y/n)" << endl;
            string buy;
            cin >> buy;
            while(buy != "y" && buy != "n") //runs intil valid input
            {
                cout <<"Enter y/n. Try again:" << endl;
                cin >> buy;
            }
            if(buy == "y") //if user wants to buy
            {
                npcMenu(player, items, party); //if user wants to buy goods, opens npc menu.
            }

        }
        printStatus(player, sorcerer, items, party, map); //gives menu options after
    }



}

//chance of misfortune for after every move
void misfortune(Map &map, Player &player, Items &items, Party &party, bool tried_key)
{
    srand(time(0));
    
    cout << "Uh oh! Your team was robbed by dungeon bandits!" << endl;
    bool misfortune_run = true; // runs until misfortune happens
    int chance;

    while(misfortune_run)
    {  
    chance = (rand() % 10) + 1;
    //cookware breaks
    if(chance == 1 || chance == 2 || chance == 3) //robbery 30% chacne
    {
        cout << "Your team has been robbed!" << endl;
        int which = (rand() %  3); //random to decide which items are lost
        if(which == 1 && items.getIngredients() >= 10)
        {
            cout <<"You lost 10 kg of ingredients" << endl;
            items.setIngredients(items.getIngredients() - 10); //acounts for lost ingredients
        }
        else if((which == 2) && (items.getPots() >= 1 || items.getCauldrons() >= 1 || items.getPans() >= 1)) //for lost cookware
        {
            //below works as ingreidents did
            bool works = true;
            int lost_cookware;
            while(works){
            lost_cookware = (rand() % 3) + 0;
            if(lost_cookware == 1 && items.getPots() >= 1)
            {
                cout <<"You lost 1 Pot!" << endl;
                items.setPots(items.getPots() - 1);
                misfortune_run = false;
                works = false;
                break;
            }
            else if(lost_cookware == 2 && items.getCauldrons() >= 1)
            {
                cout <<"You lost 1 Cauldron!" << endl;
                items.setCauldrons(items.getCauldrons() - 1);
                misfortune_run = false;
                works = false;
                break;
            }
            else if(lost_cookware == 3 && items.getPots() >= 1)
            {
                cout <<"You lost 1 Pan!" << endl;
                items.setPans(items.getPans() - 1);
                misfortune_run = false;
                works = false;
                break;
            }
            }
        }
    }
    
    else if(chance == 4) //chance of weapons breaking
    {
        bool works = true;
        int lost_gear;
        while(works) //runs until weapons are broken
        {
            lost_gear = (rand() % 6) + 1; //calculates whih item will be lost

            //each if checks if the random chosen gear has at least one of it

            if(lost_gear == 1 && items.getArmor() >= 1) //if at least one armor
            {
                cout << "A set of armor broke!" << endl;
                items.setArmor(items.getArmor() - 1);  //removes 1 
                misfortune_run = false; //ends loop
                works = false; //ends loop
                break;
            }
            else if(lost_gear == 2 && items.getAxes() >= 1) //works as above
            {
                cout << "An axe broke!" << endl;
                items.setAxes(items.getAxes() - 1);
                misfortune_run = false;
                works = false;
                break;
            }
            else if(lost_gear == 3 && items.getSpears() >= 1) //works as above
            {
                cout << "A spear broke!" << endl;
                items.setSpears(items.getSpears() - 1);
                misfortune_run = false;
                works = false;
                break;
            }
            else if(lost_gear == 4 && items.getClubs() >= 1) //works as above
            {
                cout << "A club broke!" << endl;
                items.setClubs(items.getClubs() - 1);
                misfortune_run = false;
                works = false;
                break;
            }
            else if(lost_gear == 5 && items.getRapiers() >= 1) //works as above
            {
                cout << "A rapier broke!" << endl;
                items.setRapiers(items.getRapiers() - 1);
                misfortune_run = false;
                works = false;
                break;
            }
            else if(lost_gear == 6 && items.getLongswords() >= 1) //works as above
            {
                cout << "A Longsword broke!" << endl;
                items.setLongswords(items.getLongswords() - 1);
                misfortune_run = false;
                works = false;
                break;
            }
        }
    }

    else if(chance == 5|| chance == 6 || chance == 7) //foodpoisoning chance
    {
        int poison;
        bool run = true;
        while(run) //runs until misfortune happens
        {
            poison = (rand() % 3) + 0; //chooses party member
            //below if's check if chose party member has health to recieve foodpoisoning
            if(poison == 0 && party.getPartyName(0).length() > 0) 
            {
                party.setPartyFullness(0, party.getPartyFullness(0) - 10); //removes 10 hunger
                cout << party.getPartyName(0) << " got good poisoning and lost 10 points of hunger." << endl;
                if(party.getPartyFullness(0) <= 0) //if fullness is below 0
                {
                    cout << party.getPartyName(0) << " has died." << endl; //says member dies
                    party.setPartyName(0, ""); //removes name
                }
                misfortune_run = false; //ends loop
                run = false; //ends loop
                break;
            }
            else if(poison == 1 && party.getPartyName(1).length() > 0) //works as above
            {
                party.setPartyFullness(1, party.getPartyFullness(1) - 10);
                cout << party.getPartyName(1) << " got good poisoning and lost 10 points of hunger." << endl;
                if(party.getPartyFullness(1) <= 0)
                {
                    cout << party.getPartyName(1) << " has died." << endl;
                    party.setPartyName(1, "");
                }
                misfortune_run = false;
                run = false;
                break;
            }
            else if(poison == 2 && party.getPartyName(2).length() > 0) //works as above
            {
                party.setPartyFullness(2, party.getPartyFullness(2) - 10);
                cout << party.getPartyName(2) << " got good poisoning and lost 10 points of hunger." << endl;
                if(party.getPartyFullness(2) <= 0)
                {
                    cout << party.getPartyName(2) << " has died." << endl;
                    party.setPartyName(2, "");
                }
                misfortune_run = false;
                run = false;
                break;
            }
            else if(poison == 3 && party.getPartyName(3).length() > 0) //works as above
            {
                party.setPartyFullness(3, party.getPartyFullness(3) - 10);
                cout << party.getPartyName(3) << " got good poisoning and lost 10 points of hunger." << endl;
                if(party.getPartyFullness(3) <= 0)
                {
                    cout << party.getPartyName(3) << " has died." << endl;
                    party.setPartyName(3, "");
                }
                misfortune_run = false;
                run = false;
                break;
            }
        }
    }

    
    else if((chance == 8 || chance == 9 || chance == 10) && tried_key) //chance of member locked in room
    {
        int locked;
        bool run = true;
        while(run) //runs until misfortune occures/party member is locked
        {
            locked = (rand() % 3) + 0; //chooses random member
            if(locked == 0 && party.getPartyName(0).length() > 0) //uses name length to check if alive
            {
                cout << party.getPartyName(0) << " is locked in the room! You must move on with out them." << endl;
                party.setPartyName(0, ""); //removes name
                party.setPartyFullness(0, 0); //sets fullness to 0
                misfortune_run = false; //ends loop
                run = false; //ends loop;
                break;
            }
            else if(locked == 1 && party.getPartyName(1).length() > 0) //works as above
            {
                cout << party.getPartyName(1) << " is locked in the room! You must move on with out them." << endl;
                party.setPartyName(1, "");
                party.setPartyFullness(1, 0);
                misfortune_run = false;
                run = false;
                break;
            }
            else if(locked == 2 && party.getPartyName(2).length() > 0) //works as above
            {
                cout << party.getPartyName(2) << " is locked in the room! You must move on with out them." << endl;
                party.setPartyName(2, "");
                party.setPartyFullness(2, 0);
                misfortune_run = false;
                run = false;
                break;
            }
            else if(locked == 3 && party.getPartyName(3).length() > 0) //works as above
            {
                cout << party.getPartyName(3) << " is locked in the room! You must move on with out them." << endl;
                party.setPartyName(3, "");
                party.setPartyFullness(3, 0);
                misfortune_run = false;
                run = false;
                break;
            }
        }
    }

    
    }
}

//checks if every is alive, returns false if death count is one that should end game
bool membersCheck(Player &player, Party &party)
{
    int dead = 0; //dead counter
    for(int i = 0; i < 4; i++) //loops through all members
    {
        if(party.getPartyFullness(i) <= 0) //if current party member's fullness is 0
        {
            party.setPartyName(i, ""); //removes name
            party.setPartyFullness(i, 0); //removes fullness
            dead++; //dead counter inceases
        }
    }
    if(player.getFullness() <= 0) //if player's fullness is 0
    {
        return false;
    }
    if(dead > 3) //if more than three are dead game ends
    {
        return false;
    }
    else 
    {
        return true;
    }
    

}

//writes results to file. Similar status to status function
void writeResults(string file_name, Player &player, Items &items, Party &party, Sorcerer &sorcerer)
{
    ofstream fout; //to write to file
    fout.open(file_name); //opens file
    //same menu as seen in status funciton
    fout  << "" << endl;
    fout << "" << endl;
    fout << "+-------------+" << endl;
    fout << "|  STATS   |" << endl;
    fout << "+-------------+" << endl;
    fout << "| Rooms Cleared: " << player.getRooms() <<" | Keys: " << player.getKeys() << " | Anger Level: " << sorcerer.getAnger() << endl;
    fout << "+-------------+" << endl;
    fout << "| INVENTORY   |" << endl;
    fout << "+-------------+" << endl;
    fout << "| Gold        | " << items.getGold() << endl;
    fout << "| Ingredients | " << items.getIngredients() << " kg" << endl;
    fout << "| Cookware    | P: " << items.getPots() << " | F: " << items.getPans() << " | C: " << items.getCauldrons() << endl;
    fout << "| Weapons     | C: " << items.getClubs() << " | S: " << items.getSpears() << " | R: " << items.getRapiers() << " | B: " << items.getAxes() << "  | L: " << items.getLongswords() << endl;
    fout << "| Armor       | " << items.getArmor() << endl;
    fout << "| Treasures   | R: " <<  items.getRings() << " | N: " <<  items.getNecklaces() << " | B: " << items.getBracelets() << " | C: " << items.getCirclets() << " | G: "<< items.getGoblets() << endl;
    fout << "+-------------+" << endl;
    fout << "| PARTY       |" << endl;
    fout << "+-------------+" << endl;
    //check if players have fullness. If dead (0), "DEAD" replaces their name, and 0 fullness is displayed
    fout << "| " << player.getName() << " | Fullness: " << player.getFullness() << endl;
    if(party.getPartyName(0).length() > 0) //check if alive
    {
       fout << "| " << party.getPartyName(0) << " | Fullness: " << party.getPartyFullness(0) << endl;  // if alive
    }
    else{
    fout << "| DEAD        |" << endl; //if dead
    }
    //below checks for each party member, just as above checked for player
    if(party.getPartyName(1).length() > 0)
    {
       fout << "| " << party.getPartyName(1) << " | Fullness: " << party.getPartyFullness(0) << endl; 
    }
    else{
    fout << "| DEAD        |" << endl;
    }
    if(party.getPartyName(2).length() > 0)
    {
       fout << "| " << party.getPartyName(2) << " | Fullness: " << party.getPartyFullness(0) << endl; 
    }
    else{
    fout << "| DEAD        |" << endl;
    }
    if(party.getPartyName(3).length() > 0)
    {
       fout << "| " << party.getPartyName(3) << " | Fullness: " << party.getPartyFullness(0) << endl; 
    }
    else{
    fout << "| DEAD        |" << endl;
    }
    fout << "+-------------+" << endl;
    fout << "" << endl;
    fout.close(); //closes file
}

//if player wins, this fucntion is called to display a winning screen
void printWinResults(Player &player, Items &items, Party &party, Sorcerer &sorcerer)
{
    //same menu as other functions
    cout  << "" << endl;
    cout << "CONGRADUALTIONS" << endl;
    cout << "" << endl;
    cout << "+-------------+" << endl;
    cout << "| WIN STATS   |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Rooms Cleared: " << player.getRooms() <<" | Keys: " << player.getKeys() << " | Anger Level: " << sorcerer.getAnger() << endl;
    cout << "+-------------+" << endl;
    cout << "| INVENTORY   |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Gold        | " << items.getGold() << endl;
    cout << "| Ingredients | " << items.getIngredients() << " kg" << endl;
    cout << "| Cookware    | P: " << items.getPots() << " | F: " << items.getPans() << " | C: " << items.getCauldrons() << endl;
    cout << "| Weapons     | C: " << items.getClubs() << " | S: " << items.getSpears() << " | R: " << items.getRapiers() << " | B: " << items.getAxes() << "  | L: " << items.getLongswords() << endl;
    cout << "| Armor       | " << items.getArmor() << endl;
    cout << "| Treasures   | R: " <<  items.getRings() << " | N: " <<  items.getNecklaces() << " | B: " << items.getBracelets() << " | C: " << items.getCirclets() << " | G: "<< items.getGoblets() << endl;
    cout << "+-------------+" << endl;
    cout << "| PARTY       |" << endl;
    cout << "+-------------+" << endl;
    //does not check if player is alive as this is only displayed if player wins/is alive
    cout << "| " << player.getName() << " | Fullness: " << player.getFullness() << endl;
    
    //has to check for party's lives, (as done in writing function), as 3 can die and the player can still win the game
    if(party.getPartyName(0).length() > 0)
    {
       cout << "| " << party.getPartyName(0) << " | Fullness: " << party.getPartyFullness(0) << endl; 
    }
    else{
    cout << "| DEAD        |" << endl;
    }
    if(party.getPartyName(1).length() > 0)
    {
       cout << "| " << party.getPartyName(1) << " | Fullness: " << party.getPartyFullness(0) << endl; 
    }
    else{
    cout << "| DEAD        |" << endl;
    }
    if(party.getPartyName(2).length() > 0)
    {
       cout << "| " << party.getPartyName(2) << " | Fullness: " << party.getPartyFullness(0) << endl; 
    }
    else{
    cout << "| DEAD        |" << endl;
    }
    if(party.getPartyName(3).length() > 0)
    {
       cout << "| " << party.getPartyName(3) << " | Fullness: " << party.getPartyFullness(0) << endl; 
    }
    else{
    cout << "| DEAD        |" << endl;
    }
    cout << "+-------------+" << endl;
    cout << "" << endl;

}

//if player loses, this fucntion is called to display a loss screen
void printLossResults(Player &player, Items &items, Party &party, Sorcerer &sorcerer)
{
    //similar memu
    cout  << "" << endl;
    cout << "~~~~~~RIP~~~~~~" << endl; //RIP design
    cout << "" << endl;
    cout << "+-------------+" << endl;
    cout << "| LOSS STATS  |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Rooms Cleared: " << player.getRooms() <<" | Keys: " << player.getKeys() << " | Anger Level: " << sorcerer.getAnger() << endl;
    cout << "+-------------+" << endl;
    cout << "| INVENTORY   |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Gold        | " << items.getGold() << endl;
    cout << "| Ingredients | " << items.getIngredients() << " kg" << endl;
    cout << "| Cookware    | P: " << items.getPots() << " | F: " << items.getPans() << " | C: " << items.getCauldrons() << endl;
    cout << "| Weapons     | C: " << items.getClubs() << " | S: " << items.getSpears() << " | R: " << items.getRapiers() << " | B: " << items.getAxes() << "  | L: " << items.getLongswords() << endl;
    cout << "| Armor       | " << items.getArmor() << endl;
    cout << "| Treasures   | R: " <<  items.getRings() << " | N: " <<  items.getNecklaces() << " | B: " << items.getBracelets() << " | C: " << items.getCirclets() << " | G: "<< items.getGoblets() << endl;
    cout << "+-------------+" << endl;
    cout << "| PARTY       |" << endl;
    cout << "+-------------+" << endl;
    //checks for deaths as write function does
    if(player.getFullness()> 0)
    {
       cout << "| " << player.getName() << " | Fullness: " << party.getPartyFullness(0) << endl; 
    }
    else{
    cout << "| PLAYER DIED   |" << endl;
    }
    cout << "| " << player.getName() << " | Fullness: " << player.getFullness() << endl;
    if(party.getPartyName(0).length() > 0)
    {
       cout << "| " << party.getPartyName(0) << " | Fullness: " << party.getPartyFullness(0) << endl; 
    }
    else{
    cout << "| DEAD        |" << endl;
    }
    if(party.getPartyName(1).length() > 0)
    {
       cout << "| " << party.getPartyName(1) << " | Fullness: " << party.getPartyFullness(0) << endl; 
    }
    else{
    cout << "| DEAD        |" << endl;
    }
    if(party.getPartyName(2).length() > 0)
    {
       cout << "| " << party.getPartyName(2) << " | Fullness: " << party.getPartyFullness(0) << endl; 
    }
    else{
    cout << "| DEAD        |" << endl;
    }
    if(party.getPartyName(3).length() > 0)
    {
       cout << "| " << party.getPartyName(3) << " | Fullness: " << party.getPartyFullness(0) << endl; 
    }
    else{
    cout << "| DEAD        |" << endl;
    }
    cout << "+-------------+" << endl;
    cout << "" << endl;

}

int main()
{
    ofstream fout;
    fout.open("results.txt");
    fout << "";
    
    //creates new objects at start of game
    Items items;
    Player player;
    Party party;
    Sorcerer sorcerer;
    Map map;
    //creates arrays to store monster names by level
    string monsters_one[4];
    string monsters_two[4];
    string monsters_three[4];
    string monsters_four[4];
    string monsters_five[4];
    string sorcerer_monster[1];
    ifstream fin; //to read monster file
    string line;
    string monster_list[32];
    char separator = ',';
    int check;
    int current_one = 0;
    int current_two = 0;
    int current_three = 0;
    int current_four = 0;
    int current_five = 0;
    bool sorcerer_killed = false;
    //riddle arrays for text file to fill
    string riddles[20]; 
    string answers[20];
    string riddles_and_answers[20];
    char separator_two = '~';
    int current_line = 0;
    int misfortune_chance;
    fin.open("riddles.txt"); //opens riddles file
    //adds all riddles and answers to their respective arrays
    while(getline(fin, line)) //goes through whole file
    {
        check = split(line, separator_two, riddles_and_answers, 20); //split funciton divides line into 2 for riddle and answer by separator
            
            if(check == 2)
            {   
                    riddles[current_line] = riddles_and_answers[0];  //assigns first end of split to riddle
                    answers[current_line] = riddles_and_answers[1]; //assigns back end of split to answer
                    current_line++;
            }
    }
    fin.close(); //closes file

    //adds all monsters to arrays based on power
    fin.open("monsters.txt");
    while(getline(fin, line))
    {
            check = split(line, separator, monster_list, 32); //splut function divides line into 2 to retrive monster name
            
            if(check == 2)
            {
                //current variables decide which monster array to add current line's monster to    
                if(current_one < 4) 
                {
                    monsters_one[current_one] = monster_list[0]; //adds to lvl one monsters
                    current_one ++;
                }
                else if (current_two < 4)
                {
                    monsters_two[current_two] = monster_list[0]; //adds to lvl two monsters
                    current_two ++;
                }
                else if (current_three < 4)
                {
                    monsters_three[current_three] = monster_list[0]; //adds to lvl three monsters
                    current_three ++;
                }
                else if (current_four < 4)
                {
                    monsters_four[current_four] = monster_list[0]; //adds to lvl four monsters
                    current_four ++;
                }
                else if (current_five < 4)
                {
                    monsters_five[current_five] = monster_list[0]; // adds to lvl 5 monsters
                    current_five ++;
                }
                else
                {
                    sorcerer_monster[0] = monster_list[0]; //addsd last line name to sorcerer array (sorcerer monster)
                }
            }
    }
    fin.close(); //closes file


    //start game
    cout <<"Welcome to dungeon escape!" << endl;
    cout <<"" << endl;
    cout << "Enter your name: " << endl;
    //user enters name and is assigned to player's name
    string name;
    cin >> name;
    player.setName(name); 
    party.makeParty();

    seeMerchant(player, items, party); //see merchant function at start of game

    srand(time(0));
    
    //randomizes map rooms
    for(int i = 0; i < 5; i++)
    {
        int x = (rand() % 11) + 1;
        int y = (rand() % 11) + 1;
        if(map.isFreeSpace(x, y))
        {
            map.addRoom(x, y);
        }    
        else
        {
            while(!map.isFreeSpace(x, y))
            {
                x = (rand() % 11) + 1;
                y = (rand() % 11) + 1; 
            }
            map.addRoom(x, y);
        }
    }
    
    //randomizes NPC spaces after rooms to not overlay rooms
    for(int i = 0; i < 5; i ++)
    {
        int x = (rand() % 11) + 1;
        int y = (rand() % 11) + 1;
        if(map.isFreeSpace(x, y))
        {
            map.addNPC(x, y);
        }    
        else
        {
            while(!map.isFreeSpace(x, y))
            {
                x = (rand() % 11) + 1;
                y = (rand() % 11) + 1; 
            }
            map.addNPC(x, y);
        }
    }

    string option = printStatus(player, sorcerer, items, party, map); //prints status, and allows player to choose option

    while((option == "1" || option == "2" || option == "3" || option == "4")) // if user wants to do an action 
    {

    //move option
    if(option == "1")
    {
        srand(time(0));
        string dir;
        cin >> dir;
        while(!map.move(dir[0])) //checks for valid direction input, running until valid
        {
            cout << "Can not move there, or not w, a, s, or d. Try again:" << endl;
            cin >> dir;
        }
        if(map.isDungeonExit(map.getPlayerRow(), map.getPlayerCol()) && player.getRooms() == 5 && sorcerer.getHealth() == 0) //if player goes to exit and sorcerer is killed
        {
            option = "5"; //ends loop
            sorcerer_killed = false; //sorcerer killed player variable is false
        }
        else{
        
        if(!map.isExplored(map.getPlayerRow(), map.getPlayerCol())) //if space is not explored
        {
            
            if(sorcerer.getHealth() != 0) //if sorcerer not dead
            {
            sorcerer.increaseAnger(); //incerases with each move
            if(sorcerer.getAnger() == 100) //if sorcerer anger is 100
            {
                option = 5; //ends 
                sorcerer_killed = true; //sets sorcerer killing player to true
            }
            }
        }
        // if NPC space is landed on
        if(map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol()))
        {
                cout << "You found an NPC! Would you like to speak to the NPC (y/n)? If not, you will be prompted to move." << endl;
                string see_npc;
                cin >> see_npc;
                while(see_npc != "y" && see_npc != "n") //runs until valid
                {
                    cout <<"Enter y/n. Try again:" << endl;
                    cin >> see_npc;
                }
    

                if(see_npc == "n") //promts user to move if they do not want to visit npc
                {
                    
                    cout << "Where would you like to move?" << endl;
                    option = 1;
                }
                else //if they visit
                {
                    map.removeNPC(map.getPlayerRow(), map.getPlayerCol()); //removes npc of map
                    string response;
                    cout <<"Hello! I am an NPC, and I have a riddle for you. You must answer it correct like, and I will see you items! If not, I will summon a random monster." << endl;
                    cout <<"Here is your riddle:" << endl;
                    cout <<"" << endl;
                    int riddle = (rand() % 19) + 0; //calcules random ridlde
                    cout << riddles[riddle] << endl; //asks riddle
                    cout <<"" << endl;
                    cout << "Enter your answer below. Be very careful, you have one chance!" << endl;
                    cin >> response;
                    if(response != answers[riddle]) //if user input is equal to answer at index of the random chosen riddle
                    {
                        cout << "Incorrect! The answer was '" << answers[riddle] << ".' Time to fight a monster!" << endl;
                        fightMonster(player, items, party, monsters_one, monsters_two, monsters_three, monsters_four, monsters_five, sorcerer_monster, sorcerer); //if incrrect, a monster is fought
                    }
                    else
                    {
                        cout << "Correct! Do you want to buy goods? (y/n)" << endl; //if correct
                        string buy;
                        cin >> buy;
                        while(buy != "y" && buy != "n") //runs utnil valid input
                        {
                            cout <<"Enter y/n. Try again:" << endl; 
                            cin >> buy;
                        }
                        if(buy == "y")
                        {
                            npcMenu(player, items, party); //npc menu displayed if user wants to buy items
                        }

                    
                        printStatus(player, sorcerer, items, party, map);  //prompts next move
                    }
            }
        }
        
        
        int party_fullness_chance;
        for(int i = 0; i < 4; i++) //loops through party members, chance of decrease of fullness 
        {
            party_fullness_chance = (rand() % 5) + 1;
            if(party_fullness_chance == 1)
            {
                party.setPartyFullness(i, party.getPartyFullness(i) - 1);
            }
        }

        int player_fullness_chance = (rand() % 5) + 1; //chance of player fullness decreases
        if(player_fullness_chance == 1)
        {
            player.setFullness(player.getFullness() - 1);
        }

        if(map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol())) //if room
        {
            if(player.getKeys() > 0) //if player has keys
            {
                cout <<"Use a key and open the door? (y/n)" << endl;
                string use_key;
                cin >> use_key;
                while(use_key != "y" && use_key != "n")
                {
                    cout <<"Enter y/n. Try again:" << endl;
                    cin >> use_key;
                }
                if(use_key == "y") //if key is used to open
                {
                    
                    player.setRooms(player.getRooms() + 1); //increases rooms
                    if(fightMonster(player, items, party, monsters_one, monsters_two, monsters_three, monsters_four, monsters_five, sorcerer_monster, sorcerer)) //if player beats monster
                    {
                        misfortune_chance = (rand() % 5) + 1; //chance of misfortune
                        if(misfortune_chance == 1 || misfortune_chance == 2 || misfortune_chance == 3)
                        {
                            misfortune(map, player, items, party, true);
                        }
                        map.removeRoom(map.getPlayerRow(), map.getPlayerCol()); //removes map
                    }
                    else //if player loses to monster
                    {
                        misfortune_chance = (rand() % 5) + 1;
                        if(misfortune_chance == 1 || misfortune_chance == 2)
                        {
                            misfortune(map, player, items, party, true); //chance of misfortune
                        }
                        player.setRooms(player.getRooms() - 1);
                        player.setKeys(player.getKeys() - 1);
                    }
                }
            }
            else
            {
                //if no keys
                cout <<"You do not have any keys. Do you want to try to break into the room? (y/n)" << endl; 
                string break_in;
                cin >> break_in;
                while(break_in != "y" && break_in != "n")
                {
                    cout <<"Enter y/n. Try again:" << endl;
                    cin >> break_in;
                }
                if(break_in == "y") //if breaks in
                {
                    srand(time(0));
                    int losses = 0;
                    bool lost = false;
                    int dweller;
                    bool win = false;
                    cout <<"Uh oh, a trap! To escape, you must play Boulder/Parchment/Shears against the room dweller." << endl;
                    cout <<"Boulder beats Shears, Parchment beats Boulder, and Shears beats parchment. " << endl;
                    cout <<"You have three tries to beat the room dweller. A win allows you into the room. 3 Losses kills a party member at random." << endl;

                    while(!win) //runs until player wins or loses
                    {
                    cout <<"Pick Boulder (1), Parchment (2), or Shears (3):" << endl;
                    string choice;
                    cin >> choice;
                    while(choice != "1" && choice != "2" && choice != "3")
                    {
                        cout <<"Enter b, p, or s. Try again:" << endl;
                        cin >> choice;
                    }
                     dweller = (rand() % 3) + 1; //randomizes dewellers pick
                    if((choice == "1" && dweller == 3) || (choice == "2" && dweller == 1) || (choice == "3" && dweller == 2)) //if player wins
                    {
                        cout << "You beat the Dweller. You may enter the room:" << endl;
                        player.setRooms(player.getRooms() + 1); //rooms increases
                        if(fightMonster(player, items, party, monsters_one, monsters_two, monsters_three, monsters_four, monsters_five, sorcerer_monster, sorcerer)) //fights monster
                        {
                        //if mosnter is beat
                            misfortune_chance = (rand() % 5) + 1;
                            if(misfortune_chance == 1 || misfortune_chance == 2 || misfortune_chance == 3)
                            {
                                misfortune(map, player, items, party, false);
                            }
                            map.removeRoom(map.getPlayerRow(), map.getPlayerCol()); //removes room
                        }
                        else
                        {
                            //if monster is killed
                            misfortune_chance = (rand() % 5) + 1;
                            if(misfortune_chance == 1 || misfortune_chance == 2)
                            {   
                                misfortune(map, player, items, party, true); //misfortune chance
                            }
                            player.setRooms(player.getRooms() - 1); 
                            player.setKeys(player.getKeys() - 1); //loses key
                        }
                        win = true; //ends loop
                        break;
                    }
                    else if((choice == "1" && dweller == 1) || (choice == "2" && dweller == 2) || (choice == "3" && dweller == 3)) //tied options
                    {
                        cout << "You tied. No penalty." << endl;
                    }

                    //if loss
                    else
                    {
                        losses++; //losses increases
                        cout << "You lost. You have " << 3 - losses << " remaining." << endl;
                        if(losses == 3)
                        {
                            bool lost = true;
                            win = false; //ends loop once losses hits three
                            break;
                        }
                    }
                    }
                    if(lost) //if player lost
                    {
                        int random_death = (rand() % 3) + 0;
                        while(party.getPartyFullness(random_death) == 0) //random player death
                        {
                            random_death = (rand() % 3) + 0;
                        }
                        party.setPartyFullness(random_death, 0);
                        cout << party.getPartyName(random_death) << " has died." << endl;
                    }

                }
            }
        }
        option = printStatus(player, sorcerer, items, party, map); //prints status for net move
        }
    }

    //investigate
    if(option == "2")
    {
        srand(time(0));
        if(map.isExplored(map.getPlayerRow(), map.getPlayerCol())) //if already explored
        {
            cout << "This space can not be explored." << endl;
           option = printStatus(player, sorcerer, items, party, map); 
        }
        else
        {
            bool fights = false;
            map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
            int chance_one = (rand() % 10) + 1;
            if(chance_one == 1) //chance of getting key
            {
                player.setKeys(player.getKeys() + 1);
            }
            int chance_two = (rand() % 5) + 1;
            if(chance_two == 5) //chance of finding treasure
            {
                int treasure = player.getRooms();
                if(treasure == 1)
                {
                    items.setRings(items.getRings() + 1);
                    cout <<"You got a Silver ring (R). (This is worth 10 gold)." << endl;
                }
                else if(treasure == 2)
                {
                    items.setNecklaces(items.getNecklaces() + 1);
                    cout <<"You got a Ruby necklace (20 gold)." << endl;

                }
                else if(treasure == 3)
                {
                    items.setBracelets(items.getBracelets() + 1);
                    cout <<"You got a Emeral bracelet (B). (This is worth 30 gold)." << endl;
                }
                else if(treasure == 4)
                {
                    items.setCirclets(items.getCirclets() + 1);
                    cout <<"You got a Diamond circlet (C). (This is worth 40 gold)." << endl;
                }
                else if(treasure == 5)
                {
                    items.setGoblets(items.getGoblets() + 1);
                    cout <<"You got a Gem-encrusted goblet. (This is worth 50 gold)." << endl;
                }

            }
            int chance_three = (rand() % 5) + 1;
            if(chance_two == 1) //chance of finding monster
            {
                fightMonster(player, items, party, monsters_one, monsters_two, monsters_three, monsters_four, monsters_five, sorcerer_monster, sorcerer); //fights monster
                
            }

            
                int party_chance;
                int player_chance;
                for(int i = 0; i < 4; i ++)
                {
                    party_chance = (rand() % 2) + 1; //50% chance of fullness drops 1
                    if(party_chance == 1)
                    {
                        party.setPartyFullness(i, party.getPartyFullness(i) - 1);
                    }
                }
                player_chance = (rand() % 2) + 1; //50% chance fullness drops 1
                if(player_chance == 1)
                {
                    player.setFullness(player.getFullness() - 1);
                }
            
            misfortune_chance = (rand() % 5) + 1; //chance of misfortune
            if(misfortune_chance == 1 || misfortune_chance == 2)
            {
                misfortune(map, player, items, party, false);
            }
            option = printStatus(player, sorcerer, items, party, map); //status printed
        }
    }
    
    //fight monster
    if(option == "3")
    {
        if(sorcerer.getHealth() > 0) //if sorcerer is alive
        {
        fightMonster(player, items, party, monsters_one, monsters_two, monsters_three, monsters_four, monsters_five, sorcerer_monster, sorcerer); //fights monster
        }
        else{
            cout <<"You have defeated the Sorcerer! There are no monsters to defeat." << endl; //if sorcerer not alive
        }

        misfortune_chance = (rand() % 5) + 1; //chance of misfortune
        if(misfortune_chance == 1 || misfortune_chance == 2)
        {
            misfortune(map, player, items, party, false);
        }

        option = printStatus(player, sorcerer, items, party, map); //prints status

    }
    
    //cook food
    if(option == "4")
    {
        cout << "Which cookware would you like to use?" << endl;
        cout << "1. Ceramic Pot (25% chance of breaking)" << endl;
        cout << "2. Frying Pan (10% chance of breaking)" << endl;
        cout << "3. Cauldron (2% chance of breaking)" << endl;
        int cookware;
        cin >> cookware;
        while((cookware != 1 && cookware != 2 && cookware !=3) || ((cookware == 1 && items.getPots() < 1) || (cookware == 2 && items.getPans() < 1) || (cookware == 3 && items.getCauldrons() < 1)))//checks player has at least one cookware desired
        {
            cout << "You did not enter a valid option, or you do not have enough of that cookware. Try again:" << endl;
            cin >> cookware;
        }

        srand(time(0));
        cout <<"How many kg of ingredients would you like to use? You must cook in increments of 5 as there is a 5:1 ratio of ingredients to amount of fullness increased." << endl;
        int amount;
        cin >> amount;
        while(amount % 5 != 0 || amount > items.getIngredients() || amount < 0) //checks valid input
        {
            cout << "You do not have that many ingredients, or did not enter a multiple of 5. Try again:" << endl;
            cin >> amount;
        }
        int break_chance;
        if(cookware == 1) //pot used
        {
            break_chance = (rand() % 4) + 1;
            //if pot breaks
            if(break_chance == 2)
            {
                items.setPots(items.getPots() - 1);
                items.setIngredients(items.getIngredients() - amount);
                cout << "Your Pot broke. The meal is not created and your ingredients are lost." << endl;
            }
            // if it does not
            else{
                items.setIngredients(items.getIngredients() - amount);
                for(int i = 0; i < 4; i++)
                {
                    party.setPartyFullness(i, party.getPartyFullness(i) + 1);
                }
                player.setFullness(player.getFullness() + 1);
                cout << "Successful cook." << endl;
            }
            //outputs fullness
            cout << "+-------------+" << endl;
            cout << "| PARTY       |" << endl;
            cout << "+-------------+" << endl;
            cout << "| " << player.getName() << " | Fullness: " << player.getFullness() << endl;
            cout << "| " << party.getPartyName(0) << " | Fullness: " << party.getPartyFullness(0) << endl;
            cout << "| " << party.getPartyName(1) << " | Fullness: " << party.getPartyFullness(1) << endl;
            cout << "| " << party.getPartyName(2) << " | Fullness: " << party.getPartyFullness(2) << endl;
            cout << "| " << party.getPartyName(3) << " | Fullness: " << party.getPartyFullness(3) << endl;
            cout << "+-------------+" << endl;
            cout <<""<< endl;

        }

        else if(cookware == 2) //for pans
        {
            break_chance = (rand() % 10) + 1;
            //if pan breaks
            if(break_chance == 2)
            {
                items.setPans(items.getPans() - 1);
                items.setIngredients(items.getIngredients() - amount);
                cout << "Your Pan broke. The meal is not created and your ingredients are lost." << endl;
            }
            //if cook works
            else{
                items.setIngredients(items.getIngredients() - amount);
                for(int i = 0; i < 4; i++)
                {
                    party.setPartyFullness(i, party.getPartyFullness(i) + 1);
                }
                player.setFullness(player.getFullness() + 1);
                cout << "Successful cook." << endl;
            }
            //prints status
            cout << "+-------------+" << endl;
            cout << "| PARTY       |" << endl;
            cout << "+-------------+" << endl;
            cout << "| " << player.getName() << " | Fullness: " << player.getFullness() << endl;
            cout << "| " << party.getPartyName(0) << " | Fullness: " << party.getPartyFullness(0) << endl;
            cout << "| " << party.getPartyName(1) << " | Fullness: " << party.getPartyFullness(1) << endl;
            cout << "| " << party.getPartyName(2) << " | Fullness: " << party.getPartyFullness(2) << endl;
            cout << "| " << party.getPartyName(3) << " | Fullness: " << party.getPartyFullness(3) << endl;
            cout << "+-------------+" << endl;
            cout <<""<< endl;
        }

        else
        {

            break_chance = (rand() % 50) + 1;
            // cauldron breaks
            if(break_chance == 2)
            {
                items.setCauldrons(items.getCauldrons() - 1);
                items.setIngredients(items.getIngredients() - amount);
                cout << "Your Cauldron broke. The meal is not created and your ingredients are lost." << endl;
            }
            //if it does not
            else{
                items.setIngredients(items.getIngredients() - amount);
                for(int i = 0; i < 4; i++)
                {
                    party.setPartyFullness(i, party.getPartyFullness(i) + 1);
                }
                player.setFullness(player.getFullness() + 1);
                cout << "Successful cook." << endl;
            }
            //prints status
            cout << "+-------------+" << endl;
            cout << "| PARTY       |" << endl;
            cout << "+-------------+" << endl;
            cout << "| " << player.getName() << " | Fullness: " << player.getFullness() << endl;
            cout << "| " << party.getPartyName(0) << " | Fullness: " << party.getPartyFullness(0) << endl;
            cout << "| " << party.getPartyName(1) << " | Fullness: " << party.getPartyFullness(1) << endl;
            cout << "| " << party.getPartyName(2) << " | Fullness: " << party.getPartyFullness(2) << endl;
            cout << "| " << party.getPartyName(3) << " | Fullness: " << party.getPartyFullness(3) << endl;
            cout << "+-------------+" << endl;
            cout <<""<< endl;
        }
        misfortune_chance = (rand() % 5) + 1; //misfortune chance
        if(misfortune_chance == 1 || misfortune_chance == 2 || misfortune_chance == 3)
        {
            misfortune(map, player, items, party, true);
            cout << "" << endl;
        }
        //status printed
        option = printStatus(player, sorcerer, items, party, map);

    }
     

     if(!membersCheck(player, party)) //if false, too few players to win. Game ends
     {
        option = "10"; // ends loop
     }
    }

    writeResults("results.txt", player, items, party, sorcerer); //writes final stats to file
  

    if(option == "5") //if 5, player gave up
    {
        //final stats for giving up
        cout <<"" << endl;
        cout << "You gave up. Here are your stats:" << endl;
        cout << "" << endl;
        cout << "+-------------+" << endl;
        cout << "| Rooms Cleared: " << player.getRooms() <<" | Keys: " << player.getKeys() << " | Anger Level: " << sorcerer.getAnger() << endl;
        cout << "+-------------+" << endl;
        cout << "| INVENTORY   |" << endl;
        cout << "+-------------+" << endl;
        cout << "| Gold        | " << items.getGold() << endl;
        cout << "| Ingredients | " << items.getIngredients() << " kg" << endl;
        cout << "| Cookware    | P: " << items.getPots() << " | F: " << items.getPans() << " | C: " << items.getCauldrons() << endl;
        cout << "| Weapons     | C: " << items.getClubs() << " | S: " << items.getSpears() << " | R: " << items.getRapiers() << " | B: " << items.getAxes() << "  | L: " << items.getLongswords() << endl;
        cout << "| Armor       | " << items.getArmor() << endl;
        cout << "| Treasures   | R: " <<  items.getRings() << " | N: " <<  items.getNecklaces() << " | B: " << items.getBracelets() << " | C: " << items.getCirclets() << " | G: "<< items.getGoblets() << endl;
        cout << "+-------------+" << endl;
        cout << "| PARTY       |" << endl;
        cout << "+-------------+" << endl;
        cout << "| " << player.getName() << " | Fullness: " << player.getFullness() << endl;
        if(party.getPartyName(0).length() > 0)
        {
        cout << "| " << party.getPartyName(0) << " | Fullness: " << party.getPartyFullness(0) << endl; 
        }
        else{
        cout << "| DEAD        |" << endl;
        }
        if(party.getPartyName(1).length() > 0)
        {
        cout << "| " << party.getPartyName(1) << " | Fullness: " << party.getPartyFullness(0) << endl; 
        }
        else{
        cout << "| DEAD        |" << endl;
        }
        if(party.getPartyName(2).length() > 0)
        {
        cout << "| " << party.getPartyName(2) << " | Fullness: " << party.getPartyFullness(0) << endl; 
        }
        else{
        cout << "| DEAD        |" << endl;
        }
        if(party.getPartyName(3).length() > 0)
        {
        cout << "| " << party.getPartyName(3) << " | Fullness: " << party.getPartyFullness(0) << endl; 
        }
        else{
        cout << "| DEAD        |" << endl;
        }
        cout << "+-------------+" << endl;
        cout << "" << endl;
        
    }
    
    //loss due to members dead by hunger or sorcerer
    else if(!membersCheck(player, party) || sorcerer_killed)
    {
        cout << "" << endl;
        cout << "YOU OR YOUR PARTY HAS DIED" << endl;
        cout << "" << endl;
        printLossResults(player, items, party, sorcerer); //printLossResults() called to print loss results
        
    }

    //if if won
    else{
        printWinResults(player, items, party, sorcerer);  //printWinResults() called to print win results
    }



    return 0;
}
