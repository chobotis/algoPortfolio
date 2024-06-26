#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <iomanip>
#include <iostream>

#include "Book-2.hpp"

namespace
{
  const double EPSILON = 1.0E-4;
}//namespace with EPSILON

//Book Constructor
Book::Book( std::string_view title,
            std::string_view author,
            std::string_view isbn,
            double           price)
  {
    _title = title;
    _author = author;
    _isbn = isbn;
    _price = price;

  }//default Constructor

//Book Queries
std::string Book::isbn  () const { return _isbn;   }
std::string Book::title () const { return _title;  }
std::string Book::author() const { return _author; }
double Book::price      () const { return _price;  }

//Book Mutators
void Book::isbn (std::string_view newIsbn)
{
  _isbn = newIsbn;
}//mutator isbn
void Book::title (std::string_view newTitle)
{
  _title = newTitle;
}//mutator title
void Book::author( std::string_view newAuthor )
{
  _author = newAuthor;
}//mutator author
void Book::price (double newPrice)
{
_price = newPrice;
}//mutator price

std::ostream & operator<<( std::ostream & stream, const Book & book )
{
  const std::string delimiter = ", ";

  stream << std::quoted(book.isbn()) << delimiter
         << std::quoted(book.title()) << delimiter
         << std::quoted(book.author())<< delimiter
         << book.price();

  return stream;
}//extraction operator

std::istream & operator>>( std::istream & stream, Book & book )
{
  Book workingItem;
  char delimiter = ',';

  stream >> std::quoted( workingItem._isbn  ) >> delimiter
         >> std::quoted( workingItem._title ) >> delimiter
         >> std::quoted( workingItem._author) >> delimiter
         >> workingItem._price;

  if (stream) book = std::move(workingItem);

  return stream;
}//insertion operator

bool operator==(const Book & lhs, const Book & rhs)
{
  if constexpr((false))
  {
    return !(lhs < rhs) && !(rhs < lhs);
  }//preliminary if statement
  else
  {
    return lhs._isbn == rhs._isbn && lhs._title == rhs._title
      && lhs._author == rhs._author
      && (std::abs(lhs._price - rhs._price) < EPSILON
      || std::abs(rhs._price - lhs._price) < EPSILON);
  }//preliminary else statement

}//bool == operator

bool operator< ( const Book & lhs, const Book & rhs )
{
  if (auto result = lhs._isbn.compare(rhs._isbn); result != 0) return result < 0;
  if (auto result = lhs._author.compare(rhs._author); result != 0) return result < 0;
  if (auto result = lhs._title.compare(rhs._title); result != 0) return result < 0;
  if (std::abs(lhs._price - rhs._price) >= EPSILON) return lhs._price < rhs._price;

  return false;
}//bool operator <

bool operator!=( const Book & lhs, const Book & rhs )
{
  return !(lhs == rhs);
}//bool operator !=
bool operator<=( const Book & lhs, const Book & rhs )
{
  return !(rhs < lhs);
}//bool opeartor <=
bool operator> ( const Book & lhs, const Book & rhs )
{
  return rhs < lhs;
}//bool operator >
bool operator>=( const Book & lhs, const Book & rhs )
{
  return !(lhs < rhs);
}//bool operator >=
