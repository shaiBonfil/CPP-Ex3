/**
 * Demo file for the exercise on numbers with units
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include <string>
#include "NumberWithUnits.hpp"
#include "NumberWithUnits.cpp"
#include <assert.h>
using namespace ariel;

int main()
{
  // ifstream units_file{"units.txt"};
  // NumberWithUnits::read_units(units_file);

  // NumberWithUnits a{2, "km"};   // 2 kilometers
  // cout << a << endl;           // Prints "2[km]".
  // cout << (-a) << endl;    // Prints "-2[km]"
  // cout << (3*a) << endl;    // Prints "6[km]"

  // NumberWithUnits b{300, "m"};  // 300 meters
  // cout << (a+b) << endl;   // Prints "2.3[km]". Note: units are determined by first number (a).
  // cout << (b-a) << endl;   // Prints "-1700[m]". Note: units are determined by first number (b).

  // cout << boolalpha; // print booleans as strings from now on:
  // cout << (a>b) << endl;  // Prints "true"
  // cout << (a<=b) << endl;  // Prints "false"
  // cout << (a==NumberWithUnits{2000, "m"}) << endl;  // Prints "true"

  // istringstream sample_input{"700 [ kg ]"};
  // sample_input >> a;
  // cout << a << endl;   // Prints "700[kg]"
  // cout << (a += NumberWithUnits{1, "ton"}) << endl;  // prints "1700[kg]"
  // cout << a << endl;   // Prints "1700[kg]". Note that a has changed.

  // try {
  //   cout << (a+b) << endl;
  // } catch (const std::exception& ex) {
  //   cout << ex.what() << endl; // Prints "Units do not match - [m] cannot be converted to [kg]"
  // }
  // cout << "End of demo!" << endl;
  ifstream units_file{"shai.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits a{1, "km"};
  NumberWithUnits b{100000, "cm"};
  NumberWithUnits x{1, "km"};
  cin >> x;
  cout << "x2: " << x << endl;
  // NumberWithUnits c{1000, "m"};
  // cout << a << endl;
  // cout << b << endl;
  // cout << c << endl;
  // cout << a + c << endl;
  // cout << a + b << endl;
  // NumberWithUnits f{2, "km"};
  // NumberWithUnits g{2000, "m"};
  // cout << ((a+c)==f) << endl;
  // cout << ((a+b)==g) << endl;

  // assert(a==b);
  // cout << (a==b) << endl;

  return 0;
} // clang++-9 -c NumberWithUnits.cpp                 ./demo
// clang++-9 -std=c++2a -o demo Demo.cpp NumberWithUnits.o
