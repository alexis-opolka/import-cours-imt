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

- Script de pré-configuration (`/config/scripts/vyos-preconfig-bootup.script`) :

    ```sh
    #!/bin/sh
    # This script is executed at boot time before VyOS configuration is applied.
    # Any modifications required to work around unfixed bugs or use
    # services not available through the VyOS CLI system can be placed here.

    CLEAN_CFG="/config/config.boot.clean"
    TARGET_VYATTA_CFG="/opt/vyatta/etc/config.boot"
    TARGET_VYOS_CFG="/config/config.boot"

    # Only act if the clean config exists
    if [ -f "$CLEAN_CFG" ]; then
        # Copy the clean config over the existing one
        cp "$CLEAN_CFG" "$TARGET_VYATTA_CFG"
        cp "$CLEAN_CFG" "$TARGET_VYOS_CFG"
        echo "$(date '+%Y-%m-%d %H:%M:%S') – Replaced config.boot with clean baseline" >> /var/log/vyos-clean-hook.log
    else
        echo "$(date '+%Y-%m-%d %H:%M:%S') – CLEAN CONFIG NOT FOUND! Skipping replacement." >> /var/log/vyos-clean-hook.log
    fi
    ```

## Configuration file

```conf
interfaces {
    loopback lo {
    }
}
service {
    ntp {
        allow-client {
            address "127.0.0.0/8"
            address "169.254.0.0/16"
            address "10.0.0.0/8"
            address "172.16.0.0/12"
            address "192.168.0.0/16"
            address "::1/128"
            address "fe80::/10"
            address "fc00::/7"
        }
        server time1.vyos.net {
        }
        server time2.vyos.net {
        }
        server time3.vyos.net {
        }
    }
    ssh {
        port "22"
    }
}
system {
    config-management {
        commit-revisions "100"
    }
    conntrack {
        modules {
            ftp
            h323
            nfs
            pptp
            sip
            sqlnet
            tftp
        }
    }
    console {
        device ttyS0 {
            speed "115200"
        }
    }
    host-name "vyos"
    login {
        user vyos {
            authentication {
                encrypted-password "$6$rounds=656000$hqLHyYboR81M1V5P$E/EuJkAJo6Pndizx7z7SgD2yOno5Qis7BhKF5y4u8YxAk2PCPtiFP14Q/x1MrvBzxMh3PEuzh0JpySSt6U8vU/"
                plaintext-password ""
            }
        }
    }
    option {
        keyboard-layout "fr"
    }
    syslog {
        global {
            facility all {
                level "info"
            }
            facility local7 {
                level "debug"
            }
        }
    }
}


// Warning: Do not remove the following line.
// vyos-config-version: "bgp@6:broadcast-relay@1:cluster@2:config-management@1:conntrack@6:conntrack-sync@2:container@2:dhcp-relay@2:dhcp-server@8:dhcpv6-server@1:dns-dynamic@4:dns-forwarding@4:firewall@15:flow-accounting@1:https@6:ids@1:interfaces@32:ipoe-server@3:ipsec@13:isis@3:l2tp@9:lldp@2:mdns@1:monitoring@1:nat@8:nat66@3:ntp@3:openconnect@3:ospf@2:pim@1:policy@8:pppoe-server@10:pptp@5:qos@2:quagga@11:reverse-proxy@1:rip@1:rpki@2:salt@1:snmp@3:ssh@2:sstp@6:system@27:vrf@3:vrrp@4:vyos-accel-ppp@2:wanloadbalance@3:webproxy@2"
// Release version: 1.4.3
```

## References

- <https://docs.vyos.io/en/latest/configuration/index.html>
- <https://docs.vyos.io/en/latest/configuration/interfaces/index.html>
- <https://docs.vyos.io/en/latest/configuration/system/option.html#keyboard-layout>
- <https://docs.vyos.io/en/latest/cli.html#configuration-overview>
- <https://docs.vyos.io/en/latest/installation/index.html>
- <https://docs.vyos.io/en/latest/quick-start.html>
