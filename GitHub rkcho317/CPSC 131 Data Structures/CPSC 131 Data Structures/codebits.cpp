#include <iostream>
#include <list>
#include <string>

int main(){

std::list<std::string> zoo = {"Lion", "Tiger", "Monkey","Weasel", "elephant", "Giraffe", "Okapi"};

//std::cout<<*(zoo.begin()+1)<<'\n'; //syntax error

//std::cout<<*(++zoo.begin()) <<'\n';  //Tiger

//std::cout<< zoo.rbegin()[4]<<'\n'; //syntax error

//std::cout<< *(zoo.crend() )<<'\n'; //Lion

//std::cout <<*(zoo.before_begin() ) <<'\n'; //Logic Error

//std::cout<<zoo[std::distance(zoo.begin() + 1, zoo.end() - 3)] <<'\n'; //syntax error

//std::cout<< *(std::next(zoo.begin(),3))<<'\n'; //Weasel

//auto p = zoo.end(); //Giraffe
//std::advance(p,-2);
//std::cout<<*p<<'\n';

//auto p = zoo.rend(); //Elephant
//std::advance(p,-5);
//std::cout<<*p<<'\n';

for (auto p=zoo.rbegin(); p!=zoo.rend();++p){
std::cout<<*p<<'\n';
if(std::advance(p,2) != zoo.rend()) std::next(p,2);
}

}