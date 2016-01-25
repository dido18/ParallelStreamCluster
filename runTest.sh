#!/bin/bash

#create the folder if doesn't exist
mkdir - p run

bin/ff_stream_cluster 2 5 1 10 10 5 none run/output.fastflow  1
