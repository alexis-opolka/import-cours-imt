#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef enum IPVersion {
    IPv4 = 4,
    IPv6 = 6
} IPVersion;
typedef enum Protocol {
    UDP = 1,
    TCP = 2
} Protocol;
typedef struct sockaddr_in sockaddr_in;

typedef struct Configuration {
    // The address to listen on
    sockaddr_in address_in;
    // The listening port
    int port_in;
    // The IP Version to use
    IPVersion ip_version;
    // The preferred protocol for communication
    Protocol preferred_protocol;
    // Maximum of allowed waiting connections
    int max_allowed_waiting_connections;
} Configuration;

char* read_request_line(char request_buffer) {
    char* lines = strtok(request_buffer, '\n');

    return lines[0];
}

void run_server(Configuration config){
    int socket_nbr;

    if (config.ip_version == IPv4) {
        if (config.preferred_protocol == TCP) {
            socket_nbr = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        } else if (config.preferred_protocol == UDP) {
            socket_nbr = socket(AF_INET, SOCK_STREAM, IPPROTO_UDP);
        } else {
            printf("Unhandled preferred protocol given to run_server!\n");
            exit(0);
        }
    } else if (config.ip_version == IPv4) {
        if (config.preferred_protocol == TCP) {
            socket_nbr = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
        } else if (config.preferred_protocol == UDP) {
            socket_nbr = socket(AF_INET6, SOCK_STREAM, IPPROTO_UDP);
        } else {
            printf("Unhandled preferred protocol given to run_server!\n");
            exit(0);
        }
    }

    config.address_in.sin_family = AF_INET;
    config.address_in.sin_addr.s_addr = INADDR_ANY;
    config.address_in.sin_port = htons(config.port_in);
    int addrlen = sizeof(config.address_in);

    int one = 1;

    setsockopt(socket_nbr, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    // On configure la socket en lui passant la structure qui contient l'addresse et le port sur lesquelle écouter.
    bind(socket_nbr, (struct sockaddr *)&config.address_in, sizeof(config.address_in));

    listen(socket_nbr, 3);

    printf("Opened socket on any IPv4 address on the %d port.\n", config.port_in);
    printf("Listening on http://127.0.0.1:%d\n", config.port_in);

    int socket_result;
    while (socket_result != -1) {
        size_t buffer_size = 1024;
        char request_buffer[buffer_size];

        socket_result = accept(socket_nbr, (struct sockaddr *)&config.address_in, (socklen_t *)&addrlen);

        printf("Connection réussie avec un client sur la socket %d\n", socket_result);

        ssize_t read_buffer = read(socket_result, &request_buffer, buffer_size);
        if (read_buffer >= 0) {
            printf("Buffer size: %d\n", read_buffer);

            request_buffer[read_buffer] = '\0';
        }

        printf("The first %d bits of the request:\n\n---------\n\n%s\n\n---------\n\n", buffer_size, request_buffer);

        // We're concatenating the request received with our own information
        char* request_line = read_request_line(request_buffer);
        strcat(request_buffer, request_line);

        send(socket_result, request_buffer, read_buffer+sizeof(request_line), 0);
        close(socket_result);
    }

    close(socket_nbr);
}

int main(int argc, char const *argv[])
{
    char mode;
    Configuration config;

    printf("Please choose an operation mode:"
        "\n\t- a for the built-in operation mode"
        "\n\t- m to use a manual operation mode"
        "\n\t- b to use the built-in configured"
        "\n\t- q to quit the shell\n"
    );

    scanf(" %c", &mode);

    switch (mode)
    {
        case 'm':

            printf("Please specify the IP version you wish to use (4/6):");
            scanf(" %d", &config.ip_version);

            printf("Please specify the port: (4 digits allowed)");
            scanf(" %d", &config.port_in);

            printf("Please specify the protocol to use:"
                "\n\t- [1] for TCP"
                "\n\t- [2] for UDP\n"
            );
            scanf(" %d", &config.preferred_protocol);

            run_server(config);

            break;

        case 'b':
            config.ip_version = IPv4;
            config.port_in = 7070;
            config.preferred_protocol = TCP;

            run_server(config);

            break;

        case 'a':
            // On crée la socket, la fonction nous renvoie le numéro du descripteur de fichier correspondant a la socket
            // AF_INET indique qu'on utilise de l'ipv4
            // SOCK_STREAM indique qu'on souhaite un protocole connecté dans lequel les paquets arrivent dans l'ordre
            // Le dernier argument sert à préciser le protocole, on met zéro pour qu'il soit choisi automatiquement
            int numero_socket = socket(AF_INET, SOCK_STREAM, 0);

            struct sockaddr_in address;			  // cette structure sert a configurer les parametres d'écoute de la socket.
            address.sin_family = AF_INET;		  // on indique le protocole ip (ici ipv4)
            address.sin_addr.s_addr = INADDR_ANY; // On écoute sur toutes les addresses entrantes
            address.sin_port = htons(7070);		  // On écoute sur le port 7070
            int addrlen = sizeof(address);

            int un = 1; // on crée une variable contenant 1 car on aura besoin d'un pointeur vers la valeur un a la ligne suivante
            // setsockopt sert à changer les options d'une socket
            // Les options SO_REUSEADDR et SO_REUSEPORT sont utiles dans le cas ou un programme précédent a attaché une socket sur le
            // même couple port/addresss et qu'elle n'a pas été supprimée
            // En précisant REUSE_PORT et REUSE_ADDR nous précisons que nous souhaitons utiliser ce couple "de force"
            setsockopt(numero_socket, SOL_SOCKET, SO_REUSEADDR, &un, sizeof(un));

            // On configure la socket en lui passant la structure qui contient l'addresse et le port sur lesquelle écouter.
            bind(numero_socket, (struct sockaddr *)&address, sizeof(address));

            // On écoute sur la socket précédement créée, le numero 3 indique qu'on autorise une queue de maximum 3 requêtes en attente de traitement
            // Ecouter signifie simplement que le noyau va enregistrer les paquets qui arrivent sur cette socket.
            listen(numero_socket, 3);

            printf("Opened socket on any IPv4 address on the 7070 port.\n");
            printf("Listening on http://127.0.0.1:7070\n");


            // L'appel à la fonction accept met le programme en pause en attendant que le noyau ait réussi un handshake tcp avec un client.
            // Lorsqu'une connection est réussie, on enregistre le numéro de la nouvelle socket qui sera utilisée pour commmuniquer avec le client.
            int socket_nouvelle_connection = accept(numero_socket, (struct sockaddr *)&address, (socklen_t *)&addrlen);

            printf("Connection réussie avec un client\n");

            // On ferme la socket connectée au client
            close(socket_nouvelle_connection);
            // On ferme la socket d'écoute
            close(numero_socket);
            return 0;        

        default:
            break;
    }

    printf("Goodbye!\n");
    exit(0);
}
