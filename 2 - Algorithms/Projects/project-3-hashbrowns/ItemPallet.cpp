#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "ItemPallet.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int sku) {
  // TODO: implement this function, then delete the return statement below
  int output = sku / 100000 % 10;
  return output;
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int sku) {
   // TODO: implement this function, then delete the return statement below
	int output = sku / 10000 % 10;
  return output;
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int sku) {
   // TODO: implement this function, then delete the return statement below
  int output = sku / 1000 % 10;
  return output;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int sku) {
   // TODO: implement this function, then delete the return statement below
	int output = sku / 100 % 10;
  return output;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int sku) {
    // TODO: implement this function, then delete the return statement below
	int output = sku / 10 % 10;
  return output;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct6(unsigned int sku) {
    // TODO: implement this function, then delete the return statement below
	int output = sku / 1 % 10;
  return output;
}

// Constructor for struct Item
Item::Item(string itemName, unsigned int sku):itemName_(itemName), sku_(sku)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void ItemPallet::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemName;
    unsigned int sku;
    while (myfile >> itemName >> sku) {
			if (itemName.size() > 0)
      	addItem(itemName, sku);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

void ItemPallet::addItem(string itemName, unsigned int sku) {
  // TO BE COMPLETED
  // function that adds the specified SKU to the pallet (i.e., to all hash tables)
 
  Item newItem(itemName, sku);
  hT1[newItem, sku];
  hT2[newItem, sku];
  hT3[newItem, sku];
  hT4[newItem, sku];
  hT5[newItem, sku];
  hT6[newItem, sku];
    
}

bool ItemPallet::removeItem(unsigned int sku) {
   // TODO: implement this function, then delete the return statement below

  // function that removes the pair of glasses specified by the sku from the display
  // if pair is found, then it is removed and the function returns true
  // else returns false
  bool output = false;

  hT1.erase(hT1.find(sku));
  hT2.erase(hT2.find(sku));
  hT3.erase(hT3.find(sku));
  hT4.erase(hT4.find(sku));
  hT5.erase(hT5.find(sku));
  hT6.erase(hT6.find(sku));


    return output;
}

unsigned int ItemPallet::bestHashing() {
  // TODO: implement this function, then delete the return statement below
    
  // function that decides the best has function, i.e. the ones among
  // fct1-fct6 that creates the most balanced hash table for the current
  // ItemPallet data member allItems

	// Hints:
	// Calculate the balance of each hashtable, one by one.
  //=======================================================================
  CustomHashTable palletList [6] = {hT1, hT2, hT3, hT4, hT5, hT6};
  unsigned int output = 0;
  int least [6] = {-1,-1,-1,-1,-1,-1};
  int most [6] = {-1,-1,-1,-1,-1,-1};
  int balance [6] = {};
  for (int i = 0; i < 6; ++i){
    for (int j = 0; j < 10; ++j){
      int size = palletList[i].bucket_size(j);
      if (most[i] == NULL || size > most[i]){
        most[i] = size;
      }
      if (least[i] == -1 || size < least[i]){
        least[i] = size;
      }
    }
    balance[i] = most[i] - least[i];
  }
  for (int k = 0; k < 6; k++){
    if (balance[k] < balance[output]){
      output = k;
    }
  }
  return ++output;
}

// ALREADY COMPLETED
size_t ItemPallet::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) )
  	throw std::length_error("Hash table sizes are not the same");
    
	return hT1.size();
}
