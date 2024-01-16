#include <iostream>
#include <forward_list>
#include <string>


int main(){

std::forward_list<std::string> desert = {"Cake", "Ice Cream", "Pudding", "Pizookie", "Apple Crisp", "S'mores", "Pie"};

//std::cout<<*( desert.begin() + 1)<<'\n'; //styn error

//std::cout<<*( ++desert.begin())<<'\n';  //ice cream

//std::cout << desert.rbegin()[4]<<'\n'; //syntax error

//std::cout<< *(desert.crend() ) <<'\n'; //syntax error

//std::cout<<*(desert.before_begin() ) <<'\n'; //cake

//std::cout<<desert[std::distance(desert.begin() + 1, desert.end() - 3)] <<'\n'; //cake

//std::cout<<*(std::next(desert.begin(),3))<<'\n'; //Pizookie

//auto p = desert.end(); //syntax error
//std::advance(p,-2);
//std::cout<<*p<<'\n';

auto p = desert.rend(); //syntax error
std::advance(p,-5);
std::cout<<*p<<'\n';



return 0;
}
