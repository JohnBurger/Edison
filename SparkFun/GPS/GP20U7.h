//
// GP20U7.h
//

#ifndef GP20U7_h
#define GP20U7_h

#include "Message/GGA.h"
#include "Message/GLL.h"
#include "Message/GSA.h"
#include "Message/GSV.h"
#include "Message/RMC.h"
#include "Message/VTG.h"

// Data generated by GP-20U7 GPS chipset
class GP20U7 {

public: // Enums

    // These are the different messages that can be decoded for NMEA-0183
    enum Messages {
        INV_Invalid,           // Completely invalid syntax
        CHK_Checksum,          // Sufficiently correct to calculate checksum - but it failed
        XXX_Unknown,           // A valid message - but unknown type

        GGA_FixedData,         // UTC, Lat, Long, valid, HDoP, #Sats, Alt, Separation; Differential
        GLL_LatLong,           // Lat, Long, UTC, valid
        GSA_DilutionPrecision, // Mode, 2D/3D, {Sat#}[12], PDoP, HDoP, VDoP
        GSV_SatsView,          // #Sats, {Sat#, El, Az, S/NR}[4]
        RMC_MinimumData,       // UTC, valid, Lat, Long, Speed, Course, Date, MagVar
        VTG_CourseSpeed,       // Course (true), Course (Magnetic), Speed (knots), Speed (kph)

        GGA_Invalid,           // These are returned if there's a parse error
        GLL_Invalid,           // while decoding the advertised packet type
        GSA_Invalid,
        GSV_Invalid,
        RMC_Invalid,
        VTG_Invalid,

        GP20U7_Last,
        GP20U7_Start = GGA_FixedData,
        GP20U7_End   = VTG_CourseSpeed
    }; // Messages

public: // Methods

    // Storage for current NMEA0183 state
    GP20U7();

    // Update state by decoding line
    // Returns decoded message type
    Messages Decode(const char *line);

    NMEA0183::GGA gga;

    NMEA0183::GLL gll;

    NMEA0183::GSA gsa;

    NMEA0183::GSV gsv;

    NMEA0183::RMC rmc;

    NMEA0183::VTG vtg;

}; // GP20U7

#endif // GP20U7_h
