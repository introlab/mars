#ifndef __MARS_SINK_TRACKS_FILE
#define __MARS_SINK_TRACKS_FILE

    /**
    * \file     snk_tracks.h
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
    #include <string.h>
    #include <math.h>
    #include <limits.h>

    #include "../message/msg_tracks.h"

    //! Sink to store the tracked sources
    typedef struct snk_tracks_file_obj {

        char * fileName;                ///< File name.
        FILE * fp;                      ///< File pointer.
        char format;                    ///< Storing format ("(b)in)" or "(x)ml").

    } snk_tracks_file_obj;    

    //! Configuration of the sink for tracked sources
    typedef struct snk_tracks_file_cfg {

        char * fileName;                ///< File name.
        char format;                    ///< Storing format ("(b)in" or "(x)ml").

    } snk_tracks_file_cfg;

    /** Constructor. Initialize all elements according to the configuration file.
        \param      cfg             Configuration.
        \return                     Pointer to the instantiated object.
    */  
    snk_tracks_file_obj * snk_tracks_file_construct(const snk_tracks_file_cfg * cfg);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void snk_tracks_file_destroy(snk_tracks_file_obj * obj);

    /** Store the potential sources as a XML or binary file, according to config.
        \param      msg_tracks      Message with tracked sources.
        \param      obj             Object to be used.
    */
    void snk_tracks_file_process(snk_tracks_file_obj * obj, msg_tracks_obj * msg_tracks);

    /** Store the potential sources as a XML file
        \param      msg_tracks      Message with tracked sources.
        \param      obj             Object to be used.
    */
    void snk_tracks_file_process_xml(snk_tracks_file_obj * obj, msg_tracks_obj * msg_tracks);

    /** Store the potential sources as a binary file
        \param      msg_tracks      Message with tracked sources.
        \param      obj             Object to be used.
    */
    void snk_tracks_file_process_bin(snk_tracks_file_obj * obj, msg_tracks_obj * msg_tracks);

    /** Constructor.
        \return                     Pointer to the instantiated object.
    */  
    snk_tracks_file_cfg * snk_tracks_file_cfg_construct(void);

    /** Destructor. Free memory.
        \param      cfg             Object to be destroyed.
    */
    void snk_tracks_file_cfg_destroy(snk_tracks_file_cfg * cfg);

#endif