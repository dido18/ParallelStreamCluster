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

my $usage="$0 [simmedium | simlarge | native]  nTimes \n";

my $num_args=$#ARGV + 1;  #ARGV[0] contains the first argument

if($num_args < 2){
    print $usage;
    exit 1;
}

my $test_type = $ARGV[0];
my $times = $ARGV[1];


my $output = "map.$test_type.mic";
my $pathBin = "./ff_streamcluster_mic ";

#pfworkers set equal to one
my $workers=1;

#load the conf file args.
my $filename = "conf/$test_type.runconf";
open(my $fh, '<:encoding(UTF-8)', $filename)  or die "Could not open file '$filename' $!";
my $line = <$fh>;   # read the first line
my @words = split /["]/, $line;
close($fh);

my $args = $words[1];

#run the script for multiple cores nTimes
foreach my $pfworkers (1,5,10,15,20,25,30,35,40,45,50,55,60,65) {
    my $sum = 0;
    my $runconf = "$pathBin $args $output $workers $pfworkers ";
    print STDERR "Running $runconf \n";
    foreach my $time (1.. $times){
        my $res = `\\ssh mic0 $runconf 2>&1`;
        print STDERR "$res ";
        $sum = $sum + $res;
    }
    my $avg= $sum/$times;
    print "$pfworkers , $avg\n";
    print STDERR "\n";
}
print $runconf;
