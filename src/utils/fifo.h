#ifndef __MARS_UTILS_FIFO
#define __MARS_UTILS_FIFO

    #include <stdlib.h>
    #include <pthread.h>

    /**
    * \file     fifo.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-10-26
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

    //! A structure that holds all the fields of a fifo buffer.
    typedef struct fifo {

        pthread_mutex_t mutex;          ///< Mutex to protect the structure from simultaneous pop/push.	 
        void ** buffer;                 ///< Buffer that holds all the pointers.
        unsigned int nMaxElements;      ///< Maximum number of elements in the buffer.
        unsigned int nElements;         ///< Actual number of elements in the buffer.
        unsigned int iRead;             ///< Index of the read pointer.
        unsigned int iWrite;            ///< Index of the write pointer.

    } fifo;

    /** Constructor of the fifo object.	
        \param      nMaxElements    Maximum number of elements in the buffer.
        \return                     Pointer to the instantiated object.
    */
    fifo * fifo_construct( const unsigned int nMaxElements );

    /** Destructor of the fifo object.
        \param      obj             Pointer to the instantiated object.
    */
    void fifo_destroy( fifo * obj );

    /** Push an element in the fifo buffer.
        \param      obj             Pointer to the object.
        \param      element         Pointer to the element to be pushed.
        \return                     Return -1 if error, 0 otherwise.
    */
    int fifo_push( fifo * obj, const void * element );

    /** Pop an element from the fifo buffer.
        \param      obj             Pointer to the object.
        \return                     Return the popped element (returns NULL if error)
    */
    void * fifo_pop( fifo * obj );

#endif