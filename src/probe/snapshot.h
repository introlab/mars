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

    typedef struct snapshot_obj {

        char * fileName;
        FILE * fp;

    } snapshot_obj;

    snapshot_obj * snapshot_construct(const char * fileName);

    void snapshot_destroy(snapshot_obj * obj);

    int snapshot_vector_signedint(snapshot_obj * obj, const vector_signedint * vector);

    int snapshot_vector_unsignedint(snapshot_obj * obj, const vector_unsignedint * vector);    

    int snapshot_vector_float(snapshot_obj * obj, const vector_float * vector);

#endif