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
