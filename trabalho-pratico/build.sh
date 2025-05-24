#!/bin/bash

# Obter as flags do pkg-config
CFLAGS=$(pkg-config --cflags glib-2.0)
LIBS=$(pkg-config --libs glib-2.0)

# Compilar o arquivo
clang -fcolor-diagnostics -fansi-escape-codes -g "$1" $CFLAGS $LIBS -o "${1%.*}"
