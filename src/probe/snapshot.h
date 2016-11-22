#ifndef __MARS_PROBE_SNAPSHOT
#define __MARS_PROBE_SNAPSHOT

    /**
    * \file     snapshot.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-11-07
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

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "../signal/vector.h"

    //! A structure that holds all the fields to take snapshots over time.
    typedef struct snapshot_obj {

        char * fileName;            ///< Name of the file to save snapshots.
        FILE * fp;                  ///< Pointer to the file stream.

    } snapshot_obj;

    /** Constructor of the object.    
        \param      fileName    Name of the file to save snapshots.
        \return                 Pointer to the instantiated object.
    */

    snapshot_obj * snapshot_construct(const char * fileName);

    /** Destructor of the object.
        \param      obj         Pointer to the instantiated object.
    */
    void snapshot_destroy(snapshot_obj * obj);

    /** Take a snapshot of a vector with signed integers.
        \param      obj         Pointer to the instantiated object.
        \param      vector      Pointer to the vector.
    */
    int snapshot_vector_signedint(snapshot_obj * obj, const vector_signedint * vector);

    /** Take a snapshot of a vector with unsigned integers.
        \param      obj         Pointer to the instantiated object.
        \param      vector      Pointer to the vector.
    */
    int snapshot_vector_unsignedint(snapshot_obj * obj, const vector_unsignedint * vector);    

    /** Take a snapshot of a vector with floats.
        \param      obj         Pointer to the instantiated object.
        \param      vector      Pointer to the vector.
    */
    int snapshot_vector_float(snapshot_obj * obj, const vector_float * vector);

#endif