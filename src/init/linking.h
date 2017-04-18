#ifndef __MARS_INIT_LINKING
#define __MARS_INIT_LINKING

    #include <math.h>
    #include <stdlib.h>
    #include <string.h>

    #include "../signal/delta.h"
    #include "../signal/index.h"
    #include "../signal/map.h"
    #include "../signal/tdoa.h"

    maps_obj * linking_maps(const tdoas_obj * tdoasCoarse, const tdoas_obj * tdoasFine, const deltas_obj * deltasCoarse, const deltas_obj * deltasFine, const float ratioMatch);

    indexes_obj * linking_indexes(const maps_obj * maps);

    float linking_overlap(const float lambdaCoarseLeft, const float lambdaCoarseRight, const float lambdaFineLeft, const float lambdaFineRight);

#endif