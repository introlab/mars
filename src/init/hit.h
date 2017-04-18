#ifndef __MARS_INIT_HIT
#define __MARS_INIT_HIT

    #include <math.h>

    #include "../signal/area.h"
    #include "../signal/tau.h"
    #include "../signal/tdoa.h"
    #include "../signal/delta.h"

    areas_obj * hit_areas_zero(const taus_obj * taus, const tdoas_obj * tdoas, const deltas_obj * deltas);

    void hit_areas_pair(areas_obj * areas, const taus_obj * taus, const tdoas_obj * tdoas, const deltas_obj * deltas, const unsigned int iPair);

    float hit_areas_min(areas_obj * areas);

    area_obj * hit_area_zero(const taus_obj * taus, const tdoas_obj * tdoas, const deltas_obj * deltas);

    void hit_area_pair(area_obj * area, const areas_obj * areas, const taus_obj * taus, const tdoas_obj * tdoas, const deltas_obj * deltas, const unsigned int iPair);

    deltas_obj * hit_train(const taus_obj * taus, const tdoas_obj * tdoas, const float probMin);

    deltas_obj * hit_constant(const tdoas_obj * tdoas, const unsigned int delta);

#endif
