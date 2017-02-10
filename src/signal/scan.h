#ifndef __MARS_SIGNAL_SCAN
#define __MARS_SIGNAL_SCAN

    #include <stdlib.h>
    #include <string.h>

    #include "point.h"
    #include "tdoa.h"
    #include "index.h"

    //! Scan setup
    typedef struct scans_obj {

        unsigned int nScans;
        points_obj ** points;
        tdoas_obj ** tdoas;
        indexes_obj ** indexes;

    } scans_obj;

    scans_obj * scans_construct_null(const unsigned int nScans);

    void scans_destroy(scans_obj * obj);

#endif