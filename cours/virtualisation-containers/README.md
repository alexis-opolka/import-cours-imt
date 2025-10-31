# Virtualisation et conteneurisation

> [!NOTE]
> Support de cours: <https://formations.microlinux.fr/>

## Base de docker

### Challenge 1

- Almalinux: <https://hub.docker.com/_/almalinux>

    ```sh
    docker run -it almalinux:latest /bin/bash
    ```

- ArchLinux: <https://hub.docker.com/_/archlinux>

    ```sh
    docker run -it archlinux:latest /bin/bash
    ```

### Challenge 2

> [!NOTE]
> These two distributions doesn't have any `latest` tag, we fall back to
> `9` and `10` respectively.
>
> We can tag it back as a `latest` build later on.

- RockyLinux: <https://hub.docker.com/_/rockylinux>

    ```sh
    docker run -it rockylinux:latest /bin/bash
    ```

- Oracle Linux: <https://hub.docker.com/_/oraclelinux>

    ```sh
    docker run -it oraclelinux:latest /bin/bash
    ```

### Challenge 3

- Lancer une alpine

    ```sh
    docker run -it alpine /bin/sh
    ```

L'image docker de base n'a pas de commande de base, le conteneur ne restera pas en cours d'exécution.

### Challenge 4

```sh
docker image ls
```

## Les images docker

- L'image officielle de memcached: <https://hub.docker.com/_/memcached>
- L'image de Apache en mouture `2-alpine`:

    ```sh
    docker pull http:2-alpine
    ```

- Taille des images utilisée

    ```sh
    REPOSITORY   TAG        IMAGE ID       CREATED        SIZE
    memcached    latest     8101c3194bb0   2 months ago   85MB
    httpd        2-alpine   506d7042d2f4   3 months ago   64.6MB
    ```

## Exécuter un conteneur

- L'image officielle de redis: <https://hub.docker.com/_/redis>

- Conteneur Redis:

    ||     ID     |     Nom     |
    ||------------|-------------|
    ||f6bd538551db|strange_haibt|

- Nommer son conteneur

    ```sh
    docker run --name conteneur_redis -d redis
    ```

- Autodestruction du conteneur

    ```sh
    docker run --rm hello-world
    ```

- conteneur an arrière-plan

    ```sh
    docker run -d hello-world
    ```

- Récupération des logs

    ```sh
    docker logs <container-name>
    ```

- Récupération des logs avec timestamp

    ```sh
    docker logs -t <container-name>
    ```

## Exposer un conteneur

- Image officielle de Apache: <https://hub.docker.com/_/httpd>
- Exposer le port 80 via le port 9900 de l'hôte:

    ```sh
    docker run --name apache_bienvenue -d -p 9900:80 nginx
    ```

- Page par défaut du serveur HTTPD

    ```sh
    curl localhost:9900
    ```

    donne

    ```html
    <html><body><h1>It works!</h1></body></html>
    ```

- Volume mount

    ```sh
    docker run --name apache_coucou -p 9901:80 -v ./src/mapage:/usr/local/apache2/htdocs httpd
    ```

- Logs `apache_bienvenue`:

    ```sh
    AH00558: httpd: Could not reliably determine the server's fully qualified domain name, using 172.17.0.4. Set the 'ServerName' directive globally to suppress this message
    AH00558: httpd: Could not reliably determine the server's fully qualified domain name, using 172.17.0.4. Set the 'ServerName' directive globally to suppress this message
    [Wed Oct 29 09:06:53.537202 2025] [mpm_event:notice] [pid 1:tid 1] AH00489: Apache/2.4.65 (Unix) configured -- resuming normal operations
    [Wed Oct 29 09:06:53.539249 2025] [core:notice] [pid 1:tid 1] AH00094: Command line: 'httpd -D FOREGROUND'
    172.17.0.1 - - [29/Oct/2025:09:06:57 +0000] "GET / HTTP/1.1" 200 45
    ```

- Logs `apache_coucou`:

    ```sh
    AH00558: httpd: Could not reliably determine the server's fully qualified domain name, using 172.17.0.5. Set the 'ServerName' directive globally to suppress this message
    AH00558: httpd: Could not reliably determine the server's fully qualified domain name, using 172.17.0.5. Set the 'ServerName' directive globally to suppress this message
    [Wed Oct 29 09:04:25.896033 2025] [mpm_event:notice] [pid 1:tid 1] AH00489: Apache/2.4.65 (Unix) configured -- resuming normal operations
    [Wed Oct 29 09:04:25.897959 2025] [core:notice] [pid 1:tid 1] AH00094: Command line: 'httpd -D FOREGROUND'
    172.17.0.1 - - [29/Oct/2025:09:04:35 +0000] "GET / HTTP/1.1" 200 18
    172.17.0.1 - - [29/Oct/2025:09:05:50 +0000] "GET / HTTP/1.1" 200 18
    ```
