#ifndef __MARS_SINK_POTS
#define __MARS_SINK_POTS

    /**
    * \file     snk_pots.h
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

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <math.h>
    #include <limits.h>

    #include "../message/msg_pots.h"

    //! A structure that holds all the fields to extract samples from a RAW file. 
    typedef struct snk_pots_obj {

        char * fileName;            ///< Name of the RAW file.
        FILE * fp;                  ///< File pointer.
        char * format;              ///< Format.

    } snk_pots_obj;    

    /** Constructor of the object.	
        \param      fileName    Name of the RAW file.
        \param      format      Output format ("xml" or "bin").
        \return                 Pointer to the instantiated object.
    */
    snk_pots_obj * snk_pots_construct(const char * fileName, const char * format);

    /** Destructor of the hop2raw object.
        \param      obj         Pointer to the instantiated object.
    */
    void snk_pots_destroy(snk_pots_obj * obj);

    /** Push the potential sources to a file.
        \param      obj         Pointer to the instantiated object.
        \param      pots        Pointer to a message of pots.
        \return                 Return -1 if an error occurs, 0 otherwise.
    */
    int snk_pots_process(snk_pots_obj * obj, msg_pots_obj * pots);

    /** Push the potential sources to a file in the XML format.
        \param      obj         Pointer to the instantiated object.
        \param      pots        Pointer to a message of pots.
        \return                 Return -1 if an error occurs, 0 otherwise.
    */
    int snk_pots_process_xml(snk_pots_obj * obj, msg_pots_obj * pots);

    /** Push the potential sources to a file in the binary format.
        \param      obj         Pointer to the instantiated object.
        \param      pots        Pointer to a message of pots.
        \return                 Return -1 if an error occurs, 0 otherwise.
    */
    int snk_pots_process_bin(snk_pots_obj * obj, msg_pots_obj * pots);

#endif