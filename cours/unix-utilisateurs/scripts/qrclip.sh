#! /bin/env bash

if [ "$1" ]; then
  qrencode "$1" -o - | viu -
else
  qrencode "$(xclip -o)" -o - | viu -
fi
