#include <algorithm>    // find(), move(), move_backward(), equal(), swap(), lexicographical_compare()
#include <cstddef>      // size_t
#include <initializer_list>
#include <iomanip>      // setw()
#include <iterator>     // distance(), next()
#include <stdexcept>    // logic_error
#include <string>
#include <vector>

#include "Book.hpp"
#include "BookList.hpp"

#define exception_location "\n detected in function \"" + std::string(__func__) +  "\""    \
                           "\n at line " + std::to_string( __LINE__ ) +                    \
                           "\n in file \"" __FILE__ "\""


/*******************************************************************************
**  Private implementations, types, and objects
*******************************************************************************/
bool BookList::containersAreConsistant() const
{
  // Sizes of all containers must be equal to each other
  if(    _books_array_size != _books_vector.size()
      || _books_array_size != _books_dl_list.size()
      || _books_array_size !=  books_sl_list_size() ) return false;

  // Element content and order must be equal to each other
  auto current_array_position   = _books_array  .cbegin();
  auto current_vector_position  = _books_vector .cbegin();
  auto current_dl_list_position = _books_dl_list.cbegin();
  auto current_sl_list_position = _books_sl_list.cbegin();

  while( current_vector_position != _books_vector.cend() )
  {
    if(    *current_array_position != *current_vector_position
        || *current_array_position != *current_dl_list_position
        || *current_array_position != *current_sl_list_position ) return false;

    // Advance the iterators to the next element in unison
    ++current_array_position;
    ++current_vector_position;
    ++current_dl_list_position;
    ++current_sl_list_position;
  }

  return true;
}



// Calculate the size of the singly linked list on demand
std::size_t BookList::books_sl_list_size() const
{
///////////////////////// TO-DO (1) //////////////////////////////

      if constexpr(true){
      return std::distance(_books_sl_list.cbegin(), _books_sl_list.cend());

      }
      else{
            std::size_t size = 0;
        for (auto current = _books_sl_list.cbegin(); current != _books_sl_list.cend(); ++size,++current );
        return size;
      }

}

/*******************************************************************************
**  Constructors, destructor, and assignment operators
*******************************************************************************/
// Rule of 6 - I wanted a tailored assignment operator, so I should (best practice) write the other too
BookList::BookList()                                     = default;

BookList::BookList( const BookList  & other )            = default;
BookList::BookList(       BookList && other )            = default;

BookList & BookList::operator=( BookList    rhs )        { swap( rhs ); return *this; }
BookList & BookList::operator=( BookList && rhs )        = default;

BookList::~BookList()                                    = default;



BookList::BookList( const std::initializer_list<Book> & initList )
  : _books_vector ( initList.begin(), initList.end() ),
    _books_dl_list( initList.begin(), initList.end() ),
    _books_sl_list( initList.begin(), initList.end() )
{
  // Unlike the other containers that are expandable, the array has a fixed capacity N.  Copy only the first N elements of the
  // initialization list into the array.
  for( auto p = initList.begin();  _books_array_size < _books_array.size()  &&  p != initList.end();   ++_books_array_size, ++p)
  {
    _books_array[_books_array_size] = *p;
  }
}



BookList & BookList::operator+=( const std::initializer_list<Book> & rhs )
{
 ///////////////////////// TO-DO (2) //////////////////////////////


     for(const auto & book : rhs) insert (book, Position::BOTTOM);

  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );
  return *this;
}



BookList & BookList::operator+=( const BookList & rhs )
{

   ///////////////////////// TO-DO (3) //////////////////////////////

  for (const auto & book: rhs._books_sl_list) insert(book,Position::BOTTOM);

  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );
  return *this;
}







/*******************************************************************************
**  Queries
*******************************************************************************/
std::size_t BookList::size() const
{
  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

/*  ///////////////////////// TO-DO (4) ////////////////////////////// */
      return _books_vector.size();

}



std::size_t BookList::find( const Book & book ) const
{
  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  /*///////////////////////// TO-DO (5) //////////////////////////////  */

           if constexpr((true)){
             return std::find(_books_vector.cbegin(), _books_vector.cend(), book) - _books_vector.cbegin();
           }
           else{
             for (std::size_t offset =0; offset < _books_vector.size(); ++offset) if(_books_vector[offset] == book) return offset;

             return _books_vector.size();
           }


}

/*******************************************************************************
**  Mutators
*******************************************************************************/
void BookList::insert( const Book & book, Position position )
{
  // Convert the TOP and BOTTOM enumerations to an offset and delegate the work
  if     ( position == Position::TOP    )  insert( book, 0      );
  else if( position == Position::BOTTOM )  insert( book, size() );
  else throw std::logic_error( "Unexpected insertion position" exception_location );  // Programmer error.  Should never hit this!
}



