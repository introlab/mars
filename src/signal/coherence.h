#ifndef __MARS_SIGNAL_COHERENCE
#define __MARS_SIGNAL_COHERENCE

    /**
    * \file     coherence.h
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

    //! Coherence
    typedef struct coherence_obj {

        unsigned int S;             ///< Number of potential sources.
        float * probs;              ///< Array of probabilities.

    } coherence_obj;

    //! Coherences
    typedef struct coherences_obj {

        unsigned int nSignals;      ///< Number of coherence objects.
        coherence_obj ** array;     ///< List of coherence objects.

    } coherences_obj;

    /** Constructor. Initialize all elements to 0.
        \param      S               Number of potential sources.
        \return                     Pointer to the instantiated object.
    */  
    coherence_obj * coherence_construct_zero(const unsigned int S);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void coherence_destroy(coherence_obj * obj);

    /** Constructor. Fill the array of objects instantiated to zero.
        \param      T               Number of tracked sources.
        \param      S               Number of potential sources.
        \return                     Pointer to the instantiated object.
    */  
    coherences_obj * coherences_construct_zero(const unsigned int T, const unsigned int S);

    /** Destructor. Free memory, and destroy instantiated object in the list.
        \param      obj             Object to be destroyed.
    */
    void coherences_destroy(coherences_obj * obj);

    /** Print the content of the object.
        \param      obj         Object to be used.
    */
    void coherences_printf(const coherences_obj * obj);

#endif