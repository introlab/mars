    
    #include "particle2particle.h"

    particle2particle_obj * particle2particle_construct(const unsigned int nParticles, const float deltaT, const float st_alpha, const float st_beta, const float st_ratio, const float ve_alpha, const float ve_beta, const float ve_ratio, const float ac_alpha, const float ac_beta, const float ac_ratio, const double epsilon, const float sigmaR, const float Nmin) {

        particle2particle_obj * obj;

        obj = (particle2particle_obj *) malloc(sizeof(particle2particle_obj));

        obj->nParticles = nParticles;
        obj->deltaT = deltaT;

        obj->stationary_alpha = st_alpha;
        obj->stationary_beta = st_beta;
        obj->stationary_ratio = st_ratio;
        obj->velocity_alpha = ve_alpha;
        obj->velocity_beta = ve_beta;
        obj->velocity_ratio = ve_ratio;
        obj->acceleration_alpha = ac_alpha;
        obj->acceleration_beta = ac_beta;
        obj->acceleration_ratio = ac_ratio;

        obj->states = (char *) malloc(sizeof(char) * 3);
        obj->states[0] = 'S';
        obj->states[1] = 'V';
        obj->states[2] = 'A';

        obj->stationary_a = expf(-1.0f * obj->stationary_alpha * deltaT);
        obj->stationary_b = obj->stationary_beta * sqrtf(1.0f - obj->stationary_a * obj->stationary_a);
        obj->velocity_a = expf(-1.0f * obj->velocity_alpha * deltaT);
        obj->velocity_b = obj->velocity_beta * sqrtf(1.0f - obj->velocity_a * obj->velocity_a);
        obj->acceleration_a = expf(-1.0f * obj->acceleration_alpha * deltaT);
        obj->acceleration_b = obj->acceleration_beta * sqrtf(1.0f - obj->acceleration_a * obj->acceleration_a);

        obj->pdf_ratio = (float *) malloc(sizeof(float) * 3);
        obj->pdf_ratio[0] = obj->stationary_ratio;
        obj->pdf_ratio[1] = obj->velocity_ratio;
        obj->pdf_ratio[2] = obj->acceleration_ratio;
        obj->rnd_ratio = random_construct_zero(3);
        random_pdf(obj->rnd_ratio, obj->pdf_ratio);
        obj->indexes_ratio = (unsigned int *) malloc(sizeof(unsigned int) * nParticles);

        obj->pdf_weight = (float *) malloc(sizeof(float) * nParticles);
        obj->indexes_weight = (unsigned int *) malloc(sizeof(unsigned int) * nParticles);
        obj->rnd_weight = random_construct_zero(nParticles);

        obj->realisation_normal_x = (float *) malloc(sizeof(float) * nParticles);
        obj->realisation_normal_y = (float *) malloc(sizeof(float) * nParticles);
        obj->realisation_normal_z = (float *) malloc(sizeof(float) * nParticles);
        obj->normaloff = normaloff_construct_rnd(epsilon, 10000);

        obj->epsilon = epsilon;
        obj->Nmin = Nmin;

        obj->sigmaR = sigmaR;
        obj->gaussian = gaussian_3d_construct_weightmusigma(1.0f, 0.0f, 0.0f, 0.0f, obj->sigmaR, obj->sigmaR, obj->sigmaR);

        obj->sum_P_p_x_O = (float *) malloc(sizeof(float) * nParticles);
        obj->p_x_O = (float *) malloc(sizeof(float) * nParticles);
        obj->particles = particles_construct_zero(nParticles);

        return obj;

    }

    void particle2particle_destroy(particle2particle_obj * obj) {

    }

    void particle2particle_init(particle2particle_obj * obj, const pot_obj * pot, particles_obj * particles) {

        unsigned int iParticle;

        random_generate(obj->rnd_ratio, obj->nParticles, obj->indexes_ratio);        

        for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

            coord_copy_coord(particles->array[iParticle]->x,pot->coord);
            coord_copy_zero(particles->array[iParticle]->v);
            particles->array[iParticle]->w = (1.0f / ((float) obj->nParticles));
            particles->array[iParticle]->state = obj->states[obj->indexes_ratio[iParticle]];

        }

    }

    void particle2particle_predict(particle2particle_obj * obj, particles_obj * particles) {

        unsigned int iParticle;
        float a, b;

        normaloff_generate(obj->normaloff, obj->nParticles, obj->realisation_normal_x);
        normaloff_generate(obj->normaloff, obj->nParticles, obj->realisation_normal_y);
        normaloff_generate(obj->normaloff, obj->nParticles, obj->realisation_normal_z);

        for (iParticle = 0; iParticle < particles->nSignals; iParticle++) {

            switch(particles->array[iParticle]->state) {

                case 'S':

                    a = obj->stationary_a;
                    b = obj->stationary_b;

                break;

                case 'V':

                    a = obj->velocity_a;
                    b = obj->velocity_b;

                break;

                case 'A':

                    a = obj->acceleration_a;
                    b = obj->acceleration_b;

                break;

                default:

                    a = 1.0f;
                    b = 0.0f;

                break;

            }

            particles->array[iParticle]->v->x = a * particles->array[iParticle]->v->x + b * obj->realisation_normal_x[iParticle];
            particles->array[iParticle]->v->y = a * particles->array[iParticle]->v->y + b * obj->realisation_normal_y[iParticle];
            particles->array[iParticle]->v->z = a * particles->array[iParticle]->v->z + b * obj->realisation_normal_z[iParticle];
            
            particles->array[iParticle]->x->x = particles->array[iParticle]->x->x + obj->deltaT * particles->array[iParticle]->v->x;
            particles->array[iParticle]->x->y = particles->array[iParticle]->x->y + obj->deltaT * particles->array[iParticle]->v->y;
            particles->array[iParticle]->x->z = particles->array[iParticle]->x->z + obj->deltaT * particles->array[iParticle]->v->z;
            
        }

    }

    void particle2particle_update(particle2particle_obj * obj, const postprob_obj * postprob, const pots_obj * pots, particles_obj * particles) {

        unsigned int iParticle;
        unsigned int iS;
        float x,y,z;
        float total;
        float Neff;

        // Compute sum{P_q,j * p(O_q|x_j,i)}, and normalize

        for (iParticle = 0; iParticle < particles->nSignals; iParticle++) {

            obj->sum_P_p_x_O[iParticle] = 0.0f;

        }

        for (iS = 0; iS < pots->nSignals; iS++) {

            obj->gaussian->mu_x = pots->array[iS]->coord->x;
            obj->gaussian->mu_y = pots->array[iS]->coord->y;
            obj->gaussian->mu_z = pots->array[iS]->coord->z;

            for (iParticle = 0; iParticle < particles->nSignals; iParticle++) {

                x = particles->array[iParticle]->x->x;
                y = particles->array[iParticle]->x->y;
                z = particles->array[iParticle]->x->z;

                obj->sum_P_p_x_O[iParticle] += postprob->probs[iS] * gaussian_3d_eval(obj->gaussian, x, y, z);      

            }

        }

        // Set total to a non-zero value, to avoid division by zero.
        // Set to 1/N^2, which is much smaller than weights
        total = 1.0f / ((float) (obj->nParticles*obj->nParticles));

        for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

            total += obj->sum_P_p_x_O[iParticle];           

        }

        for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

            obj->sum_P_p_x_O[iParticle] /= total;

        }

        // Compute p(x_j,i|O)

        for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

            obj->p_x_O[iParticle] = (1.0f - postprob->probTotal) * (1.0f/((float) obj->nParticles)) + postprob->probTotal * obj->sum_P_p_x_O[iParticle];

        }

        // Update weights

        total = 0.0f;

        for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

            particles->array[iParticle]->w = obj->p_x_O[iParticle] * particles->array[iParticle]->w;
            total += particles->array[iParticle]->w;

        }

        for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

            particles->array[iParticle]->w /= total;
            
        }

        // Resample if needed

        Neff = 0.0f;

        for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

            Neff += particles->array[iParticle]->w * particles->array[iParticle]->w;

        }

        Neff = 1.0f / Neff;

        if (Neff < (obj->Nmin * (float) obj->nParticles)) {
            
            particles_copy_particles(obj->particles, particles);

            for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {
                
                obj->pdf_weight[iParticle] = obj->particles->array[iParticle]->w;

            }

            random_pdf(obj->rnd_weight, obj->pdf_weight);
            random_generate(obj->rnd_weight, obj->nParticles, obj->indexes_weight);
            random_generate(obj->rnd_ratio, obj->nParticles, obj->indexes_ratio);

            for (iParticle = 0; iParticle < obj->nParticles; iParticle++) {

                particle_copy_particle(particles->array[iParticle], obj->particles->array[obj->indexes_weight[iParticle]]);
                
                particles->array[iParticle]->state = obj->states[obj->indexes_ratio[iParticle]];
                particles->array[iParticle]->w = 1.0f / ((float) obj->nParticles);

            }

        }

    }

    void particle2particle_estimate(const particle2particle_obj * obj, const particles_obj * particles, coord_obj * coord) {

        unsigned int iParticle;

        coord_copy_zero(coord);

        for (iParticle = 0; iParticle < particles->nSignals; iParticle++) {

            coord->x += particles->array[iParticle]->w * particles->array[iParticle]->x->x;
            coord->y += particles->array[iParticle]->w * particles->array[iParticle]->x->y;
            coord->z += particles->array[iParticle]->w * particles->array[iParticle]->x->z;

        }

    }