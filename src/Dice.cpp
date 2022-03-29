# include "Dice.h"

#include <iostream>
#include<bits/stdc++.h>


Dice::Dice(){
    this->dice =  map <color, vector <int> > {
        {color::red,    {1,2,3,4,5,6}},
        {color::blue,   {1,2,3,4,5,6}},
        {color::yellow, {1,2,3,4,5,6}},
        {color::green,  {1,2,3,4,5,6}}
    };
};

Dice::Dice (const map <color, vector <int> > & d){
    this->dice =  map <color, vector <int> >(d);
};

const vector<int> & Dice::getDice (color player){
    return dice[player];
}

void Dice::removeNumber (color player, int n){
    for(int i = 0; i < dice[player].size(); i++) cout << dice[player][i] << endl;
    //vector<int>::iterator aux = remove(dice[player].begin(), dice[player].end(), n);
    dice[player].erase(remove(dice[player].begin(), dice[player].end(), n), dice[player].end()); 
    if (dice[player].empty())
    {
        resetDice(player);
    }
}

void Dice::resetDice (color player , const vector<int> & new_dice){
    dice[player] = new_dice;
}

bool Dice::isAvailable(color player, int n){
    vector<int> player_dice = dice[player];
    //for(int i =0; i < player_dice.size(); i++) cout << player_dice[i] << endl;
    return (find(player_dice.begin(), player_dice.end(), n) != player_dice.end());
}

void Dice::addNumber(color player, int n){
    dice[player].push_back(n);
}