///////////////////////////////////////////////////////////////////////////////
// disks.hpp
//
// Definitions for two algorithms that each solve the alternating disks
// problem.
//
// As provided, this header has four functions marked with TODO comments.
// You need to write in your own implementation of these functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

// TODO
#include <functional>
#include <iostream>

enum disk_color { DISK_DARK, DISK_LIGHT};

class disk_state {
private:
  std::vector<disk_color> _colors;

public:
  disk_state(size_t light_count)
    : _colors(light_count * 2, DISK_DARK) {

    assert(light_count > 0);

    for (size_t i = 1; i < _colors.size(); i += 2) {
      _colors[i] = DISK_LIGHT;
    }
  }

  bool operator== (const disk_state& rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {
    return _colors.size();
  }

  size_t light_count() const {
    return total_count() / 2;
  }

  size_t dark_count() const {
    return light_count();
  }

  bool is_index(size_t i) const {
    return (i < total_count());
  }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

  // Return true when this disk_state is in alternating format. That means
  // that the first disk at index 0 is dark, the second disk at index 1
  // is light, and so on for the entire row of disks.
  bool is_initialized() const {
      bool initialized = true ;
      for (int i = 0; i < total_count(); i++) {
          //if even element isn't dark:
          if (i % 2 == 0 && get(i) != DISK_DARK) {          
              return false;
           }
          //if odd element isn't light 
          else if (i % 2 != 0 && get(i) != DISK_LIGHT) {
              return false;
          }
      }
      return initialized;
  }

  // Return true when this disk_state is fully sorted, with all dark disks
  // on the left (low indices) and all light disks on the right (high
  // indices).
  bool is_sorted() const {
      bool sorted = true;
      for (int i = 0; i < total_count(); i++) {
          // if a light disk is on the left:
          if (i < light_count() && get(i) == DISK_LIGHT) {              
              sorted = false;
              break;
          }
          // if a dark disk is on the right:
          else if (i >= dark_count() && get(i) == DISK_DARK) {
              sorted = false;
              break;
          }
      }
      return sorted; 
  }
};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;
  
public:
  
  sorted_disks(const disk_state& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }
  
  sorted_disks(disk_state&& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }
  
  const disk_state& after() const {
    return _after;
  }
  
  unsigned swap_count() const {
    return _swap_count;
  }
};

// Algorithm that sorts disks using the alternate algorithm.
sorted_disks sort_alternate(const disk_state& before) {
  disk_state after = before;
  int swap = 0;
  for (int i = 0; i < after.light_count(); i++){
  // i = n runs
    for (int k = i; k+1 < after.total_count(); k+=2){
    //k = iterating over pairs
      if (after.get(k) == DISK_LIGHT && after.get(1+k) == DISK_DARK){
        after.swap(k);
        swap++;
      }
    }
  }
  return sorted_disks(after, swap);
}


// Algorithm that sorts disks using the lawnmower algorithm.
sorted_disks sort_lawnmower(const disk_state& before) {
  disk_state after = before;
  unsigned int swap = 0;
  for (int i = 0; i < (after.light_count() / 2); i++){
  // i = n/2 runs
    for (int j = 0; j < (after.total_count() - 2); j++){
    // j = iterate to the rightmost disk - 1
      if (after.get(j) == DISK_LIGHT && after.get(j+1) == DISK_DARK){
      // swap if [j] is light and the disk to its right is dark
        after.swap(j);
        swap++;
        j++; //jumps to the next element. Necessary?
      }
    }
    for (int k = (after.total_count() - 1); k > 0; k--){
    // k = from rightmost disk to leftmost, descending
      if (after.get(k) == DISK_DARK && after.get(k-1) == DISK_LIGHT){
      // swap if [k] is dark and the disk to its left is light
        after.swap(k-1);
        swap++;
        k--;  //jumps to the next element. Necessary?
      }
    }
  }
  return sorted_disks(after, swap);
}