#!/usr/bin/perl -w
use strict;
use warnings FATAL => 'all';

=pod
    run the map parallel version  setting workers=1 on the mic with incremental numbers of pfworkers.
    Each configurarion is runned mutiple times as specified by "nTimes" input.
    For Storing the average of the completion time redirect the script.
    es:
      perl run_map_on_mic.pl simlarge 4 > testResults/farm.output.mic
=cut

my $usage="$0 [simmedium, simlarge, native] nWorkers \n";

my $num_args=$#ARGV + 1;  #ARGV[0] contains the first argument

if($num_args < 2){
    print $usage;
    exit 1;
}

my $test_type = $ARGV[0];
#my $times = $ARGV[1];
my $workers = $ARGV[1];

my $output = "rodinia.$test_type.mic";

#binary path
my $pathBin = "./rodinia_mic ";

#load the parmaeters for the binary; simmedium, simlarge, native.
#my @args =("10 20 64 8192 8192 1000 none ","10 20 128 16384 16384 1000 none ", "10 20 128 1000000 200000 5000 none ");

my @args =("10 20 64 8192 8192 1000 none ","10 20 128 16384 16384 1000 none ", "10 20 128 1000000 2000 5000 none ");

my $arg;
if($test_type  eq "simmedium"){
    $arg = "$args[0]";
}
elsif ($test_type  eq "simlarge"){
    $arg = "$args[1]";
}else{
    $arg = "$args[2]";
}


#pfworkers set equal to one
#my $pfworkers=1;


#run the script for multiple cores nTimes
#foreach my $workers (1,5,10,15,20,25,30,35,40,45,50,55,60,65) {
#    my $sum = 0;

    my $runconf = "$pathBin $arg $output $workers";# $pfworkers ";
    print STDERR "running $runconf \n";
#    foreach my $time (1.. $times){
        my $res = `\\ssh mic0 $runconf 2>&1`;
        print STDERR "$res ";
#        $sum = $sum + $res;
#    }
#    my $avg= $sum/$times;
#    print "$workers, $avg\n";
#    print STDERR "\n";
#}