#!/usr/bin/perl -wl

#--------------------------------------------------------------------------

# ./average_time.pl file_times
#   execute the average times from the file storing muultiple execution times

#  It is called inside the "streamclusterMgmt.sh" bash script
#---------------------------------------------------------------------------
use strict;
use warnings FATAL => 'all';


# (1) quit unless we have the correct number of command-line args
my $num_args = $#ARGV + 1;

if ($num_args != 1) {
    print "\nUsage: $0 results_file \n";
    exit;
}

my $file = $ARGV[0];
open (FH, "< $file") or die "Can't open $file for read: $!";
my @times;
while (<FH>) {
    push (@times, $_);
}
close FH or die "Cannot close $file: $!";


my @sorted_times = sort @times;

if($#times + 1 > 2) {
    shift @sorted_times;        # remove the first time
    pop @sorted_times;          # remove the last time
}

my $size= @sorted_times;
#print "(perl script) Average execution time from $file of $size times ";
my $sum;                                    # create a variable to hold the sum of the array's values
foreach (@sorted_times) { $sum += $_; }     # add each element of the array to sum
my @final = $sum/@sorted_times;             # divide sum by the number of elements in the # array to find the mean

print @final;

