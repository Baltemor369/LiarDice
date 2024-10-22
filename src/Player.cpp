#include "../inc/Player.h"
#include "../const.h"
#include <algorithm>


Player::Player(std::string new_name)
{
    name = new_name;
    qtyDea = 5; 
    eliminated=0;
}

Player::~Player()
{
}

std::string Player::info() const{
    std::string info = "Player: " + name + "\nDealt Dea: ";
    for(int dea : deas){
        info += std::to_string(dea) + " ";
    }
    return info;
}

void Player::addDea(int value) {
    deas.push_back(value);
}

void Player::removeDea(){
    deas.pop_back();
    --qtyDea;
}

int Player::getDea(int index) const{
    if (0 <= index && index <= qtyDea)
    {
        return deas.at(index);
    }
    return -1;
}

void Player::setDea(int index, int value){
    deas.at(index) = value;
}

bool Player::hasDeas() const {
    for (size_t i = 0; i < qtyDea; i++)
    {
        if (getDea(i) != NULL_INT)
        {
            return true;
        }
    }
    return false;
}