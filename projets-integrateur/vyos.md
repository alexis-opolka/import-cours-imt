# Notes and references for the VyOS project

## Goals

- Créer une machine virtuelle intégrant le système VyOS.

    Le système doit être installé sur le disque virtuel de la machine virtuel.
    Nous vous fournissons la version 1.4.3.

- Intégrer automatiquement le clavier azerty.
- Homogénéiser automatiquement les noms des interfaces réseaux des machines virtuelles clonées :

    - Si une seule carte réseau virtuelle est rattachée à la machine virtuelle clonée, l’interface réseau devra se nommer eth0.
    - Si deux cartes réseaux virtuelles sont rattachées à la machine virtuelle clonée, les interfaces réseaux devront se nommer eth0 et eth1.

## Quickstart

For a quickstart, you can run the image then install it permanently like so:

```sh
install image
```

and follow the prompts on the console, after that, reboot.


## Commands

- Passer en clavier FR

    ```sh
    config
    set system option keyboard-layout fr
    commit
    save
    exit
    ```

- Passer le SSH sur le port 22 uniquement

    ```sh
    config
    set service ssh port '22'
    commit
    save
    exit
    ```

- Nettoyer les MAC au démarrage :

    > [!NOTE] Ficher de configuration impacté
    > Le chemin du fichier est: `/config/scripts/vyos-postconfig-bootup.script`.\
    > La documentation est: <https://docs.vyos.io/en/1.4/automation/command-scripting.html#postconfig-on-boot>

    ```sh
    ip a | grep eth | sed -nE 's/.*\b(eth[0-9]+)\b.*/\1/p'
    ```

## References

- <https://docs.vyos.io/en/latest/configuration/index.html>
- <https://docs.vyos.io/en/latest/configuration/interfaces/index.html>
- <https://docs.vyos.io/en/latest/configuration/system/option.html#keyboard-layout>
- <https://docs.vyos.io/en/latest/cli.html#configuration-overview>
- <https://docs.vyos.io/en/latest/installation/index.html>
- <https://docs.vyos.io/en/latest/quick-start.html>
