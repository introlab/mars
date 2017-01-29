#ifndef __MARS_UTILS_FIFO
#define __MARS_UTILS_FIFO

    /**
    * \file     fifo.h
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
    #include <pthread.h>

    //! FIFO buffer.
    typedef struct fifo_obj {

        pthread_mutex_t mutex;                  ///< Mutex, to protect from reading/writing simultaneously to the buffer by two different threads.
        void ** buffer;                         ///< Buffer that holds all the pointers.
        unsigned int nMaxElements;              ///< Maximum number of elements that can be stored.
        unsigned int nElements;                 ///< Actual number of elements in the buffer.
        unsigned int iRead;                     ///< Reading pointer index.
        unsigned int iWrite;                    ///< Writing pointer index.

    } fifo_obj;

    /** Constructor. Initialize all fields.
        \param      nMaxElements    Maximum number of elements the buffer can store.
        \return                     Pointer to the instantiated object.
    */  
    fifo_obj * fifo_construct( const unsigned int nMaxElements );

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void fifo_destroy( fifo_obj * obj );

    /** Push the element in the buffer.
        \param      obj             Pointer to the object.
        \param      element         Pointer to the element to push in buffer.
        \return                     Returns 0 is element added, or -1 if buffer already full.
    */
    int fifo_push( fifo_obj * obj, const void * element );

    /** Pop the element from the buffer.
        \param      obj             Pointer to the object.
        \return                     Pointer to the popped element.
    */
    void * fifo_pop( fifo_obj * obj );

#endif