#ifndef __MARS_INIT_SCANNING
#define __MARS_INIT_SCANNING

    #include "../signal/scan.h"
    #include "../signal/mic.h"
    #include "../signal/map.h"
    #include "../init/space.h"
    #include "../init/delay.h"
    #include "../init/linking.h"

    scans_obj * scanning_init_sphere(const mics_obj * mics, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const float c, const float sigma, const unsigned int nMatches, const unsigned int frameSize, const unsigned int delta);

    scans_obj * scanning_init_halfsphere(const mics_obj * mics, const unsigned int nLevels, const unsigned int * levels, const unsigned int fS, const float c, const float sigma, const unsigned int nMatches, const unsigned int frameSize, const unsigned int delta);

    void scanning_init_link(scans_obj * scans, const unsigned int nMatches, const float sigma);

#endif