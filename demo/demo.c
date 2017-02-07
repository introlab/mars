
    #include <mars/mars.h>

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
        
        // Load arguments from the call into the arguments structure
        args2arguments(args, argc, argv);

        // Open the configuration file and load parameters
        file2parameters(params, args->config_file);

        // Convert these parameters to individual configurations for each object
        parameters2configs(cfgs, params);

        // Initialize objects
        configs2objects(objs, cfgs, args);

        // Process
        while(objects2objects_process(objs, &timeProcessing, &timeSignal, params->general->fS) == 0) {

            if (args->verbose == 0x01) {

                if (objs->msg_tracks != NULL) {

                    tracks_printf(objs->msg_tracks->tracks);

                }
                
            }

        }

        // Free objects
        arguments_destroy(args);
        parameters_destroy(params);
        configs_destroy(cfgs);
        objects_destroy(objs);

        // Print performances
        printf("Total signal duration: %1.3f secs\n",timeSignal);
        printf("Total processing duration: %1.3f secs\n",timeProcessing);
        printf("Average CPU usage: %3.2f%%\n",100.0f*timeProcessing/timeSignal);

        return 0;

    }