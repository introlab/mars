
    #include "delay.h"

    tdoas_obj * delay_tdoas(const points_obj * points, const mics_obj * mics, const soundspeed_obj * soundspeed, const unsigned int fS, const unsigned int frameSize) {

        tdoas_obj * obj;

        unsigned int nPairs;
        
        unsigned int iChannel1;
        unsigned int iChannel2;
        unsigned int iPair;
        unsigned int iPoint;

        float diff, dist, tau;

        nPairs = mics->nChannels * (mics->nChannels -1) / 2;

        obj = tdoas_construct_zero(points->nPoints,nPairs);

        for (iPoint = 0; iPoint < points->nPoints; iPoint++) {

            iPair = 0;

            for (iChannel1 = 0; iChannel1 < mics->nChannels; iChannel1++) {

                for (iChannel2 = (iChannel1+1); iChannel2 < mics->nChannels; iChannel2++) {

                    dist = 0.0f;
                    dist += (mics->mu[iChannel1*3+0] - mics->mu[iChannel2*3+0]) * points->array[iPoint*3+0];
                    dist += (mics->mu[iChannel1*3+1] - mics->mu[iChannel2*3+1]) * points->array[iPoint*3+1];                    
                    dist += (mics->mu[iChannel1*3+2] - mics->mu[iChannel2*3+2]) * points->array[iPoint*3+2];                    

                    tau = (((float) fS) / soundspeed->mu) * dist;

                    obj->array[iPoint*nPairs+iPair] = (unsigned int) (roundf(tau)+(float) (frameSize/2));

                    iPair++;

                }

            }

        }

        return obj;

    }

    tdoas_obj * delay_tdoas_minmax(const tdoas_obj * tdoas, const deltas_obj * deltas) {

        unsigned int nPairs;
        unsigned int nPoints;
        unsigned int iPair;
        unsigned int iPoint;

        unsigned int value;
        unsigned int valueLeft;
        unsigned int valueRight; 
        unsigned int minValue;
        unsigned int maxValue;

        tdoas_obj * obj;

        nPairs = tdoas->nPairs;
        nPoints = tdoas->nPoints;

        obj = tdoas_construct_zero(2, nPairs);

        for (iPair = 0; iPair < nPairs; iPair++) {

            obj->array[0 * nPairs + iPair] = tdoas->array[0 * nPairs + iPair] - deltas->array[iPair];
            obj->array[1 * nPairs + iPair] = tdoas->array[0 * nPairs + iPair] + deltas->array[iPair];

        }

        for (iPoint = 0; iPoint < nPoints; iPoint++) {

            for (iPair = 0; iPair < nPairs; iPair++) {               

                value = tdoas->array[iPoint * nPairs + iPair];
                valueLeft = value - deltas->array[iPair];
                valueRight = value + deltas->array[iPair];

                minValue = obj->array[0 * nPairs + iPair];
                maxValue = obj->array[1 * nPairs + iPair];

                // Min value
                if (valueLeft < minValue) {

                    minValue = valueLeft;

                }

                // Max value
                if (valueRight > maxValue) {

                    maxValue = valueRight;

                }

                obj->array[0 * nPairs + iPair] = minValue;
                obj->array[1 * nPairs + iPair] = maxValue;

            }

        }

        return obj;

    }

    void delay_tdoas_allminmax(tdoas_obj * tdoas, const tdoas_obj * minmax) {

        unsigned int nPairs;
        unsigned int iPair;

        nPairs = tdoas->nPairs;

        for (iPair = 0; iPair < nPairs; iPair++) {

            if (minmax->array[0*nPairs + iPair] < tdoas->array[0*nPairs + iPair]) {

                tdoas->array[0*nPairs + iPair] = minmax->array[0*nPairs + iPair];

            }

            if (minmax->array[1*nPairs + iPair] > tdoas->array[1*nPairs + iPair]) {

                tdoas->array[1*nPairs + iPair] = minmax->array[1*nPairs + iPair];

            }

        }

    }

    taus_obj * delay_taus(const points_obj * points, const mics_obj * mics, const soundspeed_obj * soundspeed, const unsigned int fS, const unsigned int frameSize) {

        taus_obj * obj;

        unsigned int nPairs;

        unsigned int iChannel1;
        unsigned int iChannel2;
        unsigned int iPair;
        unsigned int iPoint;

        float mu_t;
        float sigma_t;
        float mu_d;
        float sigma_d;
        float mu_tau;
        float sigma_tau;

        float mu_ij_x, mu_ij_y, mu_ij_z;
        float sigma_ij_xx, sigma_ij_xy, sigma_ij_xz;
        float sigma_ij_yx, sigma_ij_yy, sigma_ij_yz;
        float sigma_ij_zx, sigma_ij_zy, sigma_ij_zz;

        nPairs = mics->nChannels * (mics->nChannels -1) / 2;

        obj = taus_construct_zero(points->nPoints, nPairs);

        mu_t = ((float) fS) / soundspeed->mu;
        sigma_t = ((float) fS) * soundspeed->sigma / (soundspeed->mu * soundspeed->mu);

        iPair = 0;

        for (iChannel1 = 0; iChannel1 < mics->nChannels; iChannel1++) {

            for (iChannel2 = (iChannel1+1); iChannel2 < mics->nChannels; iChannel2++) {

                mu_ij_x = mics->mu[iChannel1*3+0] - mics->mu[iChannel2*3+0];
                mu_ij_y = mics->mu[iChannel1*3+1] - mics->mu[iChannel2*3+1];
                mu_ij_z = mics->mu[iChannel1*3+2] - mics->mu[iChannel2*3+2];

                sigma_ij_xx = mics->sigma[iChannel1*9+0];
                sigma_ij_xy = mics->sigma[iChannel1*9+1];
                sigma_ij_xz = mics->sigma[iChannel1*9+2];
                sigma_ij_yx = mics->sigma[iChannel1*9+3];
                sigma_ij_yy = mics->sigma[iChannel1*9+4];
                sigma_ij_yz = mics->sigma[iChannel1*9+5];
                sigma_ij_zx = mics->sigma[iChannel1*9+6];
                sigma_ij_zy = mics->sigma[iChannel1*9+7];
                sigma_ij_zz = mics->sigma[iChannel1*9+8];

                for (iPoint = 0; iPoint < points->nPoints; iPoint++) {

                    mu_d = mu_ij_x * points->array[iPoint*3+0] + 
                           mu_ij_y * points->array[iPoint*3+1] + 
                           mu_ij_z * points->array[iPoint*3+2];

                    sigma_d = sqrtf(points->array[iPoint*3+0] * sigma_ij_xx * points->array[iPoint*3+0] + 
                                    points->array[iPoint*3+0] * sigma_ij_xy * points->array[iPoint*3+1] + 
                                    points->array[iPoint*3+0] * sigma_ij_xz * points->array[iPoint*3+2] + 
                                    points->array[iPoint*3+1] * sigma_ij_yx * points->array[iPoint*3+0] + 
                                    points->array[iPoint*3+1] * sigma_ij_yy * points->array[iPoint*3+1] + 
                                    points->array[iPoint*3+1] * sigma_ij_yz * points->array[iPoint*3+2] + 
                                    points->array[iPoint*3+2] * sigma_ij_zx * points->array[iPoint*3+0] + 
                                    points->array[iPoint*3+2] * sigma_ij_zy * points->array[iPoint*3+1] + 
                                    points->array[iPoint*3+2] * sigma_ij_zz * points->array[iPoint*3+2]);

                    mu_tau = mu_t * mu_d;
                    sigma_tau = sqrtf((mu_t*sigma_d)*(mu_t*sigma_d) + (mu_d*sigma_t)*(mu_d*sigma_t));

                    obj->mu[iPoint*nPairs+iPair] = mu_tau + (float) (frameSize/2);
                    obj->sigma[iPoint*nPairs+iPair] = sigma_tau;

                }

                iPair++;

            }

        }

        return obj;

    }