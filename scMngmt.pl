#!/usr/bin/perl -w
use strict;
use warnings FATAL => 'all';
use Switch;

my $usage="$0 [farm | map ] [simsmall | simmedium | simlarge ] nWorkers \n";

my $num_args=$#ARGV + 1;

if($num_args < 3){
    print $usage;
    exit 1;
}

my $simsmall  = "10 20 32 4096 4096 1000 none ";
my $simmedium = "10 20 64 8192 8192 1000 none ";
my $simlarge  = "10 20 128 16384 16384 1000 none ";

my $OUTPUT_PATH = "./run/$1.$2.out";

switch ($$1){

    case "farm" {
        print STDERR "Running "

    }

}