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

## Steps

- Add a stable, authenticated remote access

  ```sh
  ssh-keygen -t ed25519 -C "admin@localhost" # We let SSH create the ~/.ssh folder with the right permissions
  vi ~/.ssh/authorized_keys ### <-- We add the copied public fingerprint of our SSH Key
  ```

- Update the Bootloader (Defaut: SysLinux)

  > [!NOTE]
  > - The reference of Alpine regarding bootloaders is: [wiki.alpinelinux.org/wiki/Bootloaders#Syslinux](https://wiki.alpinelinux.org/wiki/Bootloaders#Syslinux)
  > - The reference of the SysLinux Bootloader is: [wiki.syslinux.org/wiki/index.php?title=SYSLINUX](https://wiki.syslinux.org/wiki/index.php?title=SYSLINUX)


- Allow the community repository for APK

  Uncomment the line into the following file:

  ```
  nano /etc/apk/repositories
  ```

  which is:

  ```sh
  #/media/cdrom/apks
  http://pkg.adfinis-on-exoscale.ch/alpine/v3.22/main
  http://pkg.adfinis-on-exoscale.ch/alpine/v3.22/community
  ```

- Build and install a Window Manager

  First, install the necessary dependencies:

  - Build requirements

    ```sh
    apk add curl git gcc cmake make clang build-base llvm-static\
      llvm-dev clang-static clang-dev imagemagick libxcb-dev cairo-dev\
      libx11-dev xcb-util-wm-dev xcb-util-cursor-dev xcb-util-keysyms-dev xcb-util-dev\
      xcb-util-xrm-dev libxdg-basedir-dev libxkbcommon-x11 libxkbcommon-dev\
      startup-notification-dev gdk-pixbuf-dev gobject-introspection-dev pango-dev
    ```

  - Lua download & Build:

    ```
    curl -L -R -O https://www.lua.org/ftp/lua-5.4.8.tar.gz
    tar zxf lua-5.4.8.tar.gz
    cd lua-5.4.8
    make all test
    make install
    ```

  - Lua LGI download & Build:

  ```sh
  luarocks install https://raw.githubusercontent.com/lgi-devs/lgi/master/lgi-scm-1.rockspec
  ```

  Then, clone the repository:

  ```sh
  git clone https://github.com/awesomewm/awesome
  ```

  and build it:

  ```sh
  make
  make install
  ```

- Now, Prepare the GUI server and libs

  ```sh
  apk add xorg-server xf86-input-libinput xinit mesa-dri-gallium xterm font-terminus\
    xf86-input-synaptics
  ```

- Set awesome as the WM for the X Server

  ```sh
  echo 'awesome' >> /home/test/.xinitrc
  ```

- Copy the shared templates to have our configuration ready to use (easy way)

  ```sh
  git clone --recurse-submodules --remote-submodules --depth 1 -j 2 https://github.com/lcpz/awesome-copycats.git
  mkdir -p ~/.config/awesome && mv awesome-copycats/* ~/.config/awesome
  cd ~/.config/awesome
  cp rc.lua.template rc.lua
  ```

  In this case, we're going to use the `powerarrow` theme.\
  We then need to modify the `~/.config/awesome/rc.lua` file.

  > [!NOTE] References
  > [github.com/lcpz/awesome-copycats/tree/master](https://github.com/lcpz/awesome-copycats/tree/master)

  La ligne à modifier dans le fichier est la ligne `101`.


> [!NOTE] Reference
> URLs:
>   - <https://ww2.coastal.edu/mmurphy2/oer/alpine/gui-prep/>
>   - <https://wiki.alpinelinux.org/wiki/Alpine_setup_scripts#setup-xorg-base>
>   - <https://wiki.alpinelinux.org/wiki/AwesomeWM#Start_your_desktop>
>   - <https://wiki.alpinelinux.org/wiki/Desktop_environments_and_Window_managers>
>   - <https://awesomewm.org/doc/api/documentation/07-my-first-awesome.md.html#>
>   - <https://github.com/awesomeWM/awesome#>
