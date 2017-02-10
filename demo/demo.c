
    #include <mars/mars.h>

    #include <ncurses.h>

    int main(int argc, char* argv[])
    {
 
        arguments * args;
        parameters * params;
        configs * cfgs;
        objects * objs;

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

        // Process
        printf("Processing............... "); fflush(stdout);
        while(objects2objects_process(objs, &timeProcessing, &timeSignal, params->general->fS) == 0) {

            if (args->verbose == 0x01) {

                if (objs->msg_tracks != NULL) {

                    tracks_printf(objs->msg_tracks->tracks);

                }
                
            }

        }
        printf("[OK]\n");

        // Free objects
        printf("Free memory.............. "); fflush(stdout);
        arguments_destroy(args);
        parameters_destroy(params);
        configs_destroy(cfgs);
        objects_destroy(objs);
        printf("[OK]\n");

        // Print performances
        printf("\n");
        printf("----------------------------------------\n");
        printf("Summary\n");
        printf("----------------------------------------\n");
        printf("Total signal duration: %1.3f secs\n",timeSignal);
        printf("Total processing duration: %1.3f secs\n",timeProcessing);
        printf("Average CPU usage: %3.2f%%\n",100.0f*timeProcessing/timeSignal);
        printf("----------------------------------------\n");

        return 0;

    }