#ifndef __MARS_SIGNAL_SCAN
#define __MARS_SIGNAL_SCAN

    /**
    * \file     scan.h
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

    #include "point.h"
    #include "tdoa.h"
    #include "index.h"

    //! Scan setup
    typedef struct scan_obj {

        points_obj * points;            ///< Points to scan.
        tdoas_obj * tdoas;              ///< TDOAs associated to each point to scan.
        indexes_obj * indexes;          ///< Indexes of points to scan according to the previous point selected at earlier stage.
        tdoa_obj * tdoaMin;             ///< Minimum TDOAs values.
        tdoa_obj * tdoaMax;             ///< Maximum TDOAs values.

    } scan_obj;

    //! Scan setups
    typedef struct scans_obj {

        unsigned int nSignals;          ///< Number of scan setups.
        scan_obj ** array;              ///< List of scan setups.

    } scans_obj;

    /** Constructor. Initialize all pointers to null.
        \return                     Pointer to the instantiaed object.
    */
    scan_obj * scan_construct_null(void);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void scan_destroy(scan_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void scan_printf(scan_obj * obj);    

    /** Constructor. Initialize the list of objects with null pointers.
        \param      nSignals        Number of microphones.
        \return                     Pointer to the instantiaed object.
    */
    scans_obj * scans_construct_null(const unsigned int nSignals);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void scans_destroy(scans_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void scans_printf(scans_obj * obj);

#endif