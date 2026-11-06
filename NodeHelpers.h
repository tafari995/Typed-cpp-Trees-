#include <iostream>
#include <string>
#include <type_traits>
#include <cstddef>
#include <functional>
using namespace std;


template <class T>
const std::string get_string(const T value);


// turns value of type T into a string, if it's not one already
template <class T>
const std::string get_string(const T value)
{
  if constexpr (std::is_same_v<T, std::string>) {
    return value; 
  } 
  else {
    return std::to_string(value); 
  }
};