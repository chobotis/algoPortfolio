#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <cstddef>

#include "Book.hpp"

int main(){
  /*
  Function main() to use the Book class above:
    Read a book 7 from standard input (std::cin) until end of file 8 . For each book read:
    Store the book in a dynamically allocated object
    Store the pointer to the book in a standard vector
    After you have reached the end of file, write the books to standard output (std::cout) in reverse
  order.
    Be sure to release the dynamically allocated objects before exiting the program
  */


  //Enter attributes for new Book object
    std::cout << std::showpoint << std::fixed << std::setprecision(2)
    <<"Welcome"
    << "Press ctrl-z or ctrl-d to quit";

    //Create empty collections of smart objects
    std::vector<std::unique_ptr<Book>> books;

    //Storing and Creating a dynamically allocated object
    Book book;
    while(std::cout <<"Enter ISBN, TITLE, AUTHOR, and PRICE\n", std::cin>>book)
    {
      books.emplace_back( std::make_unique<Book>(std::move(book)) );
      std::cout << "Item added to books: "  << *books.back() << "\n\n";
    }


   for(auto p=books.rbegin(); p != books.rend(); ++p)
   {
      std::cout<< **p <<'\n';
   }


    for(std::size_t index = books.size(); index > 0; --index)
    {
      std::cout << *books[index -1] << '\n';
    }

    return 0;

}
