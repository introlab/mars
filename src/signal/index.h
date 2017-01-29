#ifndef __MARS_SIGNAL_INDEX
#define __MARS_SIGNAL_INDEX

    /**
    * \file     index.h
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

    //! Indexes
    typedef struct index_obj {
 
        unsigned int nIndexes;          ///< Number of indexes.
        unsigned int * array;           ///< Array of indexes.

    } index_obj;

    //! List of indexes
    typedef struct indexes_obj {

        unsigned int nSignals;          ///< Number of lists of indexes.
        index_obj ** array;             ///< Array of lists of indexes.

    } indexes_obj;

    /** Constructor. Initialize all elements to 0.
        \param      nIndexes        Number of indexes.
        \return                     Pointer to the instantiated object.
    */  
    index_obj * index_construct_zero(const unsigned int nIndexes);

    /** Constructor. Initialize all elements with those in the list.
        \param      nIndexes        Number of indexes.
        \param      list            List of indexes.
        \return                     Pointer to the instantiated object.
    */  
    index_obj * index_construct_list(const unsigned int nIndexes, const unsigned int * list);

    /** Constructor. Clone the object.
        \param      index       Object to be cloned.
        \return                 Pointer to the instantiated object.
    */  
    index_obj * index_construct_index(const index_obj * index);

    /** Set all fields to zero. No memory allocated.
        \param      obj         Object to be reset.
    */  
    void index_copy_zero(index_obj * obj);

    /** Set all elements with those in the list. No memory allocated.
        \param      list        List of indexes.
        \param      obj         Object to be reset.
    */  
    void index_copy_list(index_obj * obj, const unsigned int * list);    

    /** Set fields to the field values of the model object. No memory allocated.
        \param      index       Object to be copied.
        \param      obj         Object to be modified.
    */  
    void index_copy_index(index_obj * obj, const index_obj * index);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void index_destroy(index_obj * obj);

    /** Print the content of the object.
        \param      obj             Object to be used.
    */
    void index_printf(index_obj * obj);

    /** Constructor. Fill the array of objects with null pointers.
        \param      nSignals    Number of lists of indexes.    
        \return                 Pointer to the instantiated object.
    */  
    indexes_obj * indexes_construct_null(const unsigned int nSignals);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void indexes_destroy(indexes_obj * obj);

    /** Print the content of the object.
        \param      obj             Object to be used.
    */
    void indexes_printf(indexes_obj * obj);

#endif