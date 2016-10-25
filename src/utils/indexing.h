#ifndef __MARS_UTILS_INDEXING
#define __MARS_UTILS_INDEXING

	/**
	* \file 	indexing.h
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

	/** Wrap the index withing the positive range [0,N-1]
		\param		index		The index that is a signed integer
		\param		arraySize	The size of the range (N)
		\return					Wrapped index
	*/
	unsigned int indexing_wrap(const signed int index, const unsigned int arraySize);

	/** Cycle the index withing the positive range [0,N/2+1]
		\param		index		The index that is a signed integer
		\param		arraySize	The size of the range (N/2+1)
		\return					Cycled index
	*/
	unsigned int indexing_cycle(const signed int index, const unsigned int arraySize);

#endif