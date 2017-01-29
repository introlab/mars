#ifndef __MARS_SYSTEM_PARTICLE2PARTICLE
#define __MARS_SYSTEM_PARTICLE2PARTICLE

    /**
    * \file     particle2particle.h
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

    #include "../utils/coord.h"
    #include "../utils/gaussian.h"
    #include "../utils/random.h"
    #include "../signal/particle.h"
    #include "../signal/postprob.h"
    #include "../signal/pot.h"

    //! Update the states of the particle filter
    typedef struct particle2particle_obj {

        unsigned int nParticles;                ///< Number of particles.
        float deltaT;                           ///< Time difference between two frames (in sec).

        float stationary_alpha;                 ///< \f$\alpha_{stat}\f$.
        float stationary_beta;                  ///< \f$\beta_{stat}\f$.
        float velocity_alpha;                   ///< \f$\alpha_{vel}\f$.
        float velocity_beta;                    ///< \f$\beta_{ve}\f$.
        float acceleration_alpha;               ///< \f$\alpha_{acc}\f$.
        float acceleration_beta;                ///< \f$\beta_{acc}\f$.

        float stationary_a;                     ///< \f$a_{stat}\f$.
        float stationary_b;                     ///< \f$b_{stat}\f$.
        float velocity_a;                       ///< \f$a_{vel}\f$.
        float velocity_b;                       ///< \f$b_{vel}\f$.
        float acceleration_a;                   ///< \f$a_{acc}\f$.
        float acceleration_b;                   ///< \f$b_{acc}\f$.

        float stationary_ratio;                 ///< Ratio of stationary particles.
        float velocity_ratio;                   ///< Ratio of constant velocity particles.
        float acceleration_ratio;               ///< Ratio of accelerated particles.

        char * states;                          ///< States of each particle ('U': undefined, 'S': stationary, 'V': constant velocity, 'A': accelerated).

        float sigmaR;                           ///< Standard deviation \f$\sigma_R\f$ in the matrix \f$\mathbf{R}\f$.
        gaussian_3d_obj * gaussian;             ///< 3D gaussian to estimate coherence.

        float * pdf_ratio;                      ///< Probability density function for the ratios of states.
        unsigned int * indexes_ratio;           ///< Indexes of the randomly generated states.
        random_obj * rnd_ratio;                 ///< Object to generate random numbers according to a specific PDF.
        
        float * pdf_weight;                     ///< Probability density function for the weights.
        unsigned int * indexes_weight;          ///< Indexes of the randomly generated weights.
        random_obj * rnd_weight;                ///< Object to generate random numbers according to a specific PDF.

        float * realisation_normal_x;           ///< Normally distributed numbers (x-coordinate).
        float * realisation_normal_y;           ///< Normally distributed numbers (y-coordinate).
        float * realisation_normal_z;           ///< Normally distributed numbers (z-coordinate).
        double epsilon;                         ///< Small value to generate normally distributed numbers.
        normaloff_obj * normaloff;              ///< Object to generate offline normally distributed random numbers.
       
        float * sum_P_p_x_O;                    ///< \f$\sum_{q=1}^{Q}{P_{q,i}p(O_q|\mathbf{x}_{j,i})}\f$.  
        float * p_x_O;                          ///< \f$p(\mathbf{x}_{j,i}|O)\f$.
        particles_obj * particles;              ///< Temporary copy of the particles when updating the weights.

        float Nmin;                             ///< \f$N_{min}\f$

    } particle2particle_obj;
       
    /** Constructor. Initialize all fields.
        \param      nParticles      Number of particles.
        \param      deltaT          Time difference between two frames (in sec).  
        \param      st_alpha        \f$\alpha_{stat}\f$.
        \param      st_beta         \f$\beta_{stat}\f$.
        \param      st_ratio        Ratio of stationary particles.
        \param      ve_alpha        \f$\alpha_{vel}\f$.
        \param      ve_beta         \f$\beta_{vel}\f$.
        \param      ve_ratio        Ratio of constant velocity particles.      
        \param      ac_alpha        \f$\alpha_{acc}\f$.
        \param      ac_beta         \f$\beta_{acc}\f$.
        \param      ac_ratio        Ratio of accelerated particles.
        \param      epsilon         Small value to generate normally distributed numbers.
        \param      sigmaR          Standard deviation \f$\sigma_R\f$ in the matrix \f$\mathbf{R}\f$.
        \param      Nmin            \f$N_{min}\f$            
        \return                     Pointer to the instantiated object.
    */              
    particle2particle_obj * particle2particle_construct(const unsigned int nParticles, const float deltaT, const float st_alpha, const float st_beta, const float st_ratio, const float ve_alpha, const float ve_beta, const float ve_ratio, const float ac_alpha, const float ac_beta, const float ac_ratio, const double epsilon, const float sigmaR, const float Nmin);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void particle2particle_destroy(particle2particle_obj * obj);

    /** Initialize the particle filter to the position of the potential source.
        \param      pot             Potential source.
        \param      particles       New tracked source.
        \param      obj             Object to be used.
    */
    void particle2particle_init(particle2particle_obj * obj, const pot_obj * pot, particles_obj * particles);

    /** Predict the next state of the particle filter.
        \param      particles       Particles filter which states are predicted.
        \param      obj             Object to be used.
    */
    void particle2particle_predict(particle2particle_obj * obj, particles_obj * particles);

    /** Update the state of the particle filter according to new observations.
        \param      postprob        Probabilities \f$p(t|\mathbf{E}_l^s,\mathbf{z}_l^s)\f$ for all \f$s\f$.
        \param      pots            Potential sources.
        \param      particles       Particles filter which states are updated.
        \param      obj             Object to be used.
    */
    void particle2particle_update(particle2particle_obj * obj, const postprob_obj * postprob, const pots_obj * pots, particles_obj * particles);

    /** Estimate the position of the tracked source.
        \param      particles       Particle filter.
        \param      coord           3D estimated position.
        \param      obj             Object to be used.
    */
    void particle2particle_estimate(const particle2particle_obj * obj, const particles_obj * particles, coord_obj * coord);

#endif