void BookList::insert( const Book & book, std::size_t offsetFromTop )       // insert new book at offsetFromTop, which places it before the current book at offsetFromTop
{

  if( offsetFromTop > size() ) throw InvalidOffset_Ex( "Insertion position beyond end of current list size" exception_location );


  /**********  Prevent duplicate entries  ***********************/
  ///////////////////////// TO-DO (6) //////////////////////////////


  if(find(book) != size() ){
    return;
  }



  /**********  Insert into array  ***********************/

    ///////////////////////// TO-DO (7) //////////////////////////////

    {

      if (_books_array_size >= _books_array.size()){
        throw CapacityExceeded_Ex("Capacity Exceeded" exception_location);
      }

        std::move_backward(_books_array.begin()+offsetFromTop, _books_array.begin() + _books_array_size, _books_array.begin() + _books_array_size + 1 );

      _books_array[offsetFromTop] = book;
      ++_books_array_size;

  }



  /**********  Insert into vector  **********************/
  {
    ///////////////////////// TO-DO (8) //////////////////////////////


    //Advanced _books_vector.begin() offsetFromTop times
    //std::next(_books_vector.begin(),offsetFromTop);

    //_books_vector.push_back(book);

    _books_vector.insert(_books_vector.begin() + offsetFromTop, book);

  }



  /**********  Insert into doubly linked list  **********/
  {
    ///////////////////////// TO-DO (9) //////////////////////////////

      //  std::next(_books_dl_list.begin(),offsetFromTop);

        //_books_dl_list.push_back(book);

        _books_dl_list.insert(std::next(_books_dl_list.begin(),offsetFromTop),book);

  }



  /**********  Insert into singly linked list  **********/
  {
    ///////////////////////// TO-DO (10) //////////////////////////////

    //  std::next(_books_sl_list.begin(), offsetFromTop, book);

      _books_sl_list.insert_after(std::next(_books_sl_list.before_begin(), offsetFromTop), book);
  }

  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );
} // insert( const Book & book, std::size_t offsetFromTop )



void BookList::remove( const Book & book )
{
  remove( find( book ) );
}



void BookList::remove( std::size_t offsetFromTop )
{

  if( offsetFromTop >= size() ) return;                                            // no change occurs if (zero-based) offsetFromTop >= size()

  /**********  Remove from array  ***********************/
  {
    ///////////////////////// TO-DO (11) //////////////////////////////

      std::move(_books_array.begin() + offsetFromTop+1, _books_array.begin() + _books_array_size, + _books_array.begin() + offsetFromTop);
      --_books_array_size;
      _books_array[_books_array_size] = {};

  }



  /**********  Remove from vector  **********************/
  {
    ///////////////////////// TO-DO (12) //////////////////////////////

  //  std::next(_books_vector.begin(),offsetFromTop);
    _books_vector.erase(_books_vector.begin()+offsetFromTop);
  }



  /**********  Remove from doubly linked list  **********/
  {

  //  std::next(_books_dl_list.begin(),offsetFromTop);
  //  _books_dl_list.pop_back();
  _books_dl_list.erase(std::next(_books_dl_list.begin(), offsetFromTop));
  }



  /**********  Remove from singly linked list  **********/
  {
     ///////////////////////// TO-DO (14) //////////////////////////////

    //std::next(_books_sl_list.begin(),offsetFromTop);
    _books_sl_list.erase_after(_books_sl_list.begin());


  }

  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );
}



void BookList::moveToTop( const Book & book )
{
   ///////////////////////// TO-DO (15) //////////////////////////////

  find(book);

  if(find(book) != _books_array_size ){
    remove(book);
    insert(book);
  }


}



void BookList::swap( BookList & rhs ) noexcept
{
  if( this == &rhs ) return;

  _books_array  .swap( rhs._books_array   );
  _books_vector .swap( rhs._books_vector  );
  _books_dl_list.swap( rhs._books_dl_list );
  _books_sl_list.swap( rhs._books_sl_list );

  std::swap( _books_array_size, rhs._books_array_size );
}












/*******************************************************************************
**  Insertion and Extraction Operators
*******************************************************************************/
std::ostream & operator<<( std::ostream & stream, const BookList & bookList )
{
  if( !bookList.containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  unsigned count = 0;
  for( const auto & book : bookList._books_sl_list )   stream << '\n' << std::setw(5) << count++ << ":  " << book;

  return stream;
}



std::istream & operator>>( std::istream & stream, BookList & bookList )
{
  if( !bookList.containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  for( Book book; stream >> book; )   bookList.insert( book, BookList::Position::BOTTOM );

  return stream;
}












/*******************************************************************************
**  Relational Operators
*******************************************************************************/
bool operator==( const BookList & lhs, const BookList & rhs )
{
  return !( lhs < rhs )  &&  !( rhs < lhs );
}



bool operator<( const BookList & lhs, const BookList & rhs )
{
  if( !lhs.containersAreConsistant() || !rhs.containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  // comparing arrays using std::array::operator==() will compare every element in the array (which is usually what you want).  But
  // in this case, only the first N elements are valid, so compare only those elements.  This is implicitly handled in the other
  // containers because size() and end() are already adjusted for only the valid elements.
  auto begin_lhs = lhs._books_array.cbegin();
  auto begin_rhs = rhs._books_array.cbegin();

  auto end_lhs   = begin_lhs + lhs._books_array_size;
  auto end_rhs   = begin_rhs + rhs._books_array_size;

  // C++20's spaceship operator should optimize this algorithm, but for now ...
  if( !std::equal( begin_lhs, end_lhs, begin_rhs, end_rhs ) )  return std::lexicographical_compare ( begin_lhs, end_lhs, begin_rhs, end_rhs );
  if( lhs._books_vector  != rhs._books_vector               )  return lhs._books_vector  < rhs._books_vector;
  if( lhs._books_dl_list != rhs._books_dl_list              )  return lhs._books_dl_list < rhs._books_dl_list;
  if( lhs._books_sl_list != rhs._books_sl_list              )  return lhs._books_sl_list < rhs._books_sl_list;

  // At this point, all attributes are equal to each other, so the lhs cannot be less than the rhs
  return false;
}

bool operator!=( const BookList & lhs, const BookList & rhs ) { return !( lhs == rhs ); }
bool operator<=( const BookList & lhs, const BookList & rhs ) { return !( rhs  < lhs ); }
bool operator> ( const BookList & lhs, const BookList & rhs ) { return  ( rhs  < lhs ); }
bool operator>=( const BookList & lhs, const BookList & rhs ) { return !( lhs  < rhs ); }
