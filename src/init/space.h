#ifndef __MARS_INIT_SPACE
#define __MARS_INIT_SPACE

    /**
    * \file     space.h
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

    #include <math.h>
    #include <stdlib.h>
    #include "../signal/triangle.h"
    #include "../signal/point.h"

    /** Divide a triangle in multiple triangles.
        \param      triangle            Triangle to be divided.
        \return                         Generated triangles.
    */
    triangles_obj * space_triangles_triangle_divide(const triangle_obj * triangle);

    /** Generate the triangles on the first level.
        \return                         Generated triangles.
    */
    triangles_obj * space_triangles_level_zero(void);

    /** Generate triangles on the next level.
        \param      triangles           Triangles on the previous level.
        \return                         Generated triangles on the next level.
    */
    triangles_obj * space_triangles_level_next(const triangles_obj * triangles);

    /** Generate triangles at a given level.
        \param      level               Level at which triangles are generated.
        \return                         Generated triangles at the given level.
    */
    triangles_obj * space_triangles_level_level(const unsigned int level);

    /** Compute the distance between two points.
        \param      point1              First point.
        \param      point2              Second point.
        \return                         Distance between both points.
    */
    float space_point_dist(const point_obj * point1, const point_obj * point2);

    /** Generate a the point between the two provided points.
        \param      point1              First point.
        \param      point2              Second point.
        \return                         Point in the middle.
    */
    point_obj * space_point_point(const point_obj * point1, const point_obj * point2);

    /** Generate points from triangles.
        \param      triangles           List of triangles.
        \return                         Generated points.
    */
    points_obj * space_points_triangles(const triangles_obj * triangles);

    /** Generate unique points from redundant points.
        \param      points              Redundant points.
        \return                         Unique points.
    */
    points_obj * space_points_points(const points_obj * points);

    /** Generate a sphere with given resolution level.
        \param      level               Level.
        \return                         Points that make the sphere.
    */
    points_obj * space_sphere(const unsigned int level);

    /** Generate a halfsphere with given resolution level.
        \param      level               Level.
        \return                         Points that make the halfsphere.
    */
    points_obj * space_halfsphere(const unsigned int level);

#endif