    
    #include "scan.h"

    scan_obj * scan_construct_null(void) {

        scan_obj * obj;

        obj = (scan_obj *) malloc(sizeof(scan_obj));

        obj->points = NULL;
        obj->tdoas = NULL;
        obj->indexes = NULL;

        return obj;

    }

    void scan_destroy(scan_obj * obj) {

        if (obj->points != NULL) {
            points_destroy(obj->points);	
        }
        
        if (obj->tdoas != NULL) {
            tdoas_destroy(obj->tdoas);	
        }
        
        if (obj->indexes != NULL) {
            indexes_destroy(obj->indexes);	
        }
        
        free((void *) obj);

    }

    void scan_printf(scan_obj * obj) {

        if (obj->points != NULL) {
            points_printf(obj->points);
        }
        
        if (obj->tdoas != NULL) {
            tdoas_printf(obj->tdoas);
        }

        if (obj->indexes != NULL) {
            indexes_printf(obj->indexes);
        }

    }

    scans_obj * scans_construct_null(const unsigned int nSignals) {

        scans_obj * obj;
        unsigned int iSignal;

        obj = (scans_obj *) malloc(sizeof(scans_obj)); 

        obj->nSignals = nSignals;
        obj->array = (scan_obj **) malloc(sizeof(scan_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = scan_construct_null();
        }

        return obj;

    }

    void scans_destroy(scans_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
        	if (obj->array[iSignal] != NULL) {
        	    scan_destroy(obj->array[iSignal]);	
        	}
        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void scans_printf(scans_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
        	if (obj->array[iSignal] != NULL) {
        	    scan_printf(obj->array[iSignal]);	
        	}
        }

    }