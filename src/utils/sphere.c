
	#include "sphere.h"

	matrix_float * sphere_generate(const unsigned int nLevels, const float radius) {

		matrix_float * triangles;
		matrix_float * trianglesRefined;
		unsigned int nTriangles;

		matrix_float * points;

		unsigned int iLevel;
		unsigned int iPoint;
		unsigned char iDim;

		triangles = sphere_triangles_level0();
		nTriangles = 20;

		for (iLevel = 0; iLevel < nLevels; iLevel++) {

			trianglesRefined = sphere_triangles_refine((const matrix_float *) triangles);

			nTriangles *= 4;

			matrix_float_free(triangles);			
			triangles = trianglesRefined;

		}

		points = sphere_triangles2points((const matrix_float *) triangles);

		for (iPoint = 0; iPoint < points->nRows; iPoint++) {

			for (iDim = 0; iDim < 3; iDim++) {

				points->array[iPoint][iDim] = points->array[iPoint][iDim] * radius;

			}

		}

		matrix_float_free(triangles);

		return points; 

	}

	matrix_float * sphere_triangles_level0(void) {

		float h;
		float r;

		unsigned int iPoint;
		unsigned int nPoints;
		matrix_float * points;
		
		unsigned int iTriangle;
		unsigned int nTriangles;
		matrix_float * triangles;
		
		unsigned int iDim;

		/* points */

		nPoints = 12;
		points = matrix_float_malloc(nPoints,3);

		h = sqrtf(5.0f)/5.0f;
		r = (2.0f/5.0f)*sqrtf(5.0f);

		points->array[0][0] = 0.0f;
		points->array[0][1] = 0.0f;
		points->array[0][2] = 1.0f;

		points->array[11][0] = 0.0f;
		points->array[11][1] = 0.0f;
		points->array[11][2] = -1.0f;		

		for (iPoint = 0; iPoint < 5; iPoint++) {

			points->array[iPoint+1][0] = r * sinf(2*M_PI*((float) iPoint)/5.0f);
			points->array[iPoint+1][1] = r * cosf(2*M_PI*((float) iPoint)/5.0f);
			points->array[iPoint+1][2] = h;

			points->array[iPoint+6][0] = -1.0f * r * sinf(2*M_PI*((float) iPoint)/5.0f);
			points->array[iPoint+6][1] = -1.0f * r * cosf(2*M_PI*((float) iPoint)/5.0f);
			points->array[iPoint+6][2] = -1.0f * h;

		}

		/* triangles */

		nTriangles = 20;
		triangles = matrix_float_malloc(nTriangles, 9);

		for (iDim = 0; iDim < 3; iDim++) {

			triangles->array[0][0*3+iDim] = points->array[0][iDim];
			triangles->array[0][1*3+iDim] = points->array[2][iDim];
			triangles->array[0][2*3+iDim] = points->array[1][iDim];

			triangles->array[1][0*3+iDim] = points->array[0][iDim];
			triangles->array[1][1*3+iDim] = points->array[3][iDim];
			triangles->array[1][2*3+iDim] = points->array[2][iDim];

			triangles->array[2][0*3+iDim] = points->array[0][iDim];
			triangles->array[2][1*3+iDim] = points->array[4][iDim];
			triangles->array[2][2*3+iDim] = points->array[3][iDim];

			triangles->array[3][0*3+iDim] = points->array[0][iDim];
			triangles->array[3][1*3+iDim] = points->array[5][iDim];
			triangles->array[3][2*3+iDim] = points->array[4][iDim];

			triangles->array[4][0*3+iDim] = points->array[0][iDim];
			triangles->array[4][1*3+iDim] = points->array[1][iDim];
			triangles->array[4][2*3+iDim] = points->array[5][iDim];

			triangles->array[5][0*3+iDim] = points->array[9][iDim];
			triangles->array[5][1*3+iDim] = points->array[1][iDim];
			triangles->array[5][2*3+iDim] = points->array[2][iDim];

			triangles->array[6][0*3+iDim] = points->array[10][iDim];
			triangles->array[6][1*3+iDim] = points->array[2][iDim];
			triangles->array[6][2*3+iDim] = points->array[3][iDim];

			triangles->array[7][0*3+iDim] = points->array[6][iDim];
			triangles->array[7][1*3+iDim] = points->array[3][iDim];
			triangles->array[7][2*3+iDim] = points->array[4][iDim];

			triangles->array[8][0*3+iDim] = points->array[7][iDim];
			triangles->array[8][1*3+iDim] = points->array[4][iDim];
			triangles->array[8][2*3+iDim] = points->array[5][iDim];

			triangles->array[9][0*3+iDim] = points->array[8][iDim];
			triangles->array[9][1*3+iDim] = points->array[5][iDim];
			triangles->array[9][2*3+iDim] = points->array[1][iDim];

			triangles->array[10][0*3+iDim] = points->array[4][iDim];
			triangles->array[10][1*3+iDim] = points->array[7][iDim];
			triangles->array[10][2*3+iDim] = points->array[6][iDim];

			triangles->array[11][0*3+iDim] = points->array[5][iDim];
			triangles->array[11][1*3+iDim] = points->array[8][iDim];
			triangles->array[11][2*3+iDim] = points->array[7][iDim];

			triangles->array[12][0*3+iDim] = points->array[1][iDim];
			triangles->array[12][1*3+iDim] = points->array[9][iDim];
			triangles->array[12][2*3+iDim] = points->array[8][iDim];

			triangles->array[13][0*3+iDim] = points->array[2][iDim];
			triangles->array[13][1*3+iDim] = points->array[10][iDim];
			triangles->array[13][2*3+iDim] = points->array[9][iDim];

			triangles->array[14][0*3+iDim] = points->array[3][iDim];
			triangles->array[14][1*3+iDim] = points->array[6][iDim];
			triangles->array[14][2*3+iDim] = points->array[10][iDim];

			triangles->array[15][0*3+iDim] = points->array[11][iDim];
			triangles->array[15][1*3+iDim] = points->array[6][iDim];
			triangles->array[15][2*3+iDim] = points->array[7][iDim];

			triangles->array[16][0*3+iDim] = points->array[11][iDim];
			triangles->array[16][1*3+iDim] = points->array[7][iDim];
			triangles->array[16][2*3+iDim] = points->array[8][iDim];

			triangles->array[17][0*3+iDim] = points->array[11][iDim];
			triangles->array[17][1*3+iDim] = points->array[8][iDim];
			triangles->array[17][2*3+iDim] = points->array[9][iDim];

			triangles->array[18][0*3+iDim] = points->array[11][iDim];
			triangles->array[18][1*3+iDim] = points->array[9][iDim];
			triangles->array[18][2*3+iDim] = points->array[10][iDim];

			triangles->array[19][0*3+iDim] = points->array[11][iDim];
			triangles->array[19][1*3+iDim] = points->array[10][iDim];
			triangles->array[19][2*3+iDim] = points->array[6][iDim];

		}

		/* free points */

		matrix_float_free(points);

		/* return */

		return triangles;

	}

	matrix_float * sphere_triangles_refine(const matrix_float * triangles) {

		matrix_float * trianglesRefined;		
		unsigned int iTriangle;
		unsigned int iPoint;
		
		float point1[3], point2[3], point3[3];
		float pointA[3], pointB[3], pointC[3];
		float normA, normB, normC;
		unsigned int iDim;

		/* triangles alloc */

		trianglesRefined = matrix_float_malloc(triangles->nRows*4,triangles->nCols);

		/* split each triangle into four triangles: 
		*
		*        1               1
		*       / \             / \
		*      /   \     =>    A---B
		*     /     \         / \ / \
		*    2-------3       2---C---3 
		*
		*/

		for (iTriangle = 0; iTriangle < triangles->nRows; iTriangle++) {

			normA = 0.0f;
			normB = 0.0f;
			normC = 0.0f;

			for (iDim = 0; iDim < 3; iDim++) {

				point1[iDim] = triangles->array[iTriangle][0*3+iDim];
				point2[iDim] = triangles->array[iTriangle][1*3+iDim];
				point3[iDim] = triangles->array[iTriangle][2*3+iDim];

				pointA[iDim] = point1[iDim] + point2[iDim];
				pointB[iDim] = point1[iDim] + point3[iDim];
				pointC[iDim] = point2[iDim] + point3[iDim];

				normA += pointA[iDim] * pointA[iDim];
				normB += pointB[iDim] * pointB[iDim];
				normC += pointC[iDim] * pointC[iDim];

			}

			normA = sqrtf(normA);
			normB = sqrtf(normB);
			normC = sqrtf(normC);

			for (iDim = 0; iDim < 3; iDim++) {

				pointA[iDim] /= normA;
				pointB[iDim] /= normB;
				pointC[iDim] /= normC;

			}

			for (iDim = 0; iDim < 3; iDim++) {

				trianglesRefined->array[iTriangle*4+0][0*3+iDim] = point1[iDim];
				trianglesRefined->array[iTriangle*4+0][1*3+iDim] = pointA[iDim];
				trianglesRefined->array[iTriangle*4+0][2*3+iDim] = pointB[iDim];

				trianglesRefined->array[iTriangle*4+1][0*3+iDim] = pointA[iDim];
				trianglesRefined->array[iTriangle*4+1][1*3+iDim] = point2[iDim];
				trianglesRefined->array[iTriangle*4+1][2*3+iDim] = pointC[iDim];

				trianglesRefined->array[iTriangle*4+2][0*3+iDim] = pointA[iDim];
				trianglesRefined->array[iTriangle*4+2][1*3+iDim] = pointB[iDim];
				trianglesRefined->array[iTriangle*4+2][2*3+iDim] = pointC[iDim];

				trianglesRefined->array[iTriangle*4+3][0*3+iDim] = pointB[iDim];
				trianglesRefined->array[iTriangle*4+3][1*3+iDim] = pointC[iDim];
				trianglesRefined->array[iTriangle*4+3][2*3+iDim] = point3[iDim];

			}

		}

		return trianglesRefined;

	}

	matrix_float * sphere_triangles2points(const matrix_float * triangles) {

		float diff;

		float edge;
		float edgeHalf;	

		float dist;
		float minDist;

		unsigned int iDim;

		matrix_float * points;
		unsigned int iPoint;
		unsigned int nPoints;

		unsigned int iTriangle;
		unsigned int iPointInTriangle;

		edge = 0.0f;

		for (iDim = 0; iDim < 3; iDim++) {

			diff = triangles->array[0][0*3+iDim] - triangles->array[0][1*3+iDim];
			edge += diff * diff;

		}

		edge = sqrtf(edge);
		edgeHalf = edge / 2.0f;

		nPoints = triangles->nRows/2 + 2;
		points = matrix_float_malloc(nPoints, 3);

		nPoints = 0;

		for (iTriangle = 0; iTriangle < triangles->nRows; iTriangle++) {

			for (iPointInTriangle = 0; iPointInTriangle < 3; iPointInTriangle++) {

				minDist = INFINITY;

				for (iPoint = 0; iPoint < nPoints; iPoint++) {

					dist = 0.0f;

					for (iDim = 0; iDim < 3; iDim++) {

						diff = triangles->array[iTriangle][iPointInTriangle*3+iDim] - points->array[iPoint][iDim];

						dist += diff * diff;

					}

					dist = sqrtf(dist);

					if (dist < minDist) {
						minDist = dist;
					}

				}

				if (minDist > edgeHalf) {

					for (iDim = 0; iDim < 3; iDim++) {

						points->array[nPoints][iDim] = triangles->array[iTriangle][iPointInTriangle*3+iDim];

					}

					nPoints++;

				}

			}

		}

		return points;

	}
