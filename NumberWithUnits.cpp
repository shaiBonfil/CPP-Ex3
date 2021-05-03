#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;

namespace ariel
{

    static map<string, map<string, double>> _map;

    int unitValidity(const string &unit_type)
    {
        return (_map.count(unit_type));
    }

    NumberWithUnits::NumberWithUnits(double num, const string &unit_type)
    // : number(num), unit_type(unit_type),
    {
        if (unitValidity(unit_type) != 0)
        {
            this->number = num;
            this->unit_type = unit_type;
        }
        else
        {
            throw invalid_argument("illegal unit!\n");
        }
    }

    double convert(const string &src, const string &dst, double num)
    {
        if (src == dst)
        {
            return num;
        }

        map<string, double> _inner = _map[src];
        map<string, double>::iterator it = _inner.find(dst);

        if (it == _inner.end())
        {
            throw invalid_argument("can't convert, units doesn't match!\n");
        }

        return _map[dst][src] * num;
    }

    void addUnits()
    {
        for (auto &k : _map)
        {
            for (auto &i : _map)
            {
                for (auto &j : _map)
                {
                    if ((_map[k.first].count(i.first) != 0) && (_map[k.first].count(j.first) != 0) 
                            && (j.first != i.first) && (j.first != k.first))
                    {
                        _map[i.first][j.first] = _map[i.first][k.first] * _map[k.first][j.first];
                        _map[j.first][i.first] = 1 / _map[i.first][j.first];
                    }
                }
            }
        }
    }

    void NumberWithUnits::read_units(ifstream &units_file)
    {
        string u1, u2, eq;
        double n1 = 0, n2 = 0;

        while (units_file >> n1 >> u1 >> eq >> n2 >> u2)
        {
            if ((n1 == 1) && (eq == "=") && (n2 > 0))
            {
                _map[u1][u2] = n2;
                _map[u2][u1] = 1 / n2;
            }
            else
            {
                throw invalid_argument("format error!\n");
            }
        }
        addUnits();
    }

    // Overloading +/+=/-/-= operators
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &other) const
    {
        double tmp = convert(this->unit_type, other.unit_type, other.number);
        return NumberWithUnits(this->number + tmp, this->unit_type);
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &other)
    {
        this->number += convert(this->unit_type, other.unit_type, other.number);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &other) const
    {
        double tmp = convert(this->unit_type, other.unit_type, other.number);
        return NumberWithUnits(this->number - tmp, this->unit_type);
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &other)
    {
        this->number -= convert(this->unit_type, other.unit_type, other.number);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator+()
    {
        return NumberWithUnits(this->number, this->unit_type);
    }

    NumberWithUnits NumberWithUnits::operator-()
    {
        return NumberWithUnits(-this->number, this->unit_type);
    }

    // Overloading >/>=/</<=/==/!= operators
    const float TOLERANCE = 0.001;

    bool NumberWithUnits::operator>(const NumberWithUnits &num) const
    {
        double tmp = convert(this->unit_type, num.unit_type, num.number);
        return (this->number - tmp) > TOLERANCE;
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &num) const
    {
        return (!(*this < num));
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &num) const
    {
        return (num > *this);
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &num) const
    {
        return (!(*this > num));
    }

    bool NumberWithUnits::operator==(const NumberWithUnits &num) const
    {
        return ((!(*this > num)) && (!(*this < num)));
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &num) const
    {
        return (!(*this == num));
    }

    // Overloading ++/-- operators
    NumberWithUnits &NumberWithUnits::operator++()
    {
        this->number++;
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator--()
    {
        --(this->number);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int bulshit)
    {
        NumberWithUnits copy = *this;
        this->number++;
        return copy;
    }

    NumberWithUnits NumberWithUnits::operator--(int bulshit)
    {
        NumberWithUnits copy = *this;
        (this->number)--;
        return copy;
    }

    // Overloading multiplication x*d/d*x operators
    NumberWithUnits NumberWithUnits::operator*(double f)
    {
        return NumberWithUnits(this->number * f, this->unit_type);
    }

    NumberWithUnits operator*(double f, const NumberWithUnits &num)
    {
        return NumberWithUnits(num.number * f, num.unit_type);
    }

    // Overloading I/O stream operators
    ostream &operator<<(ostream &os, const NumberWithUnits &num)
    {
        os << num.number << "[" << num.unit_type << "]";
        return os;
    }

    istream &operator>>(istream &is, NumberWithUnits &num)
    {
        string str;
        string n1;
        string unit;
        int flag = 0;
        int counter = 0;

        getline(is, str, ']');

        for (size_t i = 0; i < str.length(); i++)
        {
            if (str[i] == ' ')
            {
                continue;
            }
            if (('A' <= str[i] && str[i] <= 'Z') || ('a' <= str[i] && str[i] <= 'z') || (str[i] == '_'))
            {
                if (flag == 1)
                {
                    unit += str[i];
                }
                else
                {
                    throw invalid_argument("format error! enter '[' before letter\n");
                }
            }
            if (str[i] == '[')
            {
                flag = 1;
                counter++;
                if (counter >= 2)
                {
                    throw invalid_argument("format error! two brackets '[['\n");
                }
            }
            if (('0' <= str[i] && str[i] <= '9') || '+' == str[i] || '-' == str[i] || '.' == str[i])
            {
                if (flag == 0)
                {
                    n1 += str[i];
                }
                else
                {
                    throw invalid_argument("format error! '[' before number\n");
                }
            }
        }

        if (unitValidity(unit) != 0)
        {
            num = NumberWithUnits(stod(n1), unit);
            return is;
        }

        throw invalid_argument(unit + " is invalid unit!\n");
    }
}