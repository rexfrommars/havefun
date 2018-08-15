#!/bin/bash

set -x

make clean

make

./client &

pidof client && ./profiler `pidof client`

killall client
