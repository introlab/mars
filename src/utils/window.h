#ifndef __MARS_UTILS_WINDOWS
#define __MARS_UTILS_WINDOWS

	#include "../signal/vector.h"

	/**
	* \file 	window.h
	* \author 	François Grondin <francois.grondin2@usherbrooke.ca>
	* \version  1.0
	* \date 	2016-10-25
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

	/** Instantiate a vector that contains a Hann window.
		\param		frameSize	Number of samples per frame.
		\return					Pointer to the instantiated vector.
	*/
	vector_float * window_hann(const unsigned short frameSize);

#endif