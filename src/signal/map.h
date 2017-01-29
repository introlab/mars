#ifndef __MARS_SIGNAL_MAP
#define __MARS_SIGNAL_MAP

    /**
    * \file     map.h
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

    //! Map
    typedef struct map_obj {
 
        unsigned int nLinks;            ///< Number of elements in the map.
        unsigned char * array;          ///< List of elements in the map.

    } map_obj;

    //! Maps
    typedef struct maps_obj {

        unsigned int nSignals;          ///< Number of maps.
        map_obj ** array;               ///< List of maps.

    } maps_obj;

    /** Constructor. Initialize all elements to 0.
        \param      nLinks          Number of elements in the map.
        \return                     Pointer to the instantiated object.
    */
    map_obj * map_construct_zero(const unsigned int nLinks);

    /** Constructor. Initialize all elements to the array of booleans.
        \param      nLinks          Number of elements in the map.
        \param      bool            Array of booleans.
        \return                     Pointer to the instantiated object.
    */
    map_obj * map_construct_bool(const unsigned int nLinks, const unsigned char * bool);

    /** Constructor. Clone the object.
        \param      map         Object to be cloned.
        \return                 Pointer to the instantiated object.
    */  
    map_obj * map_construct_map(const map_obj * map);

    /** Set all fields to zero. No memory allocated.
        \param      obj         Object to be reset.
    */  
    void map_copy_zero(map_obj * obj);

    /** Set all fields to the values in the array of booleans. No memory allocated.
        \param      bool        Array of booleans.
        \param      obj         Object to be reset.
    */  
    void map_copy_bool(map_obj * obj, const unsigned char * bool);    

    /** Set fields to the field values of the model object. No memory allocated.
        \param      map         Object to be copied.
        \param      obj         Object to be modified.
    */  
    void map_copy_map(map_obj * obj, const map_obj * map);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void map_destroy(map_obj * obj);

    /** Print the content of the object.
        \param      obj             Object to be used.
    */
    void map_printf(map_obj * obj);

    /** Constructor. Fill the array of objects with null pointers.
        \param      nSignals    Number of maps.    
        \return                 Pointer to the instantiated object.
    */  
    maps_obj * maps_construct_null(const unsigned int nSignals);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void maps_destroy(maps_obj * obj);

    /** Print the content of the object.
        \param      obj             Object to be used.
    */
    void maps_printf(maps_obj * obj);


#endif