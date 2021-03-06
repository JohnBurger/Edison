/*
 * Date.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "Date.h"

using namespace NMEA0183;

Date::Date() :
      Struct(),
      day  (),
      month(),
      year () {
} // Date::Date()

bool Date::Decode(const char *&line) {
    Clear();
    if (!Struct::Decode(line)) {
        return false;
    } // if

    switch (DecodeByte(line,2,day,1,31)) {
    case Empty :
        return true; // Is truly Empty
    case Invalid :
        return false;
    case Valid :
        break;
    } // switch

    switch (DecodeByte(line,2,month,1,12)) {
    case Empty : // Is partially Empty
    case Invalid :
        return false;
    case Valid :
        break;
    } // switch

    switch (DecodeByte(line,2,year,0,99)) {
    case Empty : // Is partially Empty
    case Invalid :
        return false;
    case Valid :
        break;
    } // switch

    valid = true;
    return true;
} // Date::Decode(line)
