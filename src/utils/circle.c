
    #include "circle.h"

    matrix_float * circle_generate(const unsigned int nPoints, const float radius) {

        matrix_float * points;
        unsigned int iPoint;

        points = matrix_float_malloc(nPoints, 3);

        for (iPoint = 0; iPoint < nPoints; iPoint++) {

            points->array[iPoint][0] = radius * cosf(2.0f * M_PI * ((float) iPoint) / ((float) nPoints));
            points->array[iPoint][1] = radius * sinf(2.0f * M_PI * ((float) iPoint) / ((float) nPoints));
            points->array[iPoint][2] = 0.0f;

        }

        return points;

    }