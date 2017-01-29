#ifndef __MARS_SIGNAL_POINT
#define __MARS_SIGNAL_POINT

    /**
    * \file     point.h
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

    //! Point
    typedef struct point_obj {

        coord_obj * coord;              ///< Coordinates of the points.

    } point_obj;

    //! Points
    typedef struct points_obj {

        unsigned int nSignals;          ///< Number of points.
        point_obj ** array;             ///< List of points.

    } points_obj;

    /** Constructor. Initialize all coordinates to zero.
        \return                     Pointer to the instantiated object.
    */
    point_obj * point_construct_zero(void);

    /** Constructor. Initialize x, y and z.        
        \param      x               X-coordinate (meter).
        \param      y               Y-coordinate (meter).        
        \param      z               Z-coordinate (meter).        
        \return                     Pointer to the instantiated object.
    */  
    point_obj * point_construct_xyz(const float x, const float y, const float z);

    /** Constructor. Clone the object.
        \param      point       Object to be cloned.
        \return                 Pointer to the instantiated object.
    */  
    point_obj * point_construct_point(const point_obj * point);

    /** Set all fields to zero. No memory allocated.
        \param      obj         Object to be reset.
    */  
    void point_copy_zero(point_obj * obj);

    /** Set fields to the value x,y and z. No memory allocated.
        \param      obj         Object to be modified.
        \param      x           X-coordinate.
        \param      y           Y-coordinate.
        \param      z           Z-coordinate.
    */  
    void point_copy_xyz(point_obj * obj, const float x, const float y, const float z);

   /** Set fields to the field values of the model object. No memory allocated.
        \param      point       Object to be copied.
        \param      obj         Object to be modified.
    */  
    void point_copy_point(point_obj * obj, const point_obj * point);

    /** Destructor. Free memory.
        \param      obj         Object to be destroyed.
    */
    void point_destroy(point_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void point_printf(point_obj * obj);

    /** Constructor. Initialize the list of objects with null pointers.
        \param      nSignals        Number of points.
        \return                     Pointer to the instantiaed object.
    */
    points_obj * points_construct_null(const unsigned int nSignals);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void points_destroy(points_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void points_printf(points_obj * obj);


#endif