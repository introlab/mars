#ifndef __MARS_SIGNAL_POSTPROB
#define __MARS_SIGNAL_POSTPROB

    /**
    * \file     postprob.h
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

    //! Posteriori probability
    typedef struct postprob_obj {

        unsigned int nPots;         ///< Number of potential sources.
        float * probs;              ///< Posteriori probability \f$p(src|\mathbf{E}^s_l,\mathbf{z}^s_l)\f$
        float probTotal;            ///< Total probability for a given tracked source (or new source) \f$p(src|\mathbf{E}_l,\mathbf{z}_l)\f$

    } postprob_obj;

    //! Posteriori probabilities
    typedef struct postprobs_obj {

        unsigned int nTracks;       ///< Number of tracked sources.

        postprob_obj ** p_track;    ///< Posteriori probabilities for each tracked source \f$p(t|\mathbf{E}^s_l,\mathbf{z}^s_l)\f$ and \f$p(t|\mathbf{E}_l,\mathbf{z}_l)\f$
        postprob_obj * p_new;       ///< Posteriori probabilities for a new source \f$p(new|\mathbf{E}^s_l,\mathbf{z}^s_l)\f$ and \f$p(new|\mathbf{E}_l,\mathbf{z}_l)\f$

    } postprobs_obj;    

    /** Constructor. Initialize all coordinates to zero.
        \param      nPots           Number of potential sources.
        \return                     Pointer to the instantiated object.
    */
    postprob_obj * postprob_construct_zero(const unsigned int nPots);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void postprob_destroy(postprob_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void postprob_printf(const postprob_obj * obj);

    /** Constructor. Initialize the list of objects with instantiated objects with fields set to zero.
        \param      nPots           Number of potential sources.
        \param      nTracks         Number of tracked sources.
        \return                     Pointer to the instantiated object.
    */
    postprobs_obj * postprobs_construct_zero(const unsigned int nPots, const unsigned int nTracks);    

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void postprobs_destroy(postprobs_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void postprobs_printf(const postprobs_obj * obj);

#endif