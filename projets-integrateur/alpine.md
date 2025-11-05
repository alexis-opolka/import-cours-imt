# Notes and references for the Alpine project

## Goals

Alpine : le terminal en mode graphique

- Créer une machine virtuelle intégrant le système Alpine.

    Télécharger et utiliser le fichier iso 64 bits version 3.22.2 ( téléchargeable sur le site <https://alpinelinux.org/>).
    Télécharger le fichier iso le plus adapté aux  exigences des projets.
- Installer et configurer grub afin de pouvoir démarrer en mode graphique ou en mode console
- Intégrer à minima:

  - openssh (suite logicielle de sécurisation de transmissions)
  - filezilla (client FTP)
  - un navigateur Web
  - tcpdump  (analyseur de trafic en mode console)
  - wireshark (analyseur de trafic en mode graphique)
  - putty (client pour connexion lien série, telnet et SSH).
- Installer les services et modules VMware tools (intégration automatique de la souris, et de la configuration automatique de la résolution d'écran de la machine virtuelle).
- Optimiser le système, afin que la taille du disque dur supportant le système soit minimale (le système doit être opérationnel).

    La commande df permet d’identifier la taille disque utilisée par le système
- Optimiser le système, afin que la taille mémoire (RAM) supportant le système soit minimale (le système doit être opérationnel).

  La commande free permet d’identifier la taille mémoire utilisée par le système

## Quickstart

> [!NOTE] Credentials
>
> |          | Value |
> |----------|-------|
> | Username |  root |
> | Password |  N/A  |

For a quickstart, you can run the image then install it permanently like so:

```sh
setup-alpine
```

and follow the prompts on the console, after that, reboot.

## Commands

## Steps

### Window Manager

> [!NOTE] Reference
> URLs:
>   - <https://ww2.coastal.edu/mmurphy2/oer/alpine/gui-prep/>
>   - <https://wiki.alpinelinux.org/wiki/Alpine_setup_scripts#setup-xorg-base>
>   - <https://wiki.alpinelinux.org/wiki/AwesomeWM#Start_your_desktop>
>   - <https://wiki.alpinelinux.org/wiki/Desktop_environments_and_Window_managers>
>   - <https://awesomewm.org/doc/api/documentation/07-my-first-awesome.md.html#>
>   - <https://github.com/awesomeWM/awesome#>
