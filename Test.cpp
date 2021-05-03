/**
 * AUTHORS: Shai Bonfil
 * Date: 2021-04
 *
**/

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "doctest.h"
#include "NumberWithUnits.hpp"

using namespace ariel;
using namespace std;

ifstream units_file{"units.txt"};

TEST_CASE("+/+=/-/-= operators")
{
    NumberWithUnits::read_units(units_file);
    NumberWithUnits x{1, "km"};
    NumberWithUnits y{1000, "m"};
    NumberWithUnits u{1, "km"};
    NumberWithUnits s{100, "m"};
    NumberWithUnits z{900, "kg"};
    NumberWithUnits w{3, "ton"};
    NumberWithUnits d1{1, "USD"};
    NumberWithUnits d2{-1, "USD"};
    CHECK_EQ(x + y, NumberWithUnits{2, "km"});
    CHECK_EQ(y + x, NumberWithUnits{2000, "m"});
    CHECK_EQ(w - z, NumberWithUnits{2.100, "ton"});
    for (float i = 1; i < 10; i++)
    {
        CHECK_EQ(x += u, NumberWithUnits{i + 1, "km"});
    }
    for (float i = 900; i > 0; i = i = i - 100)
    {
        CHECK_EQ(y -= s, NumberWithUnits{i, "m"});
    }
    CHECK_EQ(+d1, NumberWithUnits{1, "USD"});
    CHECK_EQ(+d2, NumberWithUnits{-1, "USD"});
    CHECK_EQ(-d1, NumberWithUnits{-1, "USD"});
    CHECK_EQ(-d2, NumberWithUnits{1, "USD"});
    CHECK_NE(+d1, -d1);
    CHECK_THROWS(x + z);
    CHECK_THROWS(x - w);
}

TEST_CASE(">/>=/</<=/==/!= operators")
{
    NumberWithUnits::read_units(units_file);
    CHECK_GT(NumberWithUnits{1, "km"}, NumberWithUnits{100, "m"});
    CHECK_GT(NumberWithUnits{1, "ton"}, NumberWithUnits{100, "kg"});
    CHECK_GE(NumberWithUnits{1, "hour"}, NumberWithUnits{10, "min"});
    CHECK_GE(NumberWithUnits{1, "hour"}, NumberWithUnits{60, "min"});
    CHECK_LT(NumberWithUnits{1, "km"}, NumberWithUnits{2000, "m"});
    CHECK_LT(NumberWithUnits{1, "g"}, NumberWithUnits{2000, "kg"});
    CHECK_LE(NumberWithUnits{1, "hour"}, NumberWithUnits{100, "min"});
    CHECK_LE(NumberWithUnits{1, "hour"}, NumberWithUnits{60, "min"});
    CHECK_NE(NumberWithUnits{1, "m"}, NumberWithUnits{95, "cm"});
    CHECK_NE(NumberWithUnits{1, "kg"}, NumberWithUnits{987, "g"});
    CHECK_EQ(NumberWithUnits{1, "min"}, NumberWithUnits{60, "sec"});
    CHECK_EQ(NumberWithUnits{1, "USD"}, NumberWithUnits{3.33, "ILS"});
    
}

TEST_CASE("++/-- operators")
{
    NumberWithUnits::read_units(units_file);
    NumberWithUnits x{1, "km"};
    NumberWithUnits y{1000, "m"};
    NumberWithUnits z{900, "kg"};
    NumberWithUnits w{3, "ton"};
    CHECK_EQ(x++, NumberWithUnits{1, "km"});
    CHECK_EQ(x, NumberWithUnits{2, "km"});
    CHECK_EQ(++y, NumberWithUnits{1001, "m"});
    CHECK_EQ(y, NumberWithUnits{1001, "m"});
    CHECK_EQ(z--, NumberWithUnits{900, "kg"});
    CHECK_EQ(z, NumberWithUnits{899, "kg"});
    CHECK_EQ(--w, NumberWithUnits{2, "ton"});
    CHECK_EQ(w, NumberWithUnits{2, "ton"});
}

TEST_CASE("x*d/d*x operators")
{
    NumberWithUnits::read_units(units_file);
    NumberWithUnits x{2, "km"};
    CHECK_EQ((x * 2.5), NumberWithUnits{5.0, "km"});
    CHECK_EQ((3.0 * x), NumberWithUnits{6.0, "km"});
}

TEST_CASE("I/O stream operators")
{
    NumberWithUnits test{3, "ton"};
    ostringstream os;
    istringstream is("1 [ kg ]");
    is >> test;
    os << test;
    CHECK_EQ(os.str(), "1, \"kg\"");
}