#pragma once

#include <string>
#include <vector>

class Player
{
private:
    std::string name;
    std::vector<int> deas;
    int qtyDea;
    int eliminated;
public:
    Player(std::string new_name);
    ~Player();
    std::string info() const;
    std::string getName() const { return name;}
    bool hasDeas()const;
    int getDea(int index) const;
    std::vector<int> getDeas() const { return deas;}
    void setDea(int index, int value);
    void addDea(int value);
    void removeDea();
    int getQt() const{return qtyDea;}
    void setQt(int value) { qtyDea = value;}
    int getEliminated() const { return eliminated;}
    void setEliminated(int value) { eliminated = value;}
};