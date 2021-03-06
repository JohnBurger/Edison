/*
 * Bool.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "Bool.h"

using namespace NMEA0183;

Bool::Bool(char no, char yes) :
      Field(),
      no(no),
      yes(yes),
      value() {
} // Bool::Bool(no, yes)

bool Bool::Decode(const char *&line) {
    Clear();

    if (!Field::Decode(line)) {
        return false;
    } // if
    char c = *line++;
    if (c==no) {
        value = false;
        valid = true;
        return true;
    } // if
    if (c==yes) {
        value = true;
        valid = true;
        return true;
    } // if

    switch (c) {
    case ',' :
    case '*' :
        --line;
        return true;
    default :
        break;
    } // switch
    return false;
} // Bool::Decode(line)
