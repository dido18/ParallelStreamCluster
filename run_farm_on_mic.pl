#!/usr/bin/perl -w
use strict;
use warnings FATAL => 'all';
use POSIX;  #ceil() function
=pod
    Runs the farm parallel version in the mic0 with an incremental numbers of workers.
    Each configurarion is runned mutiple times as specified by "nTimes" input.
    Return the number of workers and the average among the execeution times.

    es:
      perl run_farm_on_mic.pl simlarge 4 > testResults/farm.output.mic

=cut


my $usage="$0 [simmedium | simlarge | native]  nTimes \n";

my $num_args=$#ARGV + 1;  #ARGV[0] contains the first argument

if($num_args < 2){
    print $usage;
    exit 1;
}

my $test_type = $ARGV[0];
my $times = $ARGV[1];


my $output = "farm.$test_type.mic";
my $pathBin = "./ff_streamcluster_farm_mic ";

#load the conf file args.
my $filename = "conf/$test_type.runconf";
open(my $fh, '<:encoding(UTF-8)', $filename)  or die "Could not open file '$filename' $!";
my $line = <$fh>;   # read the first line
my @words = split /["]/, $line;

close($fh);

#my @split= split / / ,$words[1];   # [4] chunksize
#$split[4] = 512;          # same chunk as number of points
#my $args = "@split";

my $args = $words[1];   #arguments input.

my $runconf;

#run the script for multiple cores nTimes
foreach my $workers (1,5,10,15,20,25,30,35,40,45,50,55,60,65) {
    my $sum = 0;
    $runconf = "$pathBin $args $output $workers ";
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
print $runconf;

