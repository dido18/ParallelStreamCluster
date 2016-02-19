#!/usr/bin/perl -w
use strict;
use warnings FATAL => 'all';
use POSIX;  #ceil() function
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
my $pathBin = "./ff_streamcluster_mic ";

#pfworkers set equal to one
my $pfworkers=1;

#run the script for multiple cores nTimes
foreach my $workers (1,5,10,15,20,25,30,35,40,45,50,55,60,65) {
    my $sum = 0;
    my $args = getArguments($workers, $test_type);
    my $runconf = "$pathBin $args $output $workers $pfworkers ";
    print STDERR "Running $runconf \n";
    foreach my $time (1.. $times){
       my $res = `\\ssh mic0 $runconf 2>&1`;
        print STDERR "$res ";
        $sum = $sum + $res;
    }
    my $avg= $sum/$times;
    print "$workers, $avg\n";
    print STDERR "\n";
}



sub getArguments{
    my $nWorkers = $_[0]; #first argument is the number of workers
    my $testType = $_[1];  #  seconf argument is the rype of test.

    my $args;
    if($testType  eq "simmedium"){
        my $n=8192;             #points simmedium
        my $chunk = ceil($n / $nWorkers);
        $args = "10 20 64 $n $chunk 1000 none";
        return  $args;
    }
    elsif ($testType  eq "simlarge") {
        my $n = 16384;            #points simlarge;
        my $chunk = ceil( $n / $nWorkers );
        $args = "10 20 128  $n $chunk 1000 none";
        return  $args;
    }elsif ($testType  eq "native"){
        my $n=1000000;              #points native;
        my $chunk = ceil($n / $nWorkers);
        $args = "10 20 128 $n $chunk 5000 none ";
        return  $args;
    }
    else{
        print STDERR "$usage";
        exit 1;
    }
}