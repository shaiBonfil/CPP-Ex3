#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "NumberWithUnits.hpp"

using namespace std;
using namespace ariel;

int main()
{
    ifstream units_file{"shai.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits x{1, "km"};
    NumberWithUnits y{30, "mm"};

    istringstream input;
    string str;
    int user = 1;
    while (user)
    {
        cout << "enter 0 to exit\n 1 to input\n 2 to add numbers\n 3 to check eq" << endl;
        cin >> ws;
        cin >> user;
        switch (user)
        {

        case 0: // exit
            cout << "exiting..." << endl;
            return 1;

        case 1: // input number
            try
            {
                cout << "enter a number and unit with legal format (" << x << ")" << endl;
                cin >> ws; // clean the buffer
                cin >> str;
                input = istringstream{str};
                input >> x;
                cout << x << endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
            catch (const std::invalid_argument &shai)
            {
                std::cerr << shai.what() << '\n';
            }
            break;

        case 2: // add numbers
            try
            {
                cout << (x + y) << endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
            break;

        case 3: // eq of numbers
            try
            {
                if (x == y)
                {
                    cout << "numbers are equal" << endl;
                }
                else
                {
                    cout << "numbers aren't equal" << endl;
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
            break;
        }
    }

    return 0;
}