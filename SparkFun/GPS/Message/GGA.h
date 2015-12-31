//
// GGA.h
//

#ifndef NMEA0183_GGA_h
#define NMEA0183_GGA_h

#include "../Field/Byte.h"
#include "../Field/Word.h"
#include "../Field/Real.h"
#include "../Field/Strings.h"
#include "../Struct/UTC.h"
#include "../Struct/Lat.h"
#include "../Struct/Lon.h"
#include "../Struct/Alt.h"
#include "Message.h"

namespace NMEA0183 {

    // Global Positioning System Fixed Data
    struct GGA : public Message {

    public: // Methods

        GGA();

        bool Match(const char *&line);

        void Clear();

        bool Decode(const char *line);

    public: // Variables

        UTC utc;

        Lat lat;

        Lon lon;

        Strings fix;

        Byte sats;

        Real hdop;

        Alt msl;

        Alt geoid;

        Real age;

        Word id;

    }; // GGA

} // NMEA0183

#endif // NMEA0183_GGA_h
