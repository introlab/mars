#ifndef __MARS_INIT_SPACE
#define __MARS_INIT_SPACE

    #include <math.h>
    #include <stdlib.h>
    #include "../signal/triangle.h"
    #include "../signal/point.h"
    #include "../utils/sort.h"

    triangles_obj * space_triangles_level_zero(void);

    triangles_obj * space_triangles_level_next(const triangles_obj * triangles);

    triangles_obj * space_triangles_level_level(const unsigned int level);

    points_obj * space_points_triangles(const triangles_obj * triangles);

    points_obj * space_sphere(const unsigned int level);

    points_obj * space_halfsphere(const unsigned int level);

    points_obj * space_arc(const unsigned int level);

    float * space_points_hash(const points_obj * points);

    float space_triangles_shortestDistance(const triangles_obj * triangles);

#endif