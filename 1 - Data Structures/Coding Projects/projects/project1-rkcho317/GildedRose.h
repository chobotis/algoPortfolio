#pragma once

#include <string>
using std::string;

#include<vector>
using std::vector;

#include<stddef.h>

#include<iostream>

// This is already done for you...
class Item {
public:
    string name;
    int sellIn;
    int quality;
    Item(string, int, int);
};

//Item Constructor
Item::Item(string new_name, int new_sellIn, int new_quality)
: name(new_name), sellIn(new_sellIn), quality(new_quality)
{
    new_name = name;
    new_sellIn = sellIn;
    new_quality = quality;
}


// This class is incomplete...
class GildedRose {
private:
    // Add something to hold at least 10 items
	vector <Item> inventory;

public:
    //Constructor
    GildedRose() = default;

    //Destructor
    ~GildedRose() {
        inventory.clear();
    };

    size_t size() const {
	    return inventory.size();
    };

    Item& get(size_t) {
        int i;
	    return inventory[i];
    };

    void add(const Item & temp) {
        inventory.push_back(temp);
    };

    Item& operator[](size_t) {
        int i;
        return inventory[i;
    };


};
