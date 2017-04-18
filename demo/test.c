    
    #include <mars/mars.h>

    #include "../src/utils/sort.h"
    #include "../src/signal/delta.h"
    #include "../src/init/hit.h"
    #include "../src/init/linking.h"

    int main(int argc, char* argv[])
    {

        points_obj * pointsCoarse;
        points_obj * pointsFine;
        points_obj * pointsCoarseRefined;
        points_obj * pointsFineRefined;

        mics_obj * mics;
        soundspeed_obj * soundspeed;
        
        taus_obj * tausCoarse;
        tdoas_obj * tdoasCoarse;
        taus_obj * tausFine;
        tdoas_obj * tdoasFine;
        
        deltas_obj * deltasCoarse;
        deltas_obj * deltasFine;

        maps_obj * maps;
        indexes_obj * indexes;

        pointsCoarse = space_halfsphere(2);
        pointsCoarseRefined = space_points_fine(pointsCoarse,2);
        pointsFine = space_halfsphere(4);
        pointsFineRefined = space_points_fine(pointsFine,2);

        mics = mics_construct_zero(3);
        soundspeed = soundspeed_construct_zero();

        soundspeed->mu = 343.0f;
        soundspeed->sigma = 5.0f;

        mics->mu[0*3+0] = 0.1f;
        mics->mu[0*3+1] = 0.0f;
        mics->mu[0*3+2] = 0.0f;
        mics->mu[1*3+0] = 0.0f;
        mics->mu[1*3+1] = 0.1f;
        mics->mu[1*3+2] = 0.0f;
        mics->mu[2*3+0] = -0.1f;
        mics->mu[2*3+1] = 0.0f;
        mics->mu[2*3+2] = 0.0f;

        mics->sigma[0*9+0] = 1E-6;
        mics->sigma[0*9+1] = 0.0f;
        mics->sigma[0*9+2] = 0.0f;
        mics->sigma[0*9+3] = 0.0f;
        mics->sigma[0*9+4] = 1E-6;
        mics->sigma[0*9+5] = 0.0f;
        mics->sigma[0*9+6] = 0.0f;
        mics->sigma[0*9+7] = 0.0f;
        mics->sigma[0*9+8] = 0.0f;
        mics->sigma[1*9+0] = 1E-6;
        mics->sigma[1*9+1] = 0.0f;
        mics->sigma[1*9+2] = 0.0f;
        mics->sigma[1*9+3] = 0.0f;
        mics->sigma[1*9+4] = 1E-6;
        mics->sigma[1*9+5] = 0.0f;
        mics->sigma[1*9+6] = 0.0f;
        mics->sigma[1*9+7] = 0.0f;
        mics->sigma[1*9+8] = 0.0f;
        mics->sigma[2*9+0] = 1E-6;
        mics->sigma[2*9+1] = 0.0f;
        mics->sigma[2*9+2] = 0.0f;
        mics->sigma[2*9+3] = 0.0f;
        mics->sigma[2*9+4] = 1E-6;
        mics->sigma[2*9+5] = 0.0f;
        mics->sigma[2*9+6] = 0.0f;
        mics->sigma[2*9+7] = 0.0f;
        mics->sigma[2*9+8] = 0.0f;     

        tausCoarse = delay_taus(pointsCoarseRefined, mics, soundspeed, 48000, 256);
        tdoasCoarse = delay_tdoas(pointsCoarse, mics, soundspeed, 48000, 256);
        tausFine = delay_taus(pointsFineRefined, mics, soundspeed, 48000, 256);
        tdoasFine = delay_tdoas(pointsFine, mics, soundspeed, 48000, 256);

        deltasCoarse = hit_train(tausCoarse, tdoasCoarse, 0.5f);
        deltasFine = hit_train(tausFine, tdoasFine, 0.5f);

        maps = linking_maps(tdoasCoarse, tdoasFine, deltasCoarse, deltasFine, 0.1f);
        indexes = linking_indexes(maps);

        maps_printf(maps);
        indexes_printf(indexes);

    }
 