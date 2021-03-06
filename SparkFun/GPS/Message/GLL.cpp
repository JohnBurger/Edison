/*
 * GLL.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include "GLL.h"

using namespace NMEA0183;

GLL::GLL() :
     Message(),
     lat(),
     lon(),
     utc(),
     status('V', 'A'),
     mode() {
} // GLL::GLL()

void GLL::Clear() {
    Message::Clear();
    lat.Clear();
    lon.Clear();
    utc.Clear();
    status.Clear();
    mode.Clear();
} // GLL::Clear()

bool GLL::Match(const char *&line) {
    return Message::Match(line, "GLL");
} // GLL::Match(line)

bool GLL::Decode(const char *line) {
    Clear();
    if (!lat.Decode(line)) {
        return false;
    } // if
    if (!lon.Decode(line)) {
        return false;
    } // if
    if (!utc.Decode(line)) {
        return false;
    } // if
    if (!status.Decode(line)) {
        return false;
    } // is
    mode.Decode(line); // Optional
    if (!Message::Decode(line)) {
        return false;
    } // if
    Message::valid = true;
    return true;
} // GLL::Decode(line)
