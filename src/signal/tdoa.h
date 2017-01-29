#ifndef __MARS_SIGNAL_TDOA
#define __MARS_SIGNAL_TDOA

    /**
    * \file     tdoa.h
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

    //! Time Difference of Arrival
    typedef struct tdoa_obj {

        unsigned int nPairs;            ///< Number of pairs of microphones.
        unsigned int * array;           ///< Array of TDOA values.

    } tdoa_obj;

    //! Time Differences of Arrival
    typedef struct tdoas_obj {

        unsigned int nSignals;          ///< Number of TDOAs vectors.
        tdoa_obj ** array;              ///< List of TDOAs vectors.

    } tdoas_obj;

    /** Constructor. Initialize all delays to zero.
        \return                 Pointer to the instantiated object.
    */  
    tdoa_obj * tdoa_construct_zero(const unsigned int nPairs);

    /** Constructor. Initialize the coordinates to the TDOA values.
        \param      nPairs      Number of pairs.
        \param      pair        TDOAs.
        \return                 Pointer to the instantiated object.
    */  
    tdoa_obj * tdoa_construct_pair(const unsigned int nPairs, const unsigned int * pair);

    /** Constructor. Clone the object.
        \param      tdoa        Object to be cloned.
        \return                 Pointer to the instantiated object.
    */  
    tdoa_obj * tdoa_construct_tdoa(const tdoa_obj * tdoa);

    /** Set all fields to zero. No memory allocated.
        \param      obj         Object to be reset.
    */  
    void tdoa_copy_zero(tdoa_obj * obj);

    /** Set fields to the TDOA values. No memory allocated.
        \param      obj         Object to be modified.
        \param      pair        TDOA values.
    */ 
    void tdoa_copy_pair(tdoa_obj * obj, const unsigned int * pair);

    /** Set fields to the field values of the model object. No memory allocated.
        \param      tdoa        Object to be copied.
        \param      obj         Object to be modified.
    */  
    void tdoa_copy_tdoa(tdoa_obj * obj, const tdoa_obj * tdoa);

    /** Destructor. Free memory.
        \param      obj         Object to be destroyed.
    */
    void tdoa_destroy(tdoa_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void tdoa_printf(tdoa_obj * obj);

    /** Constructor. Fill the array of objects with null pointers.
        \param      nSignals    Number of TDOAs.    
        \return                 Pointer to the instantiated object.
    */  
    tdoas_obj * tdoas_construct_null(const unsigned int nSignals);

    /** Destructor. Free memory.
        \param      obj         Object to be destroyed.
    */
    void tdoas_destroy(tdoas_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void tdoas_printf(tdoas_obj * obj);    

#endif