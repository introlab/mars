
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    int main(int argc, char* argv[])
    {

        int client_id;
        struct sockaddr_in server_address;
        int connection_id;
        char * message;
        unsigned int iMessage;

        if (argc != 3) {

            printf("Expecting two arguments\n");
            exit(EXIT_FAILURE);
        }

        client_id = socket(AF_INET, SOCK_STREAM, 0);

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = inet_addr(argv[1]);
        server_address.sin_port = htons(atoi(argv[2]));

        printf("Connecting socket... ");  fflush(stdout);
        if (connect(client_id, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
            printf("Cannot connect to server\n");
            exit(EXIT_FAILURE);
        }
        else {
            printf("[OK]\n");    
        }
        
        iMessage = 0;
        message = (char *) malloc(sizeof(char) * 256);

        while(1) {

            iMessage++;
            sprintf(message, "Message %u.",iMessage);

            printf("Sent: %s\n",message);

            if (send(client_id, message, strlen(message), 0) < 0) {
                printf("Could not send message.\n");
                exit(EXIT_FAILURE);
            }

            sleep(1);

        }

    }