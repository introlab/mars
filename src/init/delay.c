
    #include "delay.h"

    tdoas_obj * delay_tdoas(const points_obj * points, const mics_obj * mics, const float c, const unsigned int fS, const unsigned int frameSize) {

        tdoas_obj * obj;

        unsigned int nMics;
        unsigned int nPoints;
        unsigned int nPairs;
        
        unsigned int iMic1;
        unsigned int iMic2;
        unsigned int iPair;
        unsigned int iPoint;

        float dist;
        float tau;

        nPoints = points->nSignals;
        nMics = mics->nSignals;
        nPairs = nMics * (nMics -1) / 2;

        obj = tdoas_construct_null(nPoints);

        for (iPoint = 0; iPoint < nPoints; iPoint++) {

            obj->array[iPoint] = tdoa_construct_zero(nPairs);

            iPair = 0;

            for (iMic1 = 0; iMic1 < nMics; iMic1++) {

                for (iMic2 = (iMic1+1); iMic2 < nMics; iMic2++) {

                    dist = delay_dist(points->array[iPoint],mics->array[iMic2],mics->array[iMic1]);
                    tau = (((float) fS) / c) * dist;

                    obj->array[iPoint]->array[iPair] = (unsigned int) (roundf(tau)+(float) (frameSize/2));

                    iPair++;

                }

            }

        }

        return obj;

    }

    float delay_dist(const point_obj * point, const mic_obj * mic1, const mic_obj * mic2) {

        float dist;
        float dx, dy, dz;

        dx = mic1->coord->x - mic2->coord->x;
        dy = mic1->coord->y - mic2->coord->y;
        dz = mic1->coord->z - mic2->coord->z;

        dist = dx * point->coord->x + dy * point->coord->y + dz * point->coord->z;

        return dist;

    }

    tdoa_obj * delay_mins(const tdoas_obj * tdoas) {

        tdoa_obj * obj;
        unsigned int iPair;
        unsigned int iSignal;

        obj = tdoa_construct_tdoa(tdoas->array[0]);

        for (iSignal = 0; iSignal < tdoas->nSignals; iSignal++) {
            
            for (iPair = 0; iPair < tdoas->array[0]->nPairs; iPair++) {

                if (tdoas->array[iSignal]->array[iPair] < obj->array[iPair]) {

                    obj->array[iPair] = tdoas->array[iSignal]->array[iPair];

                }

            }

        }

        return obj;

    }

    tdoa_obj * delay_maxs(const tdoas_obj * tdoas) {

        tdoa_obj * obj;
        unsigned int iPair;
        unsigned int iSignal;

        obj = tdoa_construct_tdoa(tdoas->array[0]);

        for (iSignal = 0; iSignal < tdoas->nSignals; iSignal++) {
            
            for (iPair = 0; iPair < tdoas->array[0]->nPairs; iPair++) {

                if (tdoas->array[iSignal]->array[iPair] > obj->array[iPair]) {

                    obj->array[iPair] = tdoas->array[iSignal]->array[iPair];

                }

            }
        	
        }

        return obj;

    }