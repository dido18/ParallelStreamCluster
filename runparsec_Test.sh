#!/bin/bash

mkdir -p run

parsec_streamcluster/inst/amd64-linux.gcc/bin/streamcluster 2 5 1 10 10 5 none run/output.parsec 1
