#ifndef __MARS_SIGNAL_PARTICLE
#define __MARS_SIGNAL_PARTICLE

    /**
    * \file     particle.h
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
 
    #include "../utils/coord.h"

    //! Particle
    typedef struct particle_obj {

        float w;                    ///< Weight.
        coord_obj * x;              ///< 3D position.
        coord_obj * v;              ///< 3D velocity.
        unsigned char state;        ///< State.

    } particle_obj;

    //! Particles
    typedef struct particles_obj {

        unsigned int nSignals;      ///< Number of particles.
        particle_obj ** array;      ///< List of particles.

    } particles_obj;

    /** Constructor. Initialize all elements to 0.
        \return                     Pointer to the instantiated object.
    */  
    particle_obj * particle_construct_zero(void);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void particle_destroy(particle_obj * obj);

    /** Set the fields. No memory allocated.
        \param      particle        Object from which fields are to be copied.
        \param      obj             Object to which fiedls are to be copied.
    */  
    void particle_copy_particle(particle_obj * obj, particle_obj * particle);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void particle_printf(const particle_obj * obj);

    /** Constructor. Initialize the list of objects with instantiated objects with fields set to zero.
        \param      nSignals        Number of microphones.
    */
    particles_obj * particles_construct_zero(const unsigned int nSignals);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void particles_destroy(particles_obj * obj);

    /** Set the fields. No memory allocated.
        \param      particles       Object from which fields are to be copied.
        \param      obj             Object to which fiedls are to be copied.
    */  
    void particles_copy_particles(particles_obj * obj, particles_obj * particles);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void particles_printf(const particles_obj * obj);

#endif