    
    #include "particle.h"

    particle_obj * particle_construct_zero(void) {

        particle_obj * obj;

        obj = (particle_obj *) malloc(sizeof(particle_obj));

        obj->w = 0.0f;
        obj->x = coord_construct_zero();
        obj->v = coord_construct_zero();
        obj->state = 'U';

        return obj;

    }

    void particle_destroy(particle_obj * obj) {

        coord_destroy(obj->x);
        coord_destroy(obj->v);
        free((void *) obj);

    }

    void particle_copy_particle(particle_obj * obj, particle_obj * particle) {

        obj->w = particle->w;
        coord_copy_coord(obj->x, particle->x);
        coord_copy_coord(obj->v, particle->v);
        obj->state = particle->state;

    }

    void particle_printf(const particle_obj * obj) {

        printf("w: %+1.6f s: %c xx: %+1.3f xy: %+1.3f xz: %+1.3f xx: %+1.3f xy: %+1.3f xz: %+1.3f\n",
               obj->w, obj->state, obj->x->x, obj->x->y, obj->x->z, obj->v->x, obj->v->y, obj->v->z);

    }

    particles_obj * particles_construct_zero(const unsigned int nSignals) {

        particles_obj * obj;
        unsigned int iSignal;

        obj = (particles_obj *) malloc(sizeof(particles_obj));

        obj->nSignals = nSignals;
        obj->array = (particle_obj **) malloc(sizeof(particle_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {

            obj->array[iSignal] = particle_construct_zero();

        }

        return obj;

    }

    void particles_destroy(particles_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            particle_destroy(obj->array[iSignal]);

        }

        free((void *) obj->array);
        free((void *) obj);

    }

    void particles_copy_particles(particles_obj * obj, particles_obj * particles) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < particles->nSignals; iSignal++) {

            particle_copy_particle(obj->array[iSignal], particles->array[iSignal]);

        }

    }

    void particles_printf(const particles_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            printf("(%04u): w: %+1.6f s: %c xx: %+1.3f xy: %+1.3f xz: %+1.3f xx: %+1.3f xy: %+1.3f xz: %+1.3f\n",
                    iSignal, 
                    obj->array[iSignal]->w, 
                    obj->array[iSignal]->state, 
                    obj->array[iSignal]->x->x, 
                    obj->array[iSignal]->x->y, 
                    obj->array[iSignal]->x->z, 
                    obj->array[iSignal]->v->x, 
                    obj->array[iSignal]->v->y, 
                    obj->array[iSignal]->v->z);

        }

    }