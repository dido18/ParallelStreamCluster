#!/usr/bin/perl -wl
use strict;

my $file = "results.txt";
open (FH, "< $file") or die "Can't open $file for read: $!";
my @times;
while (<FH>) {
    push (@times, $_);
}
close FH or die "Cannot close $file: $!";


my @sorted_times = sort @times;

shift @sorted_times;        # remove the first time
pop @sorted_times;          # remove the last time



my $sum;                                    # create a variable to hold the sum of the array's values
foreach (@sorted_times) { $sum += $_; }     # add each element of the array to sum
my @final = $sum/@sorted_times;             # divide sum by the number of elements in the # array to find the mean
print @final;
