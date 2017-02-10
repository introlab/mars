    
    #include "scan.h"

    scans_obj * scans_construct_null(const unsigned int nScans) {

        scans_obj * obj;

        obj = (scans_obj *) malloc(sizeof(scans_obj));

        obj->nScans = nScans;
        
        obj->points = (points_obj **) malloc(sizeof(points_obj *) * nScans);
        memset(obj->points, 0x00, sizeof(points_obj *) * nScans);

        obj->tdoas = (tdoas_obj **) malloc(sizeof(tdoas_obj *) * nScans);
        memset(obj->tdoas, 0x00, sizeof(tdoas_obj *) * nScans);

        obj->indexes = (indexes_obj **) malloc(sizeof(indexes_obj *) * nScans);
        memset(obj->indexes, 0x00, sizeof(indexes_obj *) * nScans);

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
            if (obj->indexes[iScan] != NULL) {
                indexes_destroy(obj->indexes[iScan]);
            }

        }

        free((void *) obj->points);
        free((void *) obj->tdoas);
        free((void *) obj->indexes);
        free((void *) obj);

    }
