    
    #include "fifo.h"

    fifo_obj * fifo_construct( const unsigned int nMaxElements ) {

        fifo_obj * obj;
        unsigned int iElement;

        obj = (fifo_obj *) malloc(sizeof(fifo_obj));

        pthread_mutex_init( &(obj->mutex), NULL );

        obj->buffer = (void **) malloc(sizeof(void *) * nMaxElements);

        for (iElement = 0; iElement < nMaxElements; iElement++) {

            obj->buffer[iElement] = (void *) NULL;

        }

        obj->nMaxElements = nMaxElements;
        obj->nElements = 0;
        obj->iRead = 0;
        obj->iWrite = 0;

        return obj;

    }

    void fifo_destroy( fifo_obj * obj ) {

        free((void *) obj->buffer);
        free((void *) obj);

    }

    int fifo_push( fifo_obj * obj, const void * element ) {

        int rtnValue;

        pthread_mutex_lock( &(obj->mutex) );

        if (obj->nElements < obj->nMaxElements) {

            obj->buffer[obj->iWrite] = (void *) element;
            obj->iWrite++;

            if (obj->iWrite == obj->nMaxElements) {
            	obj->iWrite = 0;
            }

            obj->nElements++;

            rtnValue = 0;

        }
        else {

        	rtnValue = -1;

        }

        pthread_mutex_unlock( &(obj->mutex) );

        return rtnValue;

    }

    void * fifo_pop( fifo_obj * obj ) {

        void * element;

        pthread_mutex_lock( &(obj->mutex) );

        if (obj->nElements > 0) {

            element = obj->buffer[obj->iRead];
            obj->buffer[obj->iRead] = (void *) NULL;
            obj->iRead++;

            if (obj->iRead == obj->nMaxElements) {
            	obj->iRead = 0;
            }

            obj->nElements--;

        }
        else {

            element = (void *) NULL;

        }

        pthread_mutex_unlock( &(obj->mutex) );        

        return element;

    }