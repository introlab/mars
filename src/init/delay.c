
    #include "delay.h"

    tdoas_obj * delay_tdoas(const points_obj * points, const mics_obj * mics, const float c, const unsigned int fS, const unsigned int frameSize, const unsigned int delta) {

        tdoas_obj * obj;

        unsigned int nPairs;
        
        unsigned int iMic1;
        unsigned int iMic2;
        unsigned int iPair;
        unsigned int iPoint;

        float diff, dist, tau;

        nPairs = mics->nMics * (mics->nMics -1) / 2;

        obj = tdoas_construct_zero(points->nPoints,nPairs);

        for (iPoint = 0; iPoint < points->nPoints; iPoint++) {

            iPair = 0;

            for (iMic1 = 0; iMic1 < mics->nMics; iMic1++) {

                for (iMic2 = (iMic1+1); iMic2 < mics->nMics; iMic2++) {

                    dist = 0.0f;
                    dist += (mics->array[iMic1*3+0] - mics->array[iMic2*3+0]) * points->array[iPoint*3+0];
                    dist += (mics->array[iMic1*3+1] - mics->array[iMic2*3+1]) * points->array[iPoint*3+1];                    
                    dist += (mics->array[iMic1*3+2] - mics->array[iMic2*3+2]) * points->array[iPoint*3+2];                    

                    tau = (((float) fS) / c) * dist;

                    obj->array[iPoint*nPairs+iPair] = (unsigned int) (roundf(tau)+(float) (frameSize/2));

                    iPair++;

                }

            }

        }

        for (iPair = 0; iPair < nPairs; iPair++) {

            obj->arrayMin[iPair] = obj->array[iPair];
            obj->arrayMax[iPair] = obj->array[iPair];

            for (iPoint = 0; iPoint < points->nPoints; iPoint++) {

                if (obj->array[iPoint*nPairs+iPair] < obj->arrayMin[iPair]) {
                    obj->arrayMin[iPair] = obj->array[iPoint*nPairs+iPair];
                }

                if (obj->array[iPoint*nPairs+iPair] > obj->arrayMax[iPair]) {
                    obj->arrayMax[iPair] = obj->array[iPoint*nPairs+iPair];
                }

            }

            obj->arrayMin[iPair] -= delta;
            obj->arrayMax[iPair] += delta;

        }

        return obj;

    }
