
    #include "hit.h"

    areas_obj * hit_areas_zero(const taus_obj * taus, const tdoas_obj * tdoas, const deltas_obj * deltas) {

        areas_obj * areas;

        unsigned int nPointsDiscrete;
        unsigned int nPointsResolution;
        unsigned int nResolutionsPerDiscrete;
        unsigned int nPairs;

        nPointsDiscrete = tdoas->nPoints;
        nPointsResolution = taus->nPoints;
        nResolutionsPerDiscrete = nPointsResolution / nPointsDiscrete;
        nPairs = taus->nPairs;

        areas = areas_construct_zero(nPointsDiscrete, nResolutionsPerDiscrete, nPairs);

        return areas;

    }

    void hit_areas_pair(areas_obj * areas, const taus_obj * taus, const tdoas_obj * tdoas, const deltas_obj * deltas, const unsigned int iPair) {

        unsigned int iPointDiscrete;
        unsigned int nPointsDiscrete;
        unsigned int iPointResolution;
        unsigned int nPointsResolution;
        unsigned int iResolutionPerDiscrete;
        unsigned int nResolutionsPerDiscrete;
        unsigned int nPairs;

        float delta;
        float tdoa;

        float mu;
        float sigma;
        float expr1;
        float expr2;
        float prob;

        nPointsDiscrete = tdoas->nPoints;
        nPointsResolution = taus->nPoints;
        nResolutionsPerDiscrete = nPointsResolution / nPointsDiscrete;
        nPairs = taus->nPairs;

        delta = (float) deltas->array[iPair];

        for (iPointDiscrete = 0; iPointDiscrete < nPointsDiscrete; iPointDiscrete++) {

            tdoa = (float) tdoas->array[iPointDiscrete * nPairs + iPair];

            for (iResolutionPerDiscrete = 0; iResolutionPerDiscrete < nResolutionsPerDiscrete; iResolutionPerDiscrete++) {  

                iPointResolution = iPointDiscrete * nResolutionsPerDiscrete + iResolutionPerDiscrete;

                mu = taus->mu[iPointResolution * nPairs + iPair];
                sigma = taus->sigma[iPointResolution * nPairs + iPair];

                expr1 = (tdoa + delta + 0.5f - mu) / (sigma * sqrtf(2));
                expr2 = (tdoa - delta - 0.5f - mu) / (sigma * sqrtf(2));

                prob = 0.5f * (erff(expr1) - erff(expr2));                    

                areas->array[iPointResolution * nPairs + iPair] = prob;

            }

        }                

    }

    float hit_areas_min(areas_obj * areas) {

        unsigned int iPointDiscrete;
        unsigned int nPointsDiscrete;
        unsigned int iResolutionPerDiscrete;
        unsigned int nResolutionsPerDiscrete;
        unsigned int iPair;
        unsigned int nPairs;
        unsigned int iPointResolution;

        float prob;
        float minValue;

        nPointsDiscrete = areas->nPointsDiscrete;
        nResolutionsPerDiscrete = areas->nResolutionsPerDiscrete;
        nPairs = areas->nPairs;

        minValue = +INFINITY;

        for (iPointDiscrete = 0; iPointDiscrete < nPointsDiscrete; iPointDiscrete++) {

            for (iResolutionPerDiscrete = 0; iResolutionPerDiscrete < nResolutionsPerDiscrete; iResolutionPerDiscrete++) {

                iPointResolution = iPointDiscrete * nResolutionsPerDiscrete + iResolutionPerDiscrete;

                prob = 0.0f;

                for (iPair = 0; iPair < nPairs; iPair++) {

                    prob += areas->array[iPointResolution * nPairs + iPair];

                }

                if (prob < minValue) {
                    minValue = prob;
                }                

            }

        }

        minValue /= ((float) nPairs);

        return minValue;

    }

    area_obj * hit_area_zero(const taus_obj * taus, const tdoas_obj * tdoas, const deltas_obj * deltas) {

        area_obj * area;

        unsigned int nPairs;

        nPairs = taus->nPairs;

        area = area_construct_zero(nPairs);

        return area;

    }

    void hit_area_pair(area_obj * area, const areas_obj * areas, const taus_obj * taus, const tdoas_obj * tdoas, const deltas_obj * deltas, const unsigned int iPair) {

        unsigned int iPointDiscrete;
        unsigned int nPointsDiscrete;
        unsigned int iPointResolution;
        unsigned int nPointsResolution;
        unsigned int iResolutionPerDiscrete;
        unsigned int nResolutionsPerDiscrete;
        unsigned int nPairs;

        nPointsDiscrete = tdoas->nPoints;
        nPointsResolution = taus->nPoints;
        nResolutionsPerDiscrete = nPointsResolution / nPointsDiscrete;
        nPairs = taus->nPairs;

        area->array[iPair] = 0.0f;

        for (iPointDiscrete = 0; iPointDiscrete < nPointsDiscrete; iPointDiscrete++) {

            for (iResolutionPerDiscrete = 0; iResolutionPerDiscrete < nResolutionsPerDiscrete; iResolutionPerDiscrete++) {  

                iPointResolution = iPointDiscrete * nResolutionsPerDiscrete + iResolutionPerDiscrete;                

                area->array[iPair] += areas->array[iPointResolution * nPairs + iPair];

            }

        }    

    }

    deltas_obj * hit_train(const taus_obj * taus, const tdoas_obj * tdoas, const float probMin) {

        deltas_obj * deltas;
        areas_obj * areas;
        area_obj * area;
        
        unsigned int iPair;
        unsigned int nPairs;
        float minValue;
        unsigned int minIndex;

        nPairs = taus->nPairs;

        deltas = deltas_construct_zero(nPairs); 
        areas = hit_areas_zero(taus, tdoas, deltas); 
        area = hit_area_zero(taus, tdoas, deltas);

        for (iPair = 0; iPair < nPairs; iPair++) {

            hit_areas_pair(areas, taus, tdoas, deltas, iPair);
            hit_area_pair(area, areas, taus, tdoas, deltas, iPair);

        }

        while(1) {

            minValue = hit_areas_min(areas);

            if (minValue >= probMin) {
                break;
            }

            minValue = +INFINITY;

            for (iPair = 0; iPair < nPairs; iPair++) {

                if (area->array[iPair] < minValue) {
                    minValue = area->array[iPair];
                    minIndex = iPair;
                }
                
            }

            deltas->array[minIndex]++;

            hit_areas_pair(areas, taus, tdoas, deltas, minIndex);
            hit_area_pair(area, areas, taus, tdoas, deltas, minIndex);
            
        }

        return deltas;

    }

    deltas_obj * hit_constant(const tdoas_obj * tdoas, const unsigned int delta) {

        unsigned int iPair;
        unsigned int nPairs;

        deltas_obj * deltas;

        nPairs = tdoas->nPairs;

        deltas = deltas_construct_zero(nPairs);

        for (iPair = 0; iPair < nPairs; iPair++) {

            deltas->array[iPair] = delta;

        }

        return deltas;

    }