#!/bin/bash

make

set -x

time ./strplus > /dev/null

time ./strstream > /dev/null

