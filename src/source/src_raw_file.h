#ifndef __MARS_SOURCE_RAW_FILE
#define __MARS_SOURCE_RAW_FILE

    /**
    * \file     src_raw_file.h
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

    #include "../message/msg_hops.h"
    #include "../utils/pcm.h"

    #include <stdio.h>
    #include <math.h>
    #include <limits.h>
    #include <string.h>

    //! Source to generate samples from a RAW file
    typedef struct src_raw_file_obj {

        unsigned long long timeStamp;   ///< Time stamp.

        unsigned int hopSize;           ///< Number of samples per hop.
        unsigned int nMics;             ///< Number of microphones.
        unsigned int nBits;             ///< Number of bits per sample.
        char * fileName;                ///< File name.
        FILE * fp;                      ///< File pointer.

    } src_raw_file_obj;

    //! Configuration of the source for a RAW file
    typedef struct src_raw_file_cfg {

        unsigned int hopSize;           ///< Number of samples per hop.
        unsigned int nMics;             ///< Number of microphones.
        unsigned int nBits;             ///< Number of bits per sample.
        char * fileName;                ///< File name.

    } src_raw_file_cfg;

    /** Constructor. Initialize all elements according to the configuration file.
        \param      cfg             Configuration.
        \return                     Pointer to the instantiated object.
    */  
    src_raw_file_obj * src_raw_file_construct(const src_raw_file_cfg * cfg);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void src_raw_file_destroy(src_raw_file_obj * obj);

    /** Get samples from the file.
        \param      hops            List of hops where to get the samples.
        \param      obj             Object to be used.
        \return                     Returns -1 if end of file is reached.
    */
    int src_raw_file_process(src_raw_file_obj * obj, msg_hops_obj * hops);

    /** Constructor.
        \return                     Pointer to the instantiated object.
    */ 
    src_raw_file_cfg * src_raw_file_cfg_construct(void);

    /** Destructor. Free memory.
        \param      cfg             Object to be destroyed.
    */
    void src_raw_file_cfg_destroy(src_raw_file_cfg * cfg);

#endif