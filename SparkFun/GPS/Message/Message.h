//
// Message.h
//

#ifndef NMEA0183_Message_h
#define NMEA0183_Message_h

#include "../Struct/Struct.h"

namespace NMEA0183 {

    // This is the generic NMEA0183 Message
    struct Message : public Struct {

    public: // Static methods

        static bool Valid(const char *&line);

        static bool Checksum(const char *line);

    protected: // Methods

        Message();

        // Only updates line if msg Matches
        bool Match(const char *&line, const char *msg);

        // Default End-of-Message decoding
        bool Decode(const char *line);

    }; // Message

} // NMEA0183

#endif // NMEA0183_Message_h
