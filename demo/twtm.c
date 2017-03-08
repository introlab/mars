
#include <mars/mars.h>

#include <math.h>
#include <stdio.h>

int main(int argc, char* argv[]){

    msg_pots_cfg * msg_pots_config;
    mod_sst_cfg * mod_sst_config;
    msg_tracks_cfg * msg_tracks_config;

	msg_pots_obj * msg_pots;
    mod_sst_obj * mod_sst;
    msg_tracks_obj * msg_tracks;

    unsigned int iTDOA;
    unsigned int iTDOA_tracked;
    
    float d;
    float fS;

    // Files

    FILE * fpIn;
    FILE * fpOut;

    // In
    signed int TDOAs[4];
    float amplitudes[4];
    float thetas[4];
    float xs[4];
    float ys[4];
    float zs[4];

    // Out
    unsigned long long IDs_tracked[4];
    float xs_tracked[4];
    float ys_tracked[4];
    float zs_tracked[4];
    float thetas_tracked[4];
    signed int TDOAs_tracked[4];


    // Constants

    // Init configs

    msg_pots_config = msg_pots_cfg_construct();
    mod_sst_config = mod_sst_cfg_construct();
    msg_tracks_config = msg_tracks_cfg_construct();

    // Open files
    fpIn = fopen(argv[1], "r");
    fpOut = fopen(argv[2], "w");

    // Set configuration parameters (hard-coded)

    msg_pots_config->nPots = 4;

    mod_sst_config->nPots = 4;
    mod_sst_config->nTracks = 4;
    mod_sst_config->mode = "particle";
    mod_sst_config->R = 1;
    mod_sst_config->hopSize = 256;
    mod_sst_config->fS = 16000;
    mod_sst_config->sigmaQ = 0.01;
	mod_sst_config->nParticles = 1000;        
    mod_sst_config->st_alpha = 2.0f;
 	mod_sst_config->st_beta = 0.04f;
 	mod_sst_config->st_ratio = 0.5f;
 	mod_sst_config->ve_alpha = 0.05f;
 	mod_sst_config->ve_beta = 0.2f;
 	mod_sst_config->ve_ratio = 0.3f;
 	mod_sst_config->ac_alpha = 0.5f;
 	mod_sst_config->ac_beta = 0.2f;
 	mod_sst_config->ac_ratio = 0.2f;
 	mod_sst_config->Nmin = 0.7f;
 	mod_sst_config->epsilon = 1E-20f;
 	mod_sst_config->sigmaR_active = 0.15f;
 	mod_sst_config->sigmaR_prob = 0.05f;
    mod_sst_config->active_gmm = gaussians_1d_construct_null(1);
    mod_sst_config->active_gmm->array[0] = gaussian_1d_construct_weightmusigma(1.0f, 0.50f, 0.05f);
    mod_sst_config->inactive_gmm = gaussians_1d_construct_null(1);
    mod_sst_config->inactive_gmm->array[0] = gaussian_1d_construct_weightmusigma(1.0f, 0.25f, 0.05f);
    mod_sst_config->Pfalse = 0.1f;
	mod_sst_config->Pnew = 0.1f;
    mod_sst_config->Ptrack = 0.8f;
    mod_sst_config->shape = "arc";
    mod_sst_config->theta_new = 0.9f;
    mod_sst_config->N_prob = 5;
    mod_sst_config->theta_prob = 0.8f;
    mod_sst_config->N_inactive = (unsigned int *) malloc(sizeof(unsigned int) * 4);
    mod_sst_config->N_inactive[0] = 150;
    mod_sst_config->N_inactive[1] = 200;
    mod_sst_config->N_inactive[2] = 250;
    mod_sst_config->N_inactive[3] = 250;
    mod_sst_config->theta_inactive = 0.9f;   

    msg_tracks_config->nTracks = 4;

	// Init objects

    msg_pots = msg_pots_construct(msg_pots_config);
    mod_sst = mod_sst_construct(mod_sst_config);
    msg_tracks = msg_tracks_construct(msg_tracks_config);

	// Process

    while(fscanf(fpIn, 
    	         "%d,%f,%d,%f,%d,%f,%d,%f",
    	         &(TDOAs[0]),
    	         &(amplitudes[0]),
    	         &(TDOAs[1]),
    	         &(amplitudes[1]),
    	         &(TDOAs[2]),
    	         &(amplitudes[2]),
    	         &(TDOAs[3]),
    	         &(amplitudes[3])) != EOF) {

    	// Convert to x y z

    		for (iTDOA = 0; iTDOA < 4; iTDOA++) {

    			if (TDOAs[iTDOA] != -1) {

	    			// (tau-63.5)/63.5 = cos(theta)
	    			// theta = acos((tau-63.5)/63.5)

	    			thetas[iTDOA] = acosf((((float) TDOAs[iTDOA])-63.5f)/63.5f);

	    			// x = cos(theta);
	    			// y = sin(theta);
	    			// z = 0;

	    			xs[iTDOA] = cosf(thetas[iTDOA]);
	    			ys[iTDOA] = sinf(thetas[iTDOA]);
	    			zs[iTDOA] = 0.0f;

    			}
    			else {

    				xs[iTDOA] = 1.0f;
    				ys[iTDOA] = 0.0f;
    				zs[iTDOA] = 0.0f;
    				amplitudes[iTDOA] = 0.0f;

    			}

    		}

    	// Load in potential sources

    		for (iTDOA = 0; iTDOA < 4; iTDOA++) {

    			msg_pots->pots->array[iTDOA*4+0] = xs[iTDOA];
    			msg_pots->pots->array[iTDOA*4+1] = ys[iTDOA];
    			msg_pots->pots->array[iTDOA*4+2] = zs[iTDOA];
    			msg_pots->pots->array[iTDOA*4+3] = amplitudes[iTDOA];

    		}

    	// Perform tracking

    		mod_sst_process(mod_sst, msg_pots, msg_tracks);

    	// Extracts tracked sources

    		for (iTDOA_tracked = 0; iTDOA_tracked < 4; iTDOA_tracked++ ) {

    			IDs_tracked[iTDOA_tracked] = msg_tracks->tracks->ids[iTDOA_tracked];
    			xs_tracked[iTDOA_tracked] = msg_tracks->tracks->array[iTDOA_tracked * 3 + 0];
    			ys_tracked[iTDOA_tracked] = msg_tracks->tracks->array[iTDOA_tracked * 3 + 1];
    			zs_tracked[iTDOA_tracked] = msg_tracks->tracks->array[iTDOA_tracked * 3 + 2];

    		}

    	// Convert to TDOA

    		for (iTDOA_tracked = 0; iTDOA_tracked < 4; iTDOA_tracked++) {

    			// theta = atan2(y,x)

    			thetas_tracked[iTDOA_tracked] = atan2f(ys_tracked[iTDOA_tracked],xs_tracked[iTDOA_tracked]);

    			// (tau-63.5)/63.5 = cos(theta)
    			// tau = 63.5*cos(theta) + 63.5;

    			TDOAs_tracked[iTDOA_tracked] = (signed int) roundf(63.5f * cosf(thetas_tracked[iTDOA_tracked]) + 63.5f);

    			
    		}

    	// Push tracked TDOAS

		for (iTDOA_tracked = 0; iTDOA_tracked < 4; iTDOA_tracked++) {

			fprintf(fpOut, 
				    "%llu,%d",
				    IDs_tracked[iTDOA_tracked],
				    TDOAs_tracked[iTDOA_tracked]);

			if (iTDOA_tracked < 3) {
				fprintf(fpOut, ",");
			}

		}    		

		fprintf(fpOut, "\n");

    }

    fclose(fpIn);
    fclose(fpOut);

	// Free memory

    	// Optional here

}