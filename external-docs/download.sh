#!/bin/bash

[ $# -lt 2 ] && echo "usage: $0 url title [<comments>*]" && exit 1

url="$1"
title="$2"
basedir=$(dirname "$0")
target="$basedir/$title"

set -ex

mkdir -p "$target"
echo "$url" > "$target/link.txt"
for i in ${@:3}; do
  echo $i >> "$target/link.txt"
done
wget -P "$target" "$url"
