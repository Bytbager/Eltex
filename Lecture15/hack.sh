#!/bin/bash

gcc pass_creator.c -o pass_creator
./pass_creator >> pass.txt
gcc ispassok.c -o ispassok -fno-stack-protector -no-pie -g
./ispassok < pass.txt