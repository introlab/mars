#ifndef __MARS_SYSTEM_PARTICLE2COHERENCE
#define __MARS_SYSTEM_PARTICLE2COHERENCE

    /**
    * \file     particle2coherence.h
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

    #include "../utils/gaussian.h"
    #include "../signal/particle.h"
    #include "../signal/coherence.h"
    #include "../signal/pot.h"

    //! Generator of coherence probability from the particle filter and observations
    typedef struct particle2coherence_obj {

        float sigmaR;                   ///< Standard deviation in the matrix \f$\mathbf{R}\f$.                                 
        gaussian_3d_obj * gaussian;     ///< 3D gaussian object.

    } particle2coherence_obj;

    /** Constructor. Initialize all fields to zero.
        \param      sigmaR          Standard deviation in the matrix \f$\mathbf{R}\f$.
        \return                     Pointer to the instantiated object.
    */ 
    particle2coherence_obj * particle2coherence_construct(const float sigmaR);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void particle2coherence_destroy(particle2coherence_obj * obj);

    /** Fill the coherence object with probabilities \f$p(\mathbf{z}^s_l|\mathcal{C},t)\f$ for all \f$s\f$ and a given \f$t\f$.
        \param      particles       Particle filter.
        \param      pots            Potential sources.
        \param      coherence       Coherence.
        \param      obj             Object to be used.
    */
    void particle2coherence_process(particle2coherence_obj * obj, const particles_obj * particles, const pots_obj * pots, coherence_obj * coherence);

#endif