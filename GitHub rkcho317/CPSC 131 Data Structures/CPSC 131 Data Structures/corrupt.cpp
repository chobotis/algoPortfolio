#include <iostream>
#include <string>
#include <vector>

int main() {
std::vector<std::string> rainbow = {"Red", "Orange", "Yellow", "Green", "Blue", "Indigo", "Purple"};

//std::cout<< *(rainbow.begin() + 2) <<'\n';

//std::cout<< rainbow.rbegin()[3]<<'\n';

//std::cout<<*(rainbow.cend() )<<'\n';

//std::cout<<*(rainbow.before_begin() ) <<'\n';

//std::cout<<rainbow[std::distance(rainbow.begin()+1, rainbow.end()-2)]<<'\n';

//std::cout<<*(std::next(rainbow.begin(),5))<<'\n';

//std::cout<<*(rainbow.begin()+5)<<'\n'; [Not on the quiz but has the same result as #6 aka ^) 

//auto p = rainbow.end();
//std::advance(p,-5);
//std::cout<<*p<<'\n';

auto p = rainbow.rend();
std::advance(p,2);
std::cout<<*p<<'\n';

return 0;
}