    
    #include "scan.h"

    scans_obj * scans_construct_null(const unsigned int nScans) {

        scans_obj * obj;

        obj = (scans_obj *) malloc(sizeof(scans_obj));

        obj->nScans = nScans;
        
        obj->points = (points_obj **) malloc(sizeof(points_obj *) * nScans);
        memset(obj->points, 0x00, sizeof(points_obj *) * nScans);

        obj->tdoas = (tdoas_obj **) malloc(sizeof(tdoas_obj *) * nScans);
        memset(obj->tdoas, 0x00, sizeof(tdoas_obj *) * nScans);

        obj->minmax = (tdoas_obj **) malloc(sizeof(tdoas_obj *) * nScans);
        memset(obj->minmax, 0x00, sizeof(tdoas_obj *) * nScans);

        obj->deltas = (deltas_obj **) malloc(sizeof(deltas_obj *) * nScans);
        memset(obj->deltas, 0x00, sizeof(deltas_obj *) * nScans);

        obj->indexes = (indexes_obj **) malloc(sizeof(indexes_obj *) * nScans);
        memset(obj->indexes, 0x00, sizeof(indexes_obj *) * nScans);

        obj->allminmax = (tdoas_obj *) NULL;

        return obj;

    }

    void scans_destroy(scans_obj * obj) {

        unsigned int iScan;

        for (iScan = 0; iScan < obj->nScans; iScan++) {

            if (obj->points[iScan] != NULL) {
                points_destroy(obj->points[iScan]);
            }

            if (obj->tdoas[iScan] != NULL) {
                tdoas_destroy(obj->tdoas[iScan]);
            }

            if (obj->minmax[iScan] != NULL) {
                tdoas_destroy(obj->minmax[iScan]);
            }

            if (obj->deltas[iScan] != NULL) {
                deltas_destroy(obj->deltas[iScan]);
            }

            if (obj->indexes[iScan] != NULL) {
                indexes_destroy(obj->indexes[iScan]);
            }

        }

        if (obj->allminmax != NULL) {
            tdoas_destroy(obj->allminmax);
        }

        free((void *) obj->points);
        free((void *) obj->tdoas);
        free((void *) obj->minmax);
        free((void *) obj->deltas);
        free((void *) obj->indexes);
        free((void *) obj);

    }
