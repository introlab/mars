#ifndef __MARS_SIGNAL_POT
#define __MARS_SIGNAL_POT

    /**
    * \file     pot.h
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

    //! Potential source
    typedef struct pot_obj {

        coord_obj * coord;          ///< Coordinate of the potential source.
        float E;                    ///< Energy level.

    } pot_obj;

    //! Potential sources
    typedef struct pots_obj {

        unsigned int nSignals;      ///< Number of potential sources.
        pot_obj ** array;           ///< List of potential sources.

    } pots_obj;

    /** Constructor. Initialize all coordinates and energy to zero.
        \return                     Pointer to the instantiated object.
    */  
    pot_obj * pot_construct_zero(void);

    /** Constructor. Initialize x, y and z.        
        \param      x               X-coordinate (meter).
        \param      y               Y-coordinate (meter).        
        \param      z               Z-coordinate (meter).    
        \param      E               Energy level.    
        \return                     Pointer to the instantiated object.
    */  
    pot_obj * pot_construct_xyzE(const float x, const float y, const float z, const float E);

    /** Constructor. Clone the object.
        \param      pot             Object to be cloned.
        \return                     Pointer to the instantiated object.
    */  
    pot_obj * pot_construct_pot(const pot_obj * pot);

    /** Set all fields to zero. No memory allocated.
        \param      obj             Object to be reset.
    */  
    void pot_copy_zero(pot_obj * obj);

    /** Set the x, y, z and E fields. No memory allocated.
        \param      obj             Object to be set.
        \param      x               X-coordinate (meter).
        \param      y               Y-coordinate (meter).        
        \param      z               Z-coordinate (meter).        
        \param      E               Energy level.
    */  
    void pot_copy_xyzE(pot_obj * obj, const float x, const float y, const float z, const float E);    

    /** Set the fields. No memory allocated.
        \param      pot             Object from which fields are to be copied.
        \param      obj             Object to which fiedls are to be copied.
    */  
    void pot_copy_pot(pot_obj * obj, const pot_obj * pot);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void pot_destroy(pot_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void pot_printf(pot_obj * obj);

    /** Constructor. Initialize the list of objects with instantiated points.
        \param      nSignals        Number of potential sources.
        \return                     Pointer to the instantiaed object.
    */
    pots_obj * pots_construct_zero(const unsigned int nSignals);

    /** Set the fields. No memory allocated.
        \param      pots            Object from which fields are to be copied.
        \param      obj             Object to which fiedls are to be copied.
    */  
    void pots_copy_pots(pots_obj * obj, const pots_obj * pots);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void pots_destroy(pots_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void pots_printf(pots_obj * obj);    

#endif