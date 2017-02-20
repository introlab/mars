
    #include "space.h"

    triangles_obj * space_triangles_level_zero(void) {

        points_obj * points;
        triangles_obj * triangles;
        
        unsigned int iPoint;
        unsigned int iTriangle;

        float h,r;

        h = sqrtf(5.0f)/5.0f;
        r = (2.0f/5.0f)*sqrtf(5.0f);

        points = points_construct_zero(12);

        points->array[0 * 3 + 0] = 0.0f;
        points->array[0 * 3 + 1] = 0.0f;
        points->array[0 * 3 + 2] = 1.0f;
        points->array[11 * 3 + 0] = 0.0f;
        points->array[11 * 3 + 1] = 0.0f;
        points->array[11 * 3 + 2] = -1.0f;

        for (iPoint = 0; iPoint < 5; iPoint++) {

            points->array[(iPoint+1) * 3 + 0] = r * sinf(2*M_PI*((float) iPoint)/5.0f);
            points->array[(iPoint+1) * 3 + 1] = r * cosf(2*M_PI*((float) iPoint)/5.0f);
            points->array[(iPoint+1) * 3 + 2] = h;

            points->array[(iPoint+6) * 3 + 0] = -1.0f * r * sinf(2*M_PI*((float) iPoint)/5.0f);
            points->array[(iPoint+6) * 3 + 1] = -1.0f * r * cosf(2*M_PI*((float) iPoint)/5.0f);
            points->array[(iPoint+6) * 3 + 2] = -1.0f * h;

        }        

        triangles = triangles_construct_zero(20);

        // Triangle 0: Points 0, 2, 1
        triangles->array[0 * 9 + 0] = points->array[0 * 3 + 0];
        triangles->array[0 * 9 + 1] = points->array[0 * 3 + 1];
        triangles->array[0 * 9 + 2] = points->array[0 * 3 + 2];
        triangles->array[0 * 9 + 3] = points->array[2 * 3 + 0];
        triangles->array[0 * 9 + 4] = points->array[2 * 3 + 1];
        triangles->array[0 * 9 + 5] = points->array[2 * 3 + 2];
        triangles->array[0 * 9 + 6] = points->array[1 * 3 + 0];
        triangles->array[0 * 9 + 7] = points->array[1 * 3 + 1];
        triangles->array[0 * 9 + 8] = points->array[1 * 3 + 2];

        // Triangle 1: Points 0, 3, 2
        triangles->array[1 * 9 + 0] = points->array[0 * 3 + 0];
        triangles->array[1 * 9 + 1] = points->array[0 * 3 + 1];
        triangles->array[1 * 9 + 2] = points->array[0 * 3 + 2];
        triangles->array[1 * 9 + 3] = points->array[3 * 3 + 0];
        triangles->array[1 * 9 + 4] = points->array[3 * 3 + 1];
        triangles->array[1 * 9 + 5] = points->array[3 * 3 + 2];
        triangles->array[1 * 9 + 6] = points->array[2 * 3 + 0];
        triangles->array[1 * 9 + 7] = points->array[2 * 3 + 1];
        triangles->array[1 * 9 + 8] = points->array[2 * 3 + 2];

        // Triangle 2: Points 0, 4, 3
        triangles->array[2 * 9 + 0] = points->array[0 * 3 + 0];
        triangles->array[2 * 9 + 1] = points->array[0 * 3 + 1];
        triangles->array[2 * 9 + 2] = points->array[0 * 3 + 2];
        triangles->array[2 * 9 + 3] = points->array[4 * 3 + 0];
        triangles->array[2 * 9 + 4] = points->array[4 * 3 + 1];
        triangles->array[2 * 9 + 5] = points->array[4 * 3 + 2];
        triangles->array[2 * 9 + 6] = points->array[3 * 3 + 0];
        triangles->array[2 * 9 + 7] = points->array[3 * 3 + 1];
        triangles->array[2 * 9 + 8] = points->array[3 * 3 + 2];
        
        // Triangle 3: Points 0, 5, 4
        triangles->array[3 * 9 + 0] = points->array[0 * 3 + 0];
        triangles->array[3 * 9 + 1] = points->array[0 * 3 + 1];
        triangles->array[3 * 9 + 2] = points->array[0 * 3 + 2];
        triangles->array[3 * 9 + 3] = points->array[5 * 3 + 0];
        triangles->array[3 * 9 + 4] = points->array[5 * 3 + 1];
        triangles->array[3 * 9 + 5] = points->array[5 * 3 + 2];
        triangles->array[3 * 9 + 6] = points->array[4 * 3 + 0];
        triangles->array[3 * 9 + 7] = points->array[4 * 3 + 1];
        triangles->array[3 * 9 + 8] = points->array[4 * 3 + 2];

        // Triangle 4: Points 0, 1, 5
        triangles->array[4 * 9 + 0] = points->array[0 * 3 + 0];
        triangles->array[4 * 9 + 1] = points->array[0 * 3 + 1];
        triangles->array[4 * 9 + 2] = points->array[0 * 3 + 2];
        triangles->array[4 * 9 + 3] = points->array[1 * 3 + 0];
        triangles->array[4 * 9 + 4] = points->array[1 * 3 + 1];
        triangles->array[4 * 9 + 5] = points->array[1 * 3 + 2];
        triangles->array[4 * 9 + 6] = points->array[5 * 3 + 0];
        triangles->array[4 * 9 + 7] = points->array[5 * 3 + 1];
        triangles->array[4 * 9 + 8] = points->array[5 * 3 + 2];

        // Triangle 5: Points 9, 1, 2
        triangles->array[5 * 9 + 0] = points->array[9 * 3 + 0];
        triangles->array[5 * 9 + 1] = points->array[9 * 3 + 1];
        triangles->array[5 * 9 + 2] = points->array[9 * 3 + 2];
        triangles->array[5 * 9 + 3] = points->array[1 * 3 + 0];
        triangles->array[5 * 9 + 4] = points->array[1 * 3 + 1];
        triangles->array[5 * 9 + 5] = points->array[1 * 3 + 2];
        triangles->array[5 * 9 + 6] = points->array[2 * 3 + 0];
        triangles->array[5 * 9 + 7] = points->array[2 * 3 + 1];
        triangles->array[5 * 9 + 8] = points->array[2 * 3 + 2];

        // Triangle 6: Points 10, 2, 3
        triangles->array[6 * 9 + 0] = points->array[10 * 3 + 0];
        triangles->array[6 * 9 + 1] = points->array[10 * 3 + 1];
        triangles->array[6 * 9 + 2] = points->array[10 * 3 + 2];
        triangles->array[6 * 9 + 3] = points->array[2 * 3 + 0];
        triangles->array[6 * 9 + 4] = points->array[2 * 3 + 1];
        triangles->array[6 * 9 + 5] = points->array[2 * 3 + 2];
        triangles->array[6 * 9 + 6] = points->array[3 * 3 + 0];
        triangles->array[6 * 9 + 7] = points->array[3 * 3 + 1];
        triangles->array[6 * 9 + 8] = points->array[3 * 3 + 2];

        // Triangle 7: Points 6, 3, 4
        triangles->array[7 * 9 + 0] = points->array[6 * 3 + 0];
        triangles->array[7 * 9 + 1] = points->array[6 * 3 + 1];
        triangles->array[7 * 9 + 2] = points->array[6 * 3 + 2];
        triangles->array[7 * 9 + 3] = points->array[3 * 3 + 0];
        triangles->array[7 * 9 + 4] = points->array[3 * 3 + 1];
        triangles->array[7 * 9 + 5] = points->array[3 * 3 + 2];
        triangles->array[7 * 9 + 6] = points->array[4 * 3 + 0];
        triangles->array[7 * 9 + 7] = points->array[4 * 3 + 1];
        triangles->array[7 * 9 + 8] = points->array[4 * 3 + 2];
        
        // Triangle 8: Points 7, 4, 5
        triangles->array[8 * 9 + 0] = points->array[7 * 3 + 0];
        triangles->array[8 * 9 + 1] = points->array[7 * 3 + 1];
        triangles->array[8 * 9 + 2] = points->array[7 * 3 + 2];
        triangles->array[8 * 9 + 3] = points->array[4 * 3 + 0];
        triangles->array[8 * 9 + 4] = points->array[4 * 3 + 1];
        triangles->array[8 * 9 + 5] = points->array[4 * 3 + 2];
        triangles->array[8 * 9 + 6] = points->array[5 * 3 + 0];
        triangles->array[8 * 9 + 7] = points->array[5 * 3 + 1];
        triangles->array[8 * 9 + 8] = points->array[5 * 3 + 2];

        // Triangle 9: Points 8, 5, 1
        triangles->array[9 * 9 + 0] = points->array[8 * 3 + 0];
        triangles->array[9 * 9 + 1] = points->array[8 * 3 + 1];
        triangles->array[9 * 9 + 2] = points->array[8 * 3 + 2];
        triangles->array[9 * 9 + 3] = points->array[5 * 3 + 0];
        triangles->array[9 * 9 + 4] = points->array[5 * 3 + 1];
        triangles->array[9 * 9 + 5] = points->array[5 * 3 + 2];
        triangles->array[9 * 9 + 6] = points->array[1 * 3 + 0];
        triangles->array[9 * 9 + 7] = points->array[1 * 3 + 1];
        triangles->array[9 * 9 + 8] = points->array[1 * 3 + 2];

        // Triangle 10: Points 4, 7, 6
        triangles->array[10 * 9 + 0] = points->array[4 * 3 + 0];
        triangles->array[10 * 9 + 1] = points->array[4 * 3 + 1];
        triangles->array[10 * 9 + 2] = points->array[4 * 3 + 2];
        triangles->array[10 * 9 + 3] = points->array[7 * 3 + 0];
        triangles->array[10 * 9 + 4] = points->array[7 * 3 + 1];
        triangles->array[10 * 9 + 5] = points->array[7 * 3 + 2];
        triangles->array[10 * 9 + 6] = points->array[6 * 3 + 0];
        triangles->array[10 * 9 + 7] = points->array[6 * 3 + 1];
        triangles->array[10 * 9 + 8] = points->array[6 * 3 + 2];
        
        // Triangle 11: Points 5, 8, 7
        triangles->array[11 * 9 + 0] = points->array[5 * 3 + 0];
        triangles->array[11 * 9 + 1] = points->array[5 * 3 + 1];
        triangles->array[11 * 9 + 2] = points->array[5 * 3 + 2];
        triangles->array[11 * 9 + 3] = points->array[8 * 3 + 0];
        triangles->array[11 * 9 + 4] = points->array[8 * 3 + 1];
        triangles->array[11 * 9 + 5] = points->array[8 * 3 + 2];
        triangles->array[11 * 9 + 6] = points->array[7 * 3 + 0];
        triangles->array[11 * 9 + 7] = points->array[7 * 3 + 1];
        triangles->array[11 * 9 + 8] = points->array[7 * 3 + 2];
        
        // Triangle 12: Points 1, 9, 8
        triangles->array[12 * 9 + 0] = points->array[1 * 3 + 0];
        triangles->array[12 * 9 + 1] = points->array[1 * 3 + 1];
        triangles->array[12 * 9 + 2] = points->array[1 * 3 + 2];
        triangles->array[12 * 9 + 3] = points->array[9 * 3 + 0];
        triangles->array[12 * 9 + 4] = points->array[9 * 3 + 1];
        triangles->array[12 * 9 + 5] = points->array[9 * 3 + 2];
        triangles->array[12 * 9 + 6] = points->array[8 * 3 + 0];
        triangles->array[12 * 9 + 7] = points->array[8 * 3 + 1];
        triangles->array[12 * 9 + 8] = points->array[8 * 3 + 2];

        // Triangle 13: Points 2, 10, 9
        triangles->array[13 * 9 + 0] = points->array[2 * 3 + 0];
        triangles->array[13 * 9 + 1] = points->array[2 * 3 + 1];
        triangles->array[13 * 9 + 2] = points->array[2 * 3 + 2];
        triangles->array[13 * 9 + 3] = points->array[10 * 3 + 0];
        triangles->array[13 * 9 + 4] = points->array[10 * 3 + 1];
        triangles->array[13 * 9 + 5] = points->array[10 * 3 + 2];
        triangles->array[13 * 9 + 6] = points->array[9 * 3 + 0];
        triangles->array[13 * 9 + 7] = points->array[9 * 3 + 1];
        triangles->array[13 * 9 + 8] = points->array[9 * 3 + 2];

        // Triangle 14: Points 3, 6, 10
        triangles->array[14 * 9 + 0] = points->array[3 * 3 + 0];
        triangles->array[14 * 9 + 1] = points->array[3 * 3 + 1];
        triangles->array[14 * 9 + 2] = points->array[3 * 3 + 2];
        triangles->array[14 * 9 + 3] = points->array[6 * 3 + 0];
        triangles->array[14 * 9 + 4] = points->array[6 * 3 + 1];
        triangles->array[14 * 9 + 5] = points->array[6 * 3 + 2];
        triangles->array[14 * 9 + 6] = points->array[10 * 3 + 0];
        triangles->array[14 * 9 + 7] = points->array[10 * 3 + 1];
        triangles->array[14 * 9 + 8] = points->array[10 * 3 + 2];

        // Triangle 15: Points 11, 6, 7
        triangles->array[15 * 9 + 0] = points->array[11 * 3 + 0];
        triangles->array[15 * 9 + 1] = points->array[11 * 3 + 1];
        triangles->array[15 * 9 + 2] = points->array[11 * 3 + 2];
        triangles->array[15 * 9 + 3] = points->array[6 * 3 + 0];
        triangles->array[15 * 9 + 4] = points->array[6 * 3 + 1];
        triangles->array[15 * 9 + 5] = points->array[6 * 3 + 2];
        triangles->array[15 * 9 + 6] = points->array[7 * 3 + 0];
        triangles->array[15 * 9 + 7] = points->array[7 * 3 + 1];
        triangles->array[15 * 9 + 8] = points->array[7 * 3 + 2];

        // Triangle 16: Points 11, 7, 8
        triangles->array[16 * 9 + 0] = points->array[11 * 3 + 0];
        triangles->array[16 * 9 + 1] = points->array[11 * 3 + 1];
        triangles->array[16 * 9 + 2] = points->array[11 * 3 + 2];
        triangles->array[16 * 9 + 3] = points->array[7 * 3 + 0];
        triangles->array[16 * 9 + 4] = points->array[7 * 3 + 1];
        triangles->array[16 * 9 + 5] = points->array[7 * 3 + 2];
        triangles->array[16 * 9 + 6] = points->array[8 * 3 + 0];
        triangles->array[16 * 9 + 7] = points->array[8 * 3 + 1];
        triangles->array[16 * 9 + 8] = points->array[8 * 3 + 2];
        
        // Triangle 17: Points 11, 8, 9
        triangles->array[17 * 9 + 0] = points->array[11 * 3 + 0];
        triangles->array[17 * 9 + 1] = points->array[11 * 3 + 1];
        triangles->array[17 * 9 + 2] = points->array[11 * 3 + 2];
        triangles->array[17 * 9 + 3] = points->array[8 * 3 + 0];
        triangles->array[17 * 9 + 4] = points->array[8 * 3 + 1];
        triangles->array[17 * 9 + 5] = points->array[8 * 3 + 2];
        triangles->array[17 * 9 + 6] = points->array[9 * 3 + 0];
        triangles->array[17 * 9 + 7] = points->array[9 * 3 + 1];
        triangles->array[17 * 9 + 8] = points->array[9 * 3 + 2];

        // Triangle 18: Points 11, 9, 10
        triangles->array[18 * 9 + 0] = points->array[11 * 3 + 0];
        triangles->array[18 * 9 + 1] = points->array[11 * 3 + 1];
        triangles->array[18 * 9 + 2] = points->array[11 * 3 + 2];
        triangles->array[18 * 9 + 3] = points->array[9 * 3 + 0];
        triangles->array[18 * 9 + 4] = points->array[9 * 3 + 1];
        triangles->array[18 * 9 + 5] = points->array[9 * 3 + 2];
        triangles->array[18 * 9 + 6] = points->array[10 * 3 + 0];
        triangles->array[18 * 9 + 7] = points->array[10 * 3 + 1];
        triangles->array[18 * 9 + 8] = points->array[10 * 3 + 2];

        // Triangle 19: Points 11, 10, 6
        triangles->array[19 * 9 + 0] = points->array[11 * 3 + 0];
        triangles->array[19 * 9 + 1] = points->array[11 * 3 + 1];
        triangles->array[19 * 9 + 2] = points->array[11 * 3 + 2];
        triangles->array[19 * 9 + 3] = points->array[10 * 3 + 0];
        triangles->array[19 * 9 + 4] = points->array[10 * 3 + 1];
        triangles->array[19 * 9 + 5] = points->array[10 * 3 + 2];
        triangles->array[19 * 9 + 6] = points->array[6 * 3 + 0];
        triangles->array[19 * 9 + 7] = points->array[6 * 3 + 1];
        triangles->array[19 * 9 + 8] = points->array[6 * 3 + 2];

        points_destroy(points);

        return triangles;

    }

    triangles_obj * space_triangles_level_next(const triangles_obj * triangles) {

        triangles_obj * obj;
        unsigned int iTriangle;

        float point1[3];
        float point2[3];
        float point3[3];
        float pointA[3];
        float pointB[3];
        float pointC[3];
        float norm1;
        float norm2;
        float norm3;

        obj = triangles_construct_zero(triangles->nTriangles * 4);

        for (iTriangle = 0; iTriangle < triangles->nTriangles; iTriangle++) {

            pointA[0] = triangles->array[iTriangle*9+0];
            pointA[1] = triangles->array[iTriangle*9+1];
            pointA[2] = triangles->array[iTriangle*9+2];
            pointB[0] = triangles->array[iTriangle*9+3];
            pointB[1] = triangles->array[iTriangle*9+4];
            pointB[2] = triangles->array[iTriangle*9+5];
            pointC[0] = triangles->array[iTriangle*9+6];
            pointC[1] = triangles->array[iTriangle*9+7];
            pointC[2] = triangles->array[iTriangle*9+8];

            point1[0] = pointA[0] + pointB[0];
            point1[1] = pointA[1] + pointB[1];
            point1[2] = pointA[2] + pointB[2];
            point2[0] = pointB[0] + pointC[0];
            point2[1] = pointB[1] + pointC[1];
            point2[2] = pointB[2] + pointC[2];
            point3[0] = pointC[0] + pointA[0];
            point3[1] = pointC[1] + pointA[1];
            point3[2] = pointC[2] + pointA[2];

            norm1 = sqrtf(point1[0] * point1[0] + point1[1] * point1[1] + point1[2] * point1[2]);
            norm2 = sqrtf(point2[0] * point2[0] + point2[1] * point2[1] + point2[2] * point2[2]);
            norm3 = sqrtf(point3[0] * point3[0] + point3[1] * point3[1] + point3[2] * point3[2]);

            point1[0] /= norm1;
            point1[1] /= norm1;
            point1[2] /= norm1;
            point2[0] /= norm2;
            point2[1] /= norm2;
            point2[2] /= norm2;
            point3[0] /= norm3;
            point3[1] /= norm3;
            point3[2] /= norm3;

            obj->array[(iTriangle*4+0)*9+0] = pointA[0];
            obj->array[(iTriangle*4+0)*9+1] = pointA[1];
            obj->array[(iTriangle*4+0)*9+2] = pointA[2];
            obj->array[(iTriangle*4+0)*9+3] = point1[0];
            obj->array[(iTriangle*4+0)*9+4] = point1[1];
            obj->array[(iTriangle*4+0)*9+5] = point1[2];
            obj->array[(iTriangle*4+0)*9+6] = point3[0];
            obj->array[(iTriangle*4+0)*9+7] = point3[1];
            obj->array[(iTriangle*4+0)*9+8] = point3[2];

            obj->array[(iTriangle*4+1)*9+0] = point1[0];
            obj->array[(iTriangle*4+1)*9+1] = point1[1];
            obj->array[(iTriangle*4+1)*9+2] = point1[2];
            obj->array[(iTriangle*4+1)*9+3] = pointB[0];
            obj->array[(iTriangle*4+1)*9+4] = pointB[1];
            obj->array[(iTriangle*4+1)*9+5] = pointB[2];
            obj->array[(iTriangle*4+1)*9+6] = point2[0];
            obj->array[(iTriangle*4+1)*9+7] = point2[1];
            obj->array[(iTriangle*4+1)*9+8] = point2[2];

            obj->array[(iTriangle*4+2)*9+0] = point1[0];
            obj->array[(iTriangle*4+2)*9+1] = point1[1];
            obj->array[(iTriangle*4+2)*9+2] = point1[2];
            obj->array[(iTriangle*4+2)*9+3] = point2[0];
            obj->array[(iTriangle*4+2)*9+4] = point2[1];
            obj->array[(iTriangle*4+2)*9+5] = point2[2];
            obj->array[(iTriangle*4+2)*9+6] = point3[0];
            obj->array[(iTriangle*4+2)*9+7] = point3[1];
            obj->array[(iTriangle*4+2)*9+8] = point3[2];      

            obj->array[(iTriangle*4+3)*9+0] = point3[0];
            obj->array[(iTriangle*4+3)*9+1] = point3[1];
            obj->array[(iTriangle*4+3)*9+2] = point3[2];
            obj->array[(iTriangle*4+3)*9+3] = point2[0];
            obj->array[(iTriangle*4+3)*9+4] = point2[1];
            obj->array[(iTriangle*4+3)*9+5] = point2[2];
            obj->array[(iTriangle*4+3)*9+6] = pointC[0];
            obj->array[(iTriangle*4+3)*9+7] = pointC[1];
            obj->array[(iTriangle*4+3)*9+8] = pointC[2];                     

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

        //triangles_printf(obj);

        return obj;

    }

    points_obj * space_points_triangles(const triangles_obj * triangles) {

        unsigned int iTriangle;
        unsigned int iPointInTriangle;
        unsigned int iPoint;
        unsigned int nPoints;
    
        float diff, dist;        
        float point[3];

        points_obj * pointsContainer;
        points_obj * pointsUnique;

        unsigned char match;

        pointsContainer = points_construct_zero(triangles->nTriangles*3);

        nPoints = 0;

        for (iTriangle = 0; iTriangle < triangles->nTriangles; iTriangle++) {

            for (iPointInTriangle = 0; iPointInTriangle < 3; iPointInTriangle++) {

                match = 0;

                point[0] = triangles->array[iTriangle * 9 + iPointInTriangle * 3 + 0];
                point[1] = triangles->array[iTriangle * 9 + iPointInTriangle * 3 + 1];
                point[2] = triangles->array[iTriangle * 9 + iPointInTriangle * 3 + 2];

                for (iPoint = 0; iPoint < nPoints; iPoint++) {

                    dist = 0.0f;
                    
                    diff = point[0] - pointsContainer->array[iPoint * 3 + 0];
                    dist += diff * diff;
                    diff = point[1] - pointsContainer->array[iPoint * 3 + 1];
                    dist += diff * diff;
                    diff = point[2] - pointsContainer->array[iPoint * 3 + 2];
                    dist += diff * diff;

                    if (dist < 1E-10) {

                        match = 1;
                        break;

                    }

                }

                if (match == 0) {

                    pointsContainer->array[nPoints * 3 + 0] = point[0];
                    pointsContainer->array[nPoints * 3 + 1] = point[1];
                    pointsContainer->array[nPoints * 3 + 2] = point[2];
                    nPoints++;

                }

            }

        }

        pointsUnique = points_construct_zero(nPoints);
        memcpy(pointsUnique->array, pointsContainer->array, nPoints*3*sizeof(float));

        points_destroy(pointsContainer);

        return pointsUnique;

    }

    points_obj * space_sphere(const unsigned int level) {

        points_obj * obj;
        triangles_obj * triangles;

        triangles = space_triangles_level_level(level);
        obj = space_points_triangles(triangles);

        triangles_destroy(triangles);

        return obj;

    }

    points_obj * space_halfsphere(const unsigned int level) {

        points_obj * obj;

        triangles_obj * triangles;
        points_obj * pointsSphere;
        unsigned int nPoints;
        unsigned int iPoint;

        triangles = space_triangles_level_level(level);
        pointsSphere = space_points_triangles(triangles);

        nPoints = 0;

        for (iPoint = 0; iPoint < pointsSphere->nPoints; iPoint++) {
        
            if (pointsSphere->array[iPoint*3+2] >= 0.0f) {
            
                nPoints++;

            }

        }

        obj = points_construct_zero(nPoints);
        nPoints = 0;

        for (iPoint = 0; iPoint < pointsSphere->nPoints; iPoint++) {

            if (pointsSphere->array[iPoint*3+2] >= 0.0f) {
            
                obj->array[nPoints*3+0] = pointsSphere->array[iPoint*3+0];
                obj->array[nPoints*3+1] = pointsSphere->array[iPoint*3+1];
                obj->array[nPoints*3+2] = pointsSphere->array[iPoint*3+2];

                nPoints++;

            }

        }

        triangles_destroy(triangles);  
        points_destroy(pointsSphere);

        return obj;

    }

    points_obj * space_arc(const unsigned int level) {

        points_obj * obj;
        unsigned int nPoints;
        unsigned int iPoint;
        unsigned int iLevel;
        float theta;

        nPoints = 1;
        for (iLevel = 0; iLevel < level; iLevel++) {
            nPoints *= 2;
        }

        nPoints *= 3;
        nPoints++;

        obj = points_construct_zero(nPoints);

        for (iPoint = 0; iPoint < nPoints; iPoint++) {

            theta = (((float) iPoint) / ((float) nPoints - 1)) * M_PI;

            obj->array[iPoint * 3 + 0] = cosf(theta);
            obj->array[iPoint * 3 + 1] = sinf(theta);
            obj->array[iPoint * 3 + 2] = 0.0f;

        }

        return obj;

    }