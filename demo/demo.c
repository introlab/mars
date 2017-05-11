
    #include <mars/mars.h>
    #include <signal.h>
    #include <time.h>
    #include <unistd.h>

    #include "../src/general/profiler.h"

    static unsigned char quit;

    void sighandler(int signum) {
        quit = 0x01;
    }

    int main(int argc, char* argv[])
    {
 
        arguments * args;
        parameters * params;
        configs * cfgs;
        objects * objs;

        struct timespec start, end;
        unsigned long hopTimeNano;
        unsigned int nHops;

        profiler_obj * profiler;
        float timeProcessing, timeSignal;

        // Generate objects
        args = arguments_construct_null();
        params = parameters_construct_null();
        cfgs = configs_construct_null();
        objs = objects_construct_null();
        
        printf("\n");

        // Load arguments from the call into the arguments structure
        printf("Loading arguments........ "); fflush(stdout);
        args2arguments(args, argc, argv);
        printf("[OK]\n");

        // Open the configuration file and load parameters
        printf("Loading parameters....... "); fflush(stdout);
        file2parameters(params, args->config_file);
        printf("[OK]\n");

        // Convert these parameters to individual configurations for each object
        printf("Loading configurations... "); fflush(stdout);
        parameters2configs(cfgs, params);
        printf("[OK]\n");

        // Initialize objects
        printf("Initialize objects....... "); fflush(stdout);
        configs2objects(objs, cfgs, args);
        printf("[OK]\n");

        // Initialize profiler
        printf("Initialize profiler...... "); fflush(stdout);
        profiler = profiler_construct_zero(params->general->fS);
        printf("[OK]\n");

        // Process
       
        signal(SIGINT, sighandler);
        quit = 0x00;
        nHops = 0;

        if (args->realtime == 0x01) {
            hopTimeNano = (unsigned long) ((1E9) * ((float) params->general->hopSize) / ((float) params->general->fS));
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        }

        printf("Processing............... "); fflush(stdout);
        while((objects2objects_process(objs, profiler) == 0) && (quit==0x00)) {

            nHops++;

            if (args->verbose == 0x01) {

                if (objs->msg_tracks != NULL) {

                    printf("\n");
                    tracks_printf(objs->msg_tracks->tracks);

                }
                
            }

            if (args->realtime == 0x01) {

                clock_gettime(CLOCK_MONOTONIC_RAW, &end);

                do {
                    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                    usleep(100);
                } while ((end.tv_nsec - start.tv_nsec) < hopTimeNano);

                clock_gettime(CLOCK_MONOTONIC_RAW, &start);

            }

        }

        if (quit == 0x00) {
            printf("[OK]\n");    
        }
        else {
            printf("[Stopped]\n");
        }

        // Free objects
        printf("Free memory.............. "); fflush(stdout);
        arguments_destroy(args);
        parameters_destroy(params);
        configs_destroy(cfgs);
        objects_destroy(objs);
        printf("[OK]\n");

        timeSignal = profiler->duration;
        timeProcessing = profiler->resampling + profiler->stft + profiler->ssl + profiler->sst;

        // Print performances
        printf("\n");
        printf("==========================================\n");
        printf("Summary\n");
        printf("==========================================\n");
        printf("Total signal duration....... %1.5f secs\n",timeSignal);
        printf("Total processing duration... %1.5f secs\n",timeProcessing);
        printf(" + Resampling............... %1.5f secs\n",profiler->resampling);
        printf(" + STFT..................... %1.5f secs\n",profiler->stft);
        printf(" + GCC...................... %1.5f secs\n",profiler->gcc);
        printf(" + SSL...................... %1.5f secs\n",profiler->ssl);
        printf(" + SST...................... %1.5f secs\n",profiler->sst);
        printf("Average CPU usage........... %3.2f%%\n",100.0f*timeProcessing/timeSignal);
        printf("==========================================\n");

        profiler_destroy(profiler);

        return 0;

    }
