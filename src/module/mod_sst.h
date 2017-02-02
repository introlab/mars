#ifndef __MARS_MODULE_SST
#define __MARS_MODULE_SST

    /**
    * \file     mod_sst.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2017-01-25
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <math.h>

    #include "../signal/kalman.h"
    #include "../system/kalman2kalman.h"

    #include "../signal/particle.h"
    #include "../system/particle2particle.h"

    #include "../signal/coherence.h"
    #include "../system/kalman2coherence.h"
    #include "../system/particle2coherence.h"

    #include "../signal/mixture.h"
    #include "../system/mixture2mixture.h"

    #include "../message/msg_pots.h"
    #include "../message/msg_tracks.h"

    //! Module to perform sound source tracking
    typedef struct mod_sst_obj {

        unsigned int S;                                     ///< Number of potential sources.
        unsigned int Tmax;                                  ///< Maximum number of tracked sources.
        unsigned int T;                                     ///< Number of tracked sources.

        char * mode;                                        ///< Tracking mode ("particle" or "kalman").

        mixture_obj ** mixtures;                            ///< List of mixtures.
        coherences_obj ** coherences;                       ///< List of coherences.
        postprobs_obj ** postprobs;                         ///< List of postprobs.

        unsigned long long * ids;                           ///< List of IDs for tracked sources.
        unsigned long long * idsAdded;                      ///< List of IDs to be added.
        unsigned long long * idsRemoved;                    ///< List of IDs to be removed.
        
        char * type;                                        ///< Types of sound sources ('I','P','A').

        kalman_obj ** kalmans;                              ///< List of Kalman filters.
        kalman2kalman_obj * kalman2kalman_prob;             ///< List of systems to update the Kalman filters (probation).
        kalman2kalman_obj * kalman2kalman_active;           ///< List of systems to update the Kalman filters (active).
        kalman2coherence_obj * kalman2coherence_prob;       ///< List of systems to compute coherence from Kalman filters (probation).
        kalman2coherence_obj * kalman2coherence_active;     ///< List of systems to compute coherence from Kalman filters (active).
        
        particles_obj ** particles;                         ///< List of particle filters.
        particle2particle_obj * particle2particle_prob;     ///< List of systems to update the particle filters (probation).
        particle2particle_obj * particle2particle_active;   ///< List of systems to update the particle filters (active).
        particle2coherence_obj * particle2coherence_prob;   ///< List of systems to compute coherence from particle filters (probation).
        particle2coherence_obj * particle2coherence_active; ///< List of systems to compute coherence from particle filters (active).

        mixture2mixture_obj * mixture2mixture;              ///< List of systems to update the mixtures.
        
        float theta_new;                                    ///< Parameter \f$\theta_{new}\f$.
        unsigned int N_prob;                                ///< Parameter \f$N_{prob}\f$.
        float theta_prob;                                   ///< Parameter \f$\theta_{prob}\f$.
        unsigned int * N_inactive;                          ///< Parameters \f$\mathbf{N}_{inactive}\f$.
        float theta_inactive;                               ///< Parameter \f$\theta_{inactive}\f$.

        unsigned int * n_prob;                              ///< Counter for sources that are in probation.
        float * mean_prob;                                  ///< Mean of tracked sources activity.
        unsigned int * n_inactive;                          ///< Counter for sources that are inactive.

        coord_obj * coord;                                  ///< Coordinate of a tracked source.

        unsigned long long id;                              ///< ID counter.

    } mod_sst_obj;

    //! Configuration of sound source tracking
    typedef struct mod_sst_cfg {

        unsigned int nPots;                             ///< Number of potential sources.
        unsigned int nTracks;                           ///< Maximum number of tracked soruces.

        char * mode;                                    ///< Tracking mode ("particle" or "kalman");

        unsigned int R;                                 ///< Number of frames to update sound source localization.
        unsigned int hopSize;                           ///< Number of samples per hop.
        unsigned int fS;                                ///< Sample rate (samples/sec).
        float sigmaQ;                                   ///< Parameter \f$\sigma_Q\f$.
        
        unsigned int nParticles;                        ///< Number of particles.
        float st_alpha;                                 ///< \f$\alpha_{stat}\f$.
        float st_beta;                                  ///< \f$\beta_{stat}\f$.
        float st_ratio;                                 ///< Ratio of stationary particles.
        float ve_alpha;                                 ///< \f$\alpha_{vel}\f$.
        float ve_beta;                                  ///< \f$\beta_{ve}\f$.
        float ve_ratio;                                 ///< Ratio of constant velocity particles.
        float ac_alpha;                                 ///< \f$\alpha_{acc}\f$.
        float ac_beta;                                  ///< \f$\beta_{acc}\f$.
        float ac_ratio;                                 ///< Ratio of accelerated particles.
        float Nmin;                                     ///< \f$N_{min}\f$.

        float epsilon;                                  ///< Small value to avoid overflow.
        float sigmaR_active;                            ///< Standard deviation \f$\sigma_R\f$ in the matrix \f$\mathbf{R}\f$.
        float sigmaR_prob;
        gaussians_1d_obj * active_gmm;                  ///< Gaussian mixture model (GMM) for the energy distribution of an active source.
        gaussians_1d_obj * inactive_gmm;                ///< Gaussian mixture model (GMM) for the energy distribution of an inactive source.
        float Pfalse;                                   ///< A priori probability there is a false detection (\f$P_{false}\f$).
        float Pnew;                                     ///< A priori probability there is a new detection (\f$P_{new}\f$).
        float Ptrack;                                   ///< A priori probability an tracked source is observed (\f$P_{track}\f$).
        char * shape;                                   ///< Shape of the scanning region ("sphere" or "halfsphere").

        float theta_new;                                ///< Parameter \f$\theta_{new}\f$.
        unsigned int N_prob;                            ///< Parameter \f$N_{prob}\f$.
        float theta_prob;                               ///< Parameter \f$\theta_{prob}\f$.
        unsigned int * N_inactive;                      ///< Parameters \f$\mathbf{N}_{inactive}\f$.
        float theta_inactive;                           ///< Parameter \f$\theta_{inactive}\f$.

    } mod_sst_cfg;

    /** Constructor. Initialize all elements according to the configuration file.
        \param      cfg             Configuration.
        \return                     Pointer to the instantiated object.
    */ 
    mod_sst_obj * mod_sst_construct(const mod_sst_cfg * cfg);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void mod_sst_destroy(mod_sst_obj * obj);

    /** Perform Sound Source Tracking (SST) and generate tracked sources.
        \param      msg_pots        Message with the potential sources.
        \param      msg_tracks      Message with the tracked sources.
        \param      obj             Object to be used.
    */
    void mod_sst_process(mod_sst_obj * obj, const msg_pots_obj * msg_pots, msg_tracks_obj * msg_tracks);

    /** Constructor.
        \return                     Pointer to the instantiated object.
    */ 
    mod_sst_cfg * mod_sst_cfg_construct(void);

    /** Destructor. Free memory.
        \param      cfg             Object to be destroyed.
    */
    void mod_sst_cfg_destroy(mod_sst_cfg * cfg);

#endif