#ifndef __MARS_UTILS_COORD
#define __MARS_UTILS_COORD

    /**
    * \file     coord.h
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

    //! XYZ-coordinates.
    typedef struct coord_obj {

        float x;                ///< X-coordinate.
        float y;                ///< Y-coordinate.
        float z;                ///< Z-coordinate.

    } coord_obj;

    /** Constructor. Initialize all coordinates to zero.
        \return                 Pointer to the instantiated object.
    */  
    coord_obj * coord_construct_zero(void);

    /** Constructor. Initialize the coordinates to the values x,y and z.
        \param      x           X-coordinate.
        \param      y           Y-coordinate.
        \param      z           Z-coordinate.
        \return                 Pointer to the instantiated object.
    */  
    coord_obj * coord_construct_xyz(const float x, const float y, const float z);

    /** Constructor. Clone the object.
        \param      coord       Object to be cloned.
        \return                 Pointer to the instantiated object.
    */  
    coord_obj * coord_construct_coord(const coord_obj * coord);

    /** Set all fields to zero. No memory allocated.
        \param      obj         Object to be reset.
    */  
    void coord_copy_zero(coord_obj * obj);

    /** Set fields to the value x,y and z. No memory allocated.
        \param      obj         Object to be modified.
        \param      x           X-coordinate.
        \param      y           Y-coordinate.
        \param      z           Z-coordinate.
    */  
    void coord_copy_xyz(coord_obj * obj, const float x, const float y, const float z);

    /** Set fields to the field values of the model object. No memory allocated.
        \param      coord       Object to be copied.
        \param      obj         Object to be modified.
    */  
    void coord_copy_coord(coord_obj * obj, const coord_obj * coord);

    /** Destructor. Free memory.
        \param      obj         Object to be destroyed.
    */
    void coord_destroy(coord_obj * obj);

#endif