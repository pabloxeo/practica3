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
    vector<int>::iterator aux = remove(dice[player].begin(), dice[player].end(), n);
}

void Dice::resetDice (color player , const vector<int> & new_dice = {1,2,3,4,5,6}){
    dice[player] = new_dice;
}

bool Dice::isAvailable(color player, int n){
    vector<int> player_dice = dice[player];
    return (find(player_dice.begin(), player_dice.end(), n) != player_dice.end());
}