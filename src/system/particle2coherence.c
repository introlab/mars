    
    #include "particle2coherence.h"

    particle2coherence_obj * particle2coherence_construct(const float sigmaR) {

        particle2coherence_obj * obj;

        obj = (particle2coherence_obj *) malloc(sizeof(particle2coherence_obj));

        obj->sigmaR = sigmaR;
        obj->gaussian = gaussian_3d_construct_weightmusigma(1.0f, 0.0f, 0.0f, 0.0f, obj->sigmaR, obj->sigmaR, obj->sigmaR);

        return obj;

    }

    void particle2coherence_destroy(particle2coherence_obj * obj) {

    }

    void particle2coherence_process(particle2coherence_obj * obj, const particles_obj * particles, const pots_obj * pots, coherence_obj * coherence) {

        unsigned int iS;
        unsigned int iParticle;
        float value;
        float total;
        float w;
        float x,y,z;

        for (iS = 0; iS < pots->nSignals; iS++) {

            obj->gaussian->mu_x = pots->array[iS]->coord->x;
            obj->gaussian->mu_y = pots->array[iS]->coord->y;
            obj->gaussian->mu_z = pots->array[iS]->coord->z;

            total = 0.0f;

            for (iParticle = 0; iParticle < particles->nSignals; iParticle++) {
                 
                x = particles->array[iParticle]->x->x;
                y = particles->array[iParticle]->x->y;
                z = particles->array[iParticle]->x->z;
                w = particles->array[iParticle]->w;

                total += w * gaussian_3d_eval(obj->gaussian, x, y, z);

            }

            coherence->probs[iS] = total;

        }

    }