
    #include "map.h"

    map_obj * map_construct_zero(const unsigned int nLinks) {

        map_obj * obj;
        unsigned int iLink;

        obj = (map_obj *) malloc(sizeof(map_obj));

        obj->nLinks = nLinks;
        obj->array = (unsigned char *) malloc(sizeof(unsigned char) * nLinks);

        for (iLink = 0; iLink < nLinks; iLink++) {
            obj->array[iLink] = 0;
        }

        return obj;

    }

    map_obj * map_construct_bool(const unsigned int nLinks, const unsigned char * bool) {

        map_obj * obj;
        unsigned int iLink;

        obj = (map_obj *) malloc(sizeof(map_obj));

        obj->nLinks = nLinks;
        obj->array = (unsigned char *) malloc(sizeof(unsigned char) * nLinks);

        for (iLink = 0; iLink < nLinks; iLink++) {
            obj->array[iLink] = bool[iLink];
        }

        return obj;

    }

    map_obj * map_construct_map(const map_obj * map) {

        map_obj * obj;
        unsigned int iLink;

        obj = (map_obj *) malloc(sizeof(map_obj));

        obj->nLinks = map->nLinks;
        obj->array = (unsigned char *) malloc(sizeof(unsigned char) * map->nLinks);

        for (iLink = 0; iLink < map->nLinks; iLink++) {
            obj->array[iLink] = map->array[iLink];
        }

        return obj;

    }

    void map_copy_zero(map_obj * obj) {

        unsigned int iLink;

        for (iLink = 0; iLink < obj->nLinks; iLink++) {
            obj->array[iLink] = 0;
        }

    }

    void map_copy_bool(map_obj * obj, const unsigned char * bool) {

        unsigned int iLink;

        for (iLink = 0; iLink < obj->nLinks; iLink++) {
            obj->array[iLink] = bool[iLink];
        }

    }  

    void map_copy_map(map_obj * obj, const map_obj * map) {

        unsigned int iLink;

        for (iLink = 0; iLink < obj->nLinks; iLink++) {
            obj->array[iLink] = map->array[iLink];
        }

    }

    void map_destroy(map_obj * obj) {

        free((void *) obj->array);
        free((void *) obj);

    }

    void map_printf(map_obj * obj) {

        unsigned int iLink;

        for (iLink = 0; iLink < obj->nLinks; iLink++) {
            printf("%01u",obj->array[iLink]);
        }
        printf("\n");

    }

    maps_obj * maps_construct_null(const unsigned int nSignals) {

        maps_obj * obj;
        unsigned int iSignal;

        obj = (maps_obj *) malloc(sizeof(maps_obj));

        obj->nSignals = nSignals;
        obj->array = (map_obj **) malloc(sizeof(map_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = NULL;
        }

        return obj;

    }

    void maps_destroy(maps_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            if (obj->array[iSignal] != NULL) {
                map_destroy(obj->array[iSignal]);
            }
        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void maps_printf(maps_obj * obj) {

        unsigned int iSignal;
        unsigned int iLink;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%04u): ", iSignal);

            if (obj->array[iSignal] != NULL) {

                for (iLink = 0; iLink < obj->array[iSignal]->nLinks; iLink++) {

                    printf("%01u",obj->array[iSignal]->array[iLink]);

                }

            }
            else {

                printf("(null)");

            }


            printf("\n");

        }

    }