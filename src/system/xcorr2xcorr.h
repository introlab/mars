#ifndef __MARS_SYSTEM_XCORR
#define __MARS_SYSTEM_XCORR

    /**
    * \file     xcorr2xcorr.h
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

    #include "../signal/xcorr.h"
    #include "../signal/tdoa.h"

    //! Perform filtering on the cross-correlation vectors
    typedef struct xcorr2xcorr_obj {

        unsigned int frameSize;     ///< Number of samples per frame.

    } xcorr2xcorr_obj;

    /** Constructor. Initialize all fields to zero.
        \param      frameSize       Number of samples per frame.
        \return                     Pointer to the instantiated object.
    */   
    xcorr2xcorr_obj * xcorr2xcorr_construct_zero(const unsigned int frameSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void xcorr2xcorr_destroy(xcorr2xcorr_obj * obj);

    /** Compute the maximum value with a maximum sliding windows.
        \param      xcorr           Cross-correlation vector.
        \param      minTdoa         Minimum delay value.
        \param      maxTdoa         Maximum delay value.
        \param      delta           Delta 
        \param      xcorrMax        Filtered cross-correlation vector.
        \param      obj             Object to be used.
    */
    void xcorr2xcorr_process_max_single(xcorr2xcorr_obj * obj, const xcorr_obj * xcorr, const unsigned int minTdoa, const unsigned maxTdoa, const unsigned int delta, xcorr_obj * xcorrMax);

    /** Reset the delay in cross-correlation vector.
        \param      xcorr           Cross-correlation vector.
        \param      tdoa            Delay to be reset.
        \param      minTdoa         Minimum delay value.
        \param      maxTdoa         Maximum delay value.
        \param      delta           Delta 
        \param      xcorrReset      Filtered cross-correlation vector.
        \param      obj             Object to be used.
    */
    void xcorr2xcorr_process_reset_single(xcorr2xcorr_obj * obj, const xcorr_obj * xcorr, const unsigned int tdoa, const unsigned int minTdoa, const unsigned maxTdoa, const unsigned int delta, xcorr_obj * xcorrReset);

    /** Compute the maximum value with a maximum sliding windows.
        \param      xcorrs          Cross-correlation vectors.
        \param      minTdoas        Minimum delay values.
        \param      maxTdoas        Maximum delay values.
        \param      delta           Delta 
        \param      xcorrsMax       Filtered cross-correlation vectors.
        \param      obj             Object to be used.
    */
    void xcorr2xcorr_process_max_many(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoa_obj * minTdoas, const tdoa_obj * maxTdoas, const unsigned int delta, xcorrs_obj * xcorrsMax);

    /** Reset the delay in cross-correlation vectors.
        \param      xcorrs          Cross-correlation vectors.
        \param      tdoa            Delays to be reset.
        \param      minTdoas        Minimum delay values.
        \param      maxTdoas        Maximum delay values.
        \param      delta           Delta 
        \param      xcorrsReset     Filtered cross-correlation vectors.
        \param      obj             Object to be used.
    */
    void xcorr2xcorr_process_reset_many(xcorr2xcorr_obj * obj, const xcorrs_obj * xcorrs, const tdoa_obj * tdoa, const tdoa_obj * minTdoas, const tdoa_obj * maxTdoas, const unsigned int delta, xcorrs_obj * xcorrsReset);


#endif