/*
 * uart.cpp
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>
#include <string.h>

#include "uart.h"

static const char * const name[] = { "/dev/ttyMFD0", "/dev/ttyMFD1", "/dev/ttyMFD2" };

edUART::edUART(UARTs uart) :
        handle(::open(name[uart], O_RDWR)),
        original(),
        current(),
        buffer(),
        pos(0),
        last(0) {
    if (!Valid()) {
        return;
    } // if
    ::tcgetattr(handle, &original);
    current = original;

    ::cfmakeraw(&current);
    current.c_cc[VMIN] = 0;
    current.c_cc[VTIME] = 0;
    ::tcsetattr(handle, TCSANOW, &current);
} // edUART::edUART(UARTs)

bool edUART::Configure(unsigned baud) {
    if (!Valid()) {
        return false;
    } // if
    if (::cfsetspeed(&current, baud)!=0) {
        return false;
    } // if
    if (::tcsetattr(handle, TCSANOW, &current)!=0) {
        return false;
    } // if
    return true;
} // edUART::Configure(baud)

bool edUART::CTS() const {
    if (!Valid()) {
        return false;
    } // if
    int pins;
    if (::ioctl(handle,TIOCMGET,&pins) == -1) {
        return false;
    } // if
    return (pins & TIOCM_CTS)!=0;
} // edUART::CTS()

bool edUART::Write(const char *string) {
    int len = ::strlen(string);
    return Valid() &&
           ::write(handle, string, len)==len;
} // edUART::Write(string)

unsigned edUART::Copy(char *line, unsigned size) {
    unsigned index = 0;
    while (index<pos && size-->0) {
        *line++ = buffer[index++];
    } // while
    if (size>0 && buffer[pos]=='\n') {
        *line++ = buffer[pos++];
        ++index;
        --size;
    } // if
    ::memcpy(&buffer[0], &buffer[pos], last-pos);
    last -= pos;
    pos = 0;
    return index;
} // edUART::Copy(line,size)

unsigned edUART::ReadLine(char *line, unsigned size) {
    for (;;) {
        while (pos<last) {
            if (buffer[pos]!='\n') {
                ++pos;
                continue;
            } // if
            return Copy(line,size);
        } // while
        unsigned len = sizeof buffer - last;
        if (len == 0) {
            return Copy(line, size);
        } // if
        int num = ::read(handle, &buffer[last], len);
        if (num<=0) {
            return 0;
        } // if
        last += num;
    } // for
    return 0;
} // edUART::ReadLine(line,size)

void edUART::Close() {
    if (!Valid()) {
        return;
    } // if
    ::tcsetattr(handle, TCSANOW, &original);
    ::close(handle);
} // edUART::Close()

edUART::~edUART() {
    Close();
} // edUART::~edUART()
