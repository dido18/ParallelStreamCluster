#!/usr/bin/perl -w
use strict;
use warnings FATAL => 'all';

=pod
    Runs the map parallel version in the mic0 with incremental numbers of workers.
    Each configuration is runned "nTimes" times as specified by  parameter.
    The script return the average time among the nTimes execution and the number
    of workers used.

    es:
      perl run_map_on_mic.pl simlarge 4 > testResults/farm.simlarge.mic

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
my $pathBin = "./ff_streamcluster_map_mic ";


#load the conf file args.
my $filename = "conf/$test_type.runconf";
open(my $fh, '<:encoding(UTF-8)', $filename)  or die "Could not open file '$filename' $!";
my $line = <$fh>;   # read the first line
close($fh);

my @words = split /["]/, $line;

my $args = $words[1];

my $runconf;
#run the script for multiple cores nTimes
foreach my $pfworkers (1,5,10,15,20,25,30,35,40,45,50,55,60,65) {
    my $sum = 0;
     $runconf = "$pathBin $args $output $pfworkers ";
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
