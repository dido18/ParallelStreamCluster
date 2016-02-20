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


my $usage="$0 [simmedium | simlarge, native]  nTimes \n";

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

#load the conf file args.
my $filename = "conf/$test_type.runconf";
open(my $fh, '<:encoding(UTF-8)', $filename)  or die "Could not open file '$filename' $!";
my $line = <$fh>;   # read the first line
my @words = split /["]/, $line;
close($fh);

my $args = $words[1];
my $runconf;

#run the script for multiple cores nTimes
foreach my $workers (1,5,10,15,20,25,30,35,40,45,50,55,60,65) {
    my $sum = 0;
    $runconf = "$pathBin $args $output $workers $pfworkers ";
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


#not used method
sub getArguments{
    my $testType = $_[0];  #  seconf argument is the rype of test.


    if($testType  eq "simmedium"){
        #points simmedium (8192 points= 64 chunks with 128 points, of 64 dimensions)
        $args = "10 20 64 8192 128 1000 none";
        return  $args;
    }
    elsif ($testType  eq "simlarge") {
        #points simlarge (16384 points = 64 chunks with 256 points of 128 dimensions)
        $args = "10 20 128 16384 256 2000 none";
        return  $args;
    }elsif ($testType  eq "native"){
        #points native (1000000 points = 500 chunksize with 2000 points of 128 dimensions)
        $args = "10 20 128 1000000 2000 5000 none ";
        return  $args;
    }
    else{
        print STDERR "$usage";
        exit 1;
    }
}