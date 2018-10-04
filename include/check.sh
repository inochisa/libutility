#!/bin/bash

for name in $@
do
  echo "----------------$name----------------"
  grep --color=always -rw $name ./*
done
