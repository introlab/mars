#ifndef __MARS_SIGNAL_ASSIGNATION
#define __MARS_SIGNAL_ASSIGNATION

  /**
    * \file     assignation.h
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

    //! Assignation
    typedef struct assignation_obj {

        unsigned int nPots;         ///< Number of potential sources.
        signed int * array;         ///< Values of the assignations.

    } assignation_obj;

    //! Assignations
    typedef struct assignations_obj {

        unsigned int nSignals;      ///< Number of assignations.
        assignation_obj ** array;   ///< List of assignations.

    } assignations_obj;

    /** Constructor. Initialize all elements to 0.
        \param      nPots           Number of potential sources.
        \return                     Pointer to the instantiated object.
    */  
    assignation_obj * assignation_construct_zero(const unsigned int nPots);

    /** Constructor. Clone the object.
        \param      assignation     Object to be cloned.
        \return                     Pointer to the instantiated object.
    */  
    assignation_obj * assignation_construct_assignation(const assignation_obj * assignation);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void assignation_destroy(assignation_obj * obj);

    /** Print the content of the object.
        \param      obj         Object to be used.
    */
    void assignation_printf(const assignation_obj * obj);

    /** Constructor. Fill the array of objects with null pointers.
        \param      nSignals    Number of assignations.    
        \return                 Pointer to the instantiated object.
    */  
    assignations_obj * assignations_construct_null(const unsigned int nSignals);

    /** Destructor. Free memory, and destroy instantiated object in the list.
        \param      obj             Object to be destroyed.
    */
    void assignations_destroy(assignations_obj * obj);

    /** Print the content of the object.
        \param      obj         Object to be used.
    */
    void assignations_printf(const assignations_obj * obj);

#endif