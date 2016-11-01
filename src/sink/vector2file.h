#ifndef __MARS_SINK_VECTOR2FILE
#define __MARS_SINK_VECTOR2FILE

    #include "../signal/vector.h"

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    /**
    * \file     vector2file.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-11-01
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

    typedef struct vector2file_obj {

        char * fileName;            ///< Name of the file.
        FILE * fp;                  ///< File pointer.        

    } vector2file_obj;

    vector2file_obj * vector2file_construct(const char * fileName);

    void vector2file_destroy(vector2file_obj * obj);

    int vector2file_process_signedchar(vector2file_obj * obj, const vector_signedchar * vector);

    int vector2file_process_unsignedchar(vector2file_obj * obj, const vector_unsignedchar * vector);

    int vector2file_process_signedshort(vector2file_obj * obj, const vector_signedshort * vector);

    int vector2file_process_unsignedshort(vector2file_obj * obj, const vector_unsignedshort * vector);

    int vector2file_process_signedint(vector2file_obj * obj, const vector_signedint * vector);

    int vector2file_process_unsignedint(vector2file_obj * obj, const vector_unsignedint * vector);

    int vector2file_process_float(vector2file_obj * obj, const vector_float * vector);

    int vector2file_process_double(vector2file_obj * obj, const vector_double * vector);

#endif