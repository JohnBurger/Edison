/*
 * Lat.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "Lat.h"

using namespace NMEA0183;

Lat::Lat() :
     Struct(),
     degrees(2, 0, 90),
     minutes(),
     north('S', 'N') {
} // Lat::Lat()

void Lat::Clear() {
    Struct::Clear();
    degrees.Clear();
    minutes = 0.;
    north.Clear();
} // Lat::Clear()

bool Lat::Decode(const char *&line) {
    Clear();

    if (!degrees.Decode(line)) {
        return false;
    } // if
    switch (DecodeReal(line,2,minutes,0.,60.)) {
    case Empty :
        if (degrees.IsValid()) { // If degrees are valid, then the rest is missing!
            return false;
        } // if
        break;
    case Invalid :
        return false;
    case Valid :
        break;
    } // switch
    if (!north.Decode(line)) {
        return false;
    } // if
    valid = degrees.IsValid() &&
            north.IsValid();
    return true;
} // Lat::Decode(line)
