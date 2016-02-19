#!/usr/bin/perl -w
use strict;
use warnings FATAL => 'all';
use autodie; # die if problem reading or writing a file

=pod
scMgmnt.pl [test, simlarge, native] nWorkers PFworkers nTimes
    run the program for the input  nTimes with a incremental number of workers.
    if mic is present executed inthe mic machine
=cut

my $usage="$0  [test, simlarge, native] nWorkers PFworkers nTimes \n";

my $num_args=$#ARGV + 1;  #ARGV[0] contains the first argument

if($num_args < 3){
    print $usage;
    exit 1;
}

my $bin = $ARGV[0];
my $in =  $ARGV[1];
my $Times = $ARGV[2];
my $output = "$bin.$in.output";


#load the binary path
my $fileBin = "./conf/$bin.bin";
open(fhBin, "< $fileBin" )  or die "can't open $fileBin  filename: $!";
my $pathBin =<fhBin>;
close(fhBin);

if($mic eq 1){
    $pathBin = "./ff_streamcluster_mic";
}

#load the parmaeters fot he binary
my $fileRun = "./conf/$in.args";
open(fhRun, "< $fileRun" )  or  die "can't open $fileRun  filename: $!";
my $args =<fhRun>;
close(fhRun);

my $pfworkers = 1;


#run the script for multiple cores nTimes
foreach my $proc (1,2,4,8,15,25,32,60,70,100) { # the number of workers to be utilized
    my $sum=0;
    my $times = ();
    my $finalArgs = "$pathBin $args $output $proc $pfworkers";#print $finalArgs;

    print STDERR "$proc cores\n";
    foreach my $time (1..$Times){
            print "running $finalArgs...";
            my $res = `\\ssh mic0 "$finalArgs" 2>&1`;
            sleep(1);
            print $res;

    }
    print STDERR "\n";


}

