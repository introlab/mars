#ifndef __MARS_INIT_LINKING
#define __MARS_INIT_LINKING

    #include <math.h>
    #include <stdlib.h>
    #include <string.h>

    #include "../signal/index.h"
    #include "../signal/map.h"
    #include "../signal/tdoa.h"

    maps_obj * linking_maps(const tdoas_obj * tdoasCoarse, const tdoas_obj * tdoasFine, const float sigma, const unsigned int nMatches);

    indexes_obj * linking_indexes(const maps_obj * maps);

#endif