#ifndef __MARS_UTILS_ARRAY
#define __MARS_UTILS_ARRAY

    /**
    * \file     array.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-11-04
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

    //! A structure that holds all the fields in a 1-D array.     
    typedef struct array_1d {
                                
        unsigned int X;         ///< Number of elements in the 1st dimension.
        void ** ptr;            ///< Pointer to the 1-D array.

    } array_1d;

    //! A structure that holds all the fields in a 2-D array.     
    typedef struct array_2d {

        unsigned int X;         ///< Number of elements in the 1st dimension.
        unsigned int Y;         ///< Number of elements in the 2nd dimension.
        void *** ptr;           ///< Pointer to the 2-D array.

    } array_2d;    

    typedef struct array_3d {

        unsigned int X;         ///< Number of elements in the 1st dimension.
        unsigned int Y;         ///< Number of elements in the 2nd dimension.
        unsigned int Z;         ///< Number of elements in the 3rd dimension.
        void **** ptr;          ///< Pointer to the 3-D array.

    } array_3d;       

    /** Constructor of the array object.   
        \param      X           Number of elements in the 1st dimension.
        \return                 Pointer to the instantiated object.
    */      
    array_1d * array_1d_malloc(const unsigned int X);

    /** Constructor of the array object.   
        \param      X           Number of elements in the 1st dimension.
        \param      Y           Number of elements in the 2nd dimension.
        \return                 Pointer to the instantiated object.
    */      
    array_2d * array_2d_malloc(const unsigned int X, const unsigned int Y);

    /** Constructor of the array object.   
        \param      X           Number of elements in the 1st dimension.
        \param      Y           Number of elements in the 2nd dimension.
        \param      Z           Number of elements in the 3rd dimension.
        \return                 Pointer to the instantiated object.
    */      
    array_3d * array_3d_malloc(const unsigned int X, const unsigned int Y, const unsigned int Z);

    /** Destructor of the array object.
        \param      obj         Pointer to the instantiated object.
    */
    void array_1d_free(array_1d * obj);

    /** Destructor of the array object.
        \param      obj         Pointer to the instantiated object.
    */
    void array_2d_free(array_2d * obj);

    /** Destructor of the array object.
        \param      obj         Pointer to the instantiated object.
    */
    void array_3d_free(array_3d * obj);

#endif