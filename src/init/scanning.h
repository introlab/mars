#ifndef __MARS_INIT_SCANNING
#define __MARS_INIT_SCANNING

    #include "../signal/scan.h"
    #include "../signal/soundspeed.h"
    #include "../signal/mic.h"
    #include "../signal/map.h"
    #include "../signal/tau.h"
    #include "../init/space.h"
    #include "../init/delay.h"
    #include "../init/hit.h"
    #include "../init/linking.h"

    scans_obj * scanning_init_sphere(const mics_obj * mics, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const soundspeed_obj * soundspeed, const float ratioMatch, const unsigned int frameSize, const signed int * deltas, const float probMin, const unsigned int nRefineLevels);

    scans_obj * scanning_init_halfsphere(const mics_obj * mics, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const soundspeed_obj * soundspeed, const float ratioMatch, const unsigned int frameSize, const signed int * deltas, const float probMin, const unsigned int nRefineLevels);

    void scanning_init_link(scans_obj * scans, const float ratioMatch);

    void scanning_init_minmax(scans_obj * scans);

#endif