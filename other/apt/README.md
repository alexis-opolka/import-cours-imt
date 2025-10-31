# Create a mirror of an APT repository


```sh
docker run -it --privileged -v $(pwd):/deb -w /deb --mount type=bind,src=/var/www/html/apt_repository/,dst=/var/www/html/apt_repository debian:bookworm bash
```

```sh
apt update && apt install -y sudo aptly nano
gpg --no-default-keyring --keyring trustedkeys.gpg --keyserver keyserver.ubuntu.com --recv-keys 6ED0E7B82643E131 78DBA3BC47EF2265 F8D2585B8783D481
aptly mirror create -architectures="amd64" bookworm http://ftp.debian.org/debian/ bookworm
aptly mirror update bookworm
```
