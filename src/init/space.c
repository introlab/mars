
    #include "space.h"

    triangles_obj * space_triangles_triangle_divide(const triangle_obj * triangle) {

        triangles_obj * triangles;
        point_obj * point1;
        point_obj * point2;
        point_obj * point3;
        point_obj * pointA;
        point_obj * pointB;
        point_obj * pointC;

        triangles = triangles_construct_null(4);

        pointA = triangle->pointA;
        pointB = triangle->pointB;
        pointC = triangle->pointC;

        point1 = space_point_point(pointA, pointB);
        point2 = space_point_point(pointB, pointC);
        point3 = space_point_point(pointC, pointA);

        triangles->array[0] = triangle_construct_point(pointA, point1, point3);
        triangles->array[1] = triangle_construct_point(point1, pointB, point2);
        triangles->array[2] = triangle_construct_point(point1, point2, point3);
        triangles->array[3] = triangle_construct_point(point3, point2, pointC);

        point_destroy(point1);
        point_destroy(point2);
        point_destroy(point3);

        return triangles;

    }

    triangles_obj * space_triangles_level_zero(void) {

        points_obj * points;
        triangles_obj * triangles;
        
        unsigned int iPoint;
        unsigned int iTriangle;

        float h,r;

        h = sqrtf(5.0f)/5.0f;
        r = (2.0f/5.0f)*sqrtf(5.0f);

        points = points_construct_null(12);

        points->array[0] = point_construct_xyz(0.0f, 0.0f, 1.0f);
        points->array[11] = point_construct_xyz(0.0f, 0.0f, -1.0f);        

        for (iPoint = 0; iPoint < 5; iPoint++) {

            points->array[iPoint+1] = point_construct_xyz(r * sinf(2*M_PI*((float) iPoint)/5.0f), 
                                                        r * cosf(2*M_PI*((float) iPoint)/5.0f), 
                                                        h);

            points->array[iPoint+6] = point_construct_xyz(-1.0f * r * sinf(2*M_PI*((float) iPoint)/5.0f), 
                                                          -1.0f * r * cosf(2*M_PI*((float) iPoint)/5.0f), 
                                                          -1.0f * h);

        }        

        triangles = triangles_construct_null(20);

        triangles->array[0] = triangle_construct_point(points->array[0], points->array[2], points->array[1]);
        triangles->array[1] = triangle_construct_point(points->array[0], points->array[3], points->array[2]);
        triangles->array[2] = triangle_construct_point(points->array[0], points->array[4], points->array[3]);
        triangles->array[3] = triangle_construct_point(points->array[0], points->array[5], points->array[4]);
        triangles->array[4] = triangle_construct_point(points->array[0], points->array[1], points->array[5]);
        triangles->array[5] = triangle_construct_point(points->array[9], points->array[1], points->array[2]);
        triangles->array[6] = triangle_construct_point(points->array[10], points->array[2], points->array[3]);
        triangles->array[7] = triangle_construct_point(points->array[6], points->array[3], points->array[4]);
        triangles->array[8] = triangle_construct_point(points->array[7], points->array[4], points->array[5]);
        triangles->array[9] = triangle_construct_point(points->array[8], points->array[5], points->array[1]);
        triangles->array[10] = triangle_construct_point(points->array[4], points->array[7], points->array[6]);
        triangles->array[11] = triangle_construct_point(points->array[5], points->array[8], points->array[7]);
        triangles->array[12] = triangle_construct_point(points->array[1], points->array[9], points->array[8]);
        triangles->array[13] = triangle_construct_point(points->array[2], points->array[10], points->array[9]);
        triangles->array[14] = triangle_construct_point(points->array[3], points->array[6], points->array[10]);
        triangles->array[15] = triangle_construct_point(points->array[11], points->array[6], points->array[7]);
        triangles->array[16] = triangle_construct_point(points->array[11], points->array[7], points->array[8]);
        triangles->array[17] = triangle_construct_point(points->array[11], points->array[8], points->array[9]);
        triangles->array[18] = triangle_construct_point(points->array[11], points->array[9], points->array[10]);
        triangles->array[19] = triangle_construct_point(points->array[11], points->array[10], points->array[6]);

        points_destroy(points);

        return triangles;

    }

    triangles_obj * space_triangles_level_next(const triangles_obj * triangles) {

        triangles_obj * obj;
        triangles_obj * divided;
        unsigned int iSignal;

        obj = triangles_construct_null(triangles->nSignals * 4);

        for (iSignal = 0; iSignal < triangles->nSignals; iSignal++) {

            divided = space_triangles_triangle_divide(triangles->array[iSignal]);

            obj->array[iSignal*4+0] = triangle_construct_triangle(divided->array[0]);
            obj->array[iSignal*4+1] = triangle_construct_triangle(divided->array[1]);
            obj->array[iSignal*4+2] = triangle_construct_triangle(divided->array[2]);
            obj->array[iSignal*4+3] = triangle_construct_triangle(divided->array[3]);

            triangles_destroy(divided);

        }

        return obj;

    }

    triangles_obj * space_triangles_level_level(const unsigned int level) {

        triangles_obj * obj;
        triangles_obj * triangles;
        unsigned int iLevel;

        obj = space_triangles_level_zero();

        for (iLevel = 0; iLevel < level; iLevel++) {
            triangles = space_triangles_level_next(obj);
            triangles_destroy(obj);
            obj = triangles;
        }

        return obj;

    }

    float space_point_dist(const point_obj * point1, const point_obj * point2) {

        float dx, dy, dz;
        float dist;

        dx = point1->coord->x - point2->coord->x;
        dy = point1->coord->y - point2->coord->y;
        dz = point1->coord->z - point2->coord->z;

        dist = sqrtf(dx * dx + dy * dy + dz * dz);

        return dist;

    }

    point_obj * space_point_point(const point_obj * point1, const point_obj * point2) {

        point_obj * obj;
        float x1, y1, z1;
        float x2, y2, z2;
        float x12, y12, z12;
        float norm12;       

        x1 = point1->coord->x;
        y1 = point1->coord->y;
        z1 = point1->coord->z;
        x2 = point2->coord->x;
        y2 = point2->coord->y;
        z2 = point2->coord->z;

        x12 = x1 + x2;
        y12 = y1 + y2;
        z12 = z1 + z2;

        norm12 = sqrtf(x12*x12+y12*y12+z12*z12);

        x12 = x12 / norm12;
        y12 = y12 / norm12;
        z12 = z12 / norm12;

        obj = point_construct_xyz(x12,y12,z12);

        return obj;

    }

    points_obj * space_points_triangles(const triangles_obj * triangles) {

        points_obj * obj;
        unsigned int iSignal;

        obj = points_construct_null(triangles->nSignals * 3);

        for (iSignal = 0; iSignal < triangles->nSignals; iSignal++) {

            obj->array[iSignal*3+0] = point_construct_point(triangles->array[iSignal]->pointA);
            obj->array[iSignal*3+1] = point_construct_point(triangles->array[iSignal]->pointB);
            obj->array[iSignal*3+2] = point_construct_point(triangles->array[iSignal]->pointC);

        }

        return obj;

    }

    points_obj * space_points_points(const points_obj * points) {

        points_obj * obj;
        points_obj * tmp;

        unsigned int iSignal1;
        unsigned int iSignal2;
        unsigned int nSignalsUnique;
        unsigned char match;

        tmp = points_construct_null(points->nSignals);
        nSignalsUnique = 0;

        for (iSignal1 = 0; iSignal1 < points->nSignals; iSignal1++) {

            match = 0;

            for (iSignal2 = 0; iSignal2 < nSignalsUnique; iSignal2++) {

                if (space_point_dist(points->array[iSignal1], tmp->array[iSignal2]) < 1E-10) {

                    match = 1;
                    break;

                }

            }

            if (match == 0) {

                tmp->array[nSignalsUnique] = point_construct_point(points->array[iSignal1]);
                nSignalsUnique++;

            }

        }

        obj = points_construct_null(nSignalsUnique);

        for (iSignal1 = 0; iSignal1 < nSignalsUnique; iSignal1++) {
            obj->array[iSignal1] = point_construct_point(tmp->array[iSignal1]);
        }

        points_destroy(tmp);

        return obj;

    }

    points_obj * space_sphere(const unsigned int level) {

        points_obj * obj;

        triangles_obj * triangles;
        points_obj * points;

        triangles = space_triangles_level_level(level);
        points = space_points_triangles(triangles);
        obj = space_points_points(points);

        triangles_destroy(triangles);
        points_destroy(points);

        return obj;

    }

    points_obj * space_halfsphere(const unsigned int level) {

        points_obj * obj;

        triangles_obj * triangles;
        points_obj * points;
        points_obj * pointsSphere;
        unsigned int nSignals;
        unsigned int iSignal;

        triangles = space_triangles_level_level(level);
        points = space_points_triangles(triangles);
        pointsSphere = space_points_points(points);

        nSignals = 0;

        for (iSignal = 0; iSignal < pointsSphere->nSignals; iSignal++) {
        
            if (pointsSphere->array[iSignal]->coord->z >= 0.0f) {
            
                nSignals++;

            }

        }

        obj = points_construct_null(nSignals);
        nSignals = 0;

        for (iSignal = 0; iSignal < pointsSphere->nSignals; iSignal++) {

            if (pointsSphere->array[iSignal]->coord->z >= 0.0f) {
            
                obj->array[nSignals] = point_construct_point(pointsSphere->array[iSignal]);
                nSignals++;

            }

        }

        triangles_destroy(triangles);
        points_destroy(points);        
        points_destroy(pointsSphere);

        return obj;

    }