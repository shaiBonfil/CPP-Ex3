#pragma once

#include <iostream>
#include <string>

namespace ariel
{

    class NumberWithUnits
    {

    private:
        double number;
        std::string unit_type;

    public:
        NumberWithUnits(double number, const std::string &unit_type);

        ~NumberWithUnits() {}

        static void read_units(std::ifstream &units_file);

        // Overloading +/+=/-/-= operators
        NumberWithUnits operator+(const NumberWithUnits &other) const;
        NumberWithUnits &operator+=(const NumberWithUnits &other);
        NumberWithUnits operator-(const NumberWithUnits &other) const;
        NumberWithUnits &operator-=(const NumberWithUnits &other);
        NumberWithUnits operator+(); // + unary
        NumberWithUnits operator-(); // - unary

        // Overloading >/>=/</<=/==/!= operators
        bool operator==(const NumberWithUnits &num) const;
        bool operator!=(const NumberWithUnits &num) const;
        bool operator>(const NumberWithUnits &num) const;
        bool operator>=(const NumberWithUnits &num) const;
        bool operator<(const NumberWithUnits &num) const;
        bool operator<=(const NumberWithUnits &num) const;

        // Overloading ++/-- operators
        NumberWithUnits &operator++();
        NumberWithUnits &operator--();
        NumberWithUnits operator++(int bulshit);
        NumberWithUnits operator--(int bulshit);

        // Overloading multiplication x*d/d*x operators
        NumberWithUnits operator*(double f);
        friend NumberWithUnits operator*(double f, const NumberWithUnits &num);

        // Overloading I/O stream operators
        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &num);
        friend std::istream &operator>>(std::istream &is, NumberWithUnits &num);
    };
}