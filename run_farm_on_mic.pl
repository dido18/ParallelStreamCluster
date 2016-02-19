#!/usr/bin/perl -w
use strict;
use warnings FATAL => 'all';

=pod
    run the farm parallel version on the mic with incremental numbers of workers.
    Each configurarion is runned mutiple times as specified by "nTimes" input.
    For Storing the average of the completion time redirect the script.
    es:
      perl run_farm_on_mic.pl simlarge 4 > testResults/farm.output.mic

    the input (simlarge,native) are changed to have more chunks aariving from the stream.
=cut


my $usage="$0 [simlarge, native]  nTimes \n";

my $num_args=$#ARGV + 1;  #ARGV[0] contains the first argument

if($num_args < 2){
    print $usage;
    exit 1;
}

my $test_type = $ARGV[0];
my $times = $ARGV[1];

my $output = "farm.$test_type.mic";

#binary path
my $pathBin = "./ff_streamcluster_mic ";

#load the parmaeters for the binary; simlarge, native has the same number of points but with many chunks.
# (kmin, kmax, dim, n, chuncksize, intermediatecenters, input)
#orginal simmedium:  10 20 64 8192 8192 1000 none  (1 chunk) -> (64 chunks of 128 point)
#original simlarge: 10 20 128 16384 16384 1000 none  (1 chunk)-> (40 chunks of 4000 points)
#original native: 10 20 128 1000000 200000 5000 none (5 chunks with 200000) -> (500 chunks of 200 points)

my @args =("10 20 64 8192 128 1000 none ","10 20 128 16384 4000 1000 none ", "10 20 128 1000000 2000 5000 none ");


my $arg;
if($test_type  eq "simmedium"){
    $arg = "$args[0]";
}
elsif ($test_type  eq "simlarge"){
    $arg = "$args[1]";
}else{
    $arg = "$args[2]";
}

my $arg;
if($test_type  eq "simlarge"){
    $arg = "$args[0]";
}else{
    $arg = "$args[1]";
}

#pfworkers set equal to one
my $pfworkers=1;

#run the script for multiple cores nTimes
foreach my $workers (1,5,10,15,20,25,30,35,40,45,50,55,60,65) {
    my $sum = 0;

    my $runconf = "$pathBin $arg $output $workers $pfworkers ";
    print STDERR "running $runconf :\n";
    foreach my $time (1.. $times){
        my $res = `\\ssh mic0 $runconf 2>&1`;
        print STDERR "$res ";
        $sum = $sum + $res;
    }
    my $avg= $sum/$times;
    print "$workers, $avg\n";
    print STDERR "\n";
}
