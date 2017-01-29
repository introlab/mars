#ifndef __MARS_SIGNAL_TRIANGLE
#define __MARS_SIGNAL_TRIANGLE

    /**
    * \file     triangle.h
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
    #include "../signal/point.h"

    //! Triangle
    typedef struct triangle_obj {

        point_obj * pointA;             ///< First point of the triangle.
        point_obj * pointB;             ///< Second point of the triangle.
        point_obj * pointC;             ///< Third point of the triangle.

    } triangle_obj;

    //! Triangles
    typedef struct triangles_obj {

        unsigned nSignals;              ///< Number of triangles.
        triangle_obj ** array;          ///< List of triangles.

    } triangles_obj;

    /** Constructor. Initialize all points to zero.
        \return                     Pointer to the instantiated object.
    */  
    triangle_obj * triangle_construct_zero(void);

    /** Constructor. Initialize points. 
        \param      pointA          First point of the triangle.
        \param      pointB          First point of the triangle.
        \param      pointC          First point of the triangle.
        \return                     Pointer to the instantiated object.
    */  
    triangle_obj * triangle_construct_point(const point_obj * pointA, const point_obj * pointB, const point_obj * pointC);

    /** Constructor. Clone the object.
        \param      triangle        Object to be cloned.
        \return                     Pointer to the instantiated object.
    */  
    triangle_obj * triangle_construct_triangle(const triangle_obj * triangle);

    /** Set all fields to zero. No memory allocated.
        \param      obj             Object to be reset.
    */
    void triangle_copy_zero(triangle_obj * obj);

    /** Set the points. No memory allocated.
        \param      obj             Object to be set.
        \param      pointA          First point of the triangle.
        \param      pointB          First point of the triangle.
        \param      pointC          First point of the triangle.   
    */ 
    void triangle_copy_point(triangle_obj * obj, const point_obj * pointA, const point_obj * pointB, const point_obj * pointC);

    /** Set the fields. No memory allocated.
        \param      triangle        Object from which fields are to be copied.
        \param      obj             Object to which fields are to be copied.
    */  
    void triangle_copy_triangle(triangle_obj * obj, const triangle_obj * triangle);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void triangle_destroy(triangle_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void triangle_printf(triangle_obj * obj);

    /** Constructor. Fill the array of objects with null pointers.
        \param      nSignals    Number of triangles.    
        \return                 Pointer to the instantiated object.
    */  
    triangles_obj * triangles_construct_null(const unsigned int nSignals);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void triangles_destroy(triangles_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void triangles_printf(triangles_obj * obj);

#endif