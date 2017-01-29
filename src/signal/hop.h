#ifndef __MARS_SIGNAL_HOP
#define __MARS_SIGNAL_HOP

    /**
    * \file     hop.h
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
 
    //! Hop
    typedef struct hop_obj {

        unsigned int hopSize;           ///< Number of samples per hop.
        float * array;                  ///< Array of samples.

    } hop_obj;

    //! Hops
    typedef struct hops_obj {

        unsigned int nSignals;          ///< Number of hops.
        hop_obj ** array;               ///< List of hops.

    } hops_obj;

    /** Constructor. Initialize all elements to 0.
        \param      hopSize         Number of samples per hop.
        \return                     Pointer to the instantiated object.
    */  
    hop_obj * hop_construct_zero(const unsigned int hopSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void hop_destroy(hop_obj * obj);

    /** Print the content of the object.
        \param      obj             Object to be used.
    */
    void hop_printf(const hop_obj * obj);

    /** Constructor. Fill the array of objects with null pointers.
        \param      nSignals        Number of hops.    
        \return                     Pointer to the instantiated object.
    */ 
    hops_obj * hops_construct_null(const unsigned int nSignals);

    /** Constructor. Fill the array of objects instantiated to zero.
        \param      nSignals        Number of hops.
        \param      hopSize         Number of samples per hop.
        \return                     Pointer to the instantiated object.
    */  
    hops_obj * hops_construct_zero(const unsigned int nSignals, const unsigned int hopSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void hops_destroy(hops_obj * obj);

    /** Print the content of the object.
        \param      obj             Object to be used.
    */
    void hops_printf(const hops_obj * obj);

#endif