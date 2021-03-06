/*
 * uart.h
 *
 *   Author: John Burger
 *   This code is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 */

#ifndef uart_h
#define uart_h

#include <termios.h>

class edUART {

public: // Enums

    enum UARTs {
        UART0, UART1, Console
    }; // UARTs

public: // Methods

    edUART(UARTs uart);

    inline bool Valid() const;

    bool Configure(unsigned baud);

    bool CTS() const;

    bool Write(const char *string);

    // Returns number of characters in line (which may not end in \n)
    unsigned ReadLine(char *line, unsigned size);

    void Close();

    ~edUART();

private: // Variables

    int handle;

    termios original;

    termios current;

private: // Methods

    unsigned Copy(char *line, unsigned size);

private: // Variables

    char buffer[256];

    unsigned pos;

    unsigned last;

}; // edUART

inline bool edUART::Valid() const {
    return handle!=-1;
} // edUART::Valid()

#endif // uart_h
