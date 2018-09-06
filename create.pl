#!/usr/bin/perl

use warnings;
use strict;

die "program x y density" unless (scalar(@ARGV) == 6);
my ($x, $y, $density, $emp, $obs, $ful) = @ARGV;
print "$y$emp$obs$ful\n";
for (my $i = 0; $i < $y; $i++) {
	for (my $j = 0; $j < $x; $j++) {
		if (int(rand($y) * 2) < $density) {
			print "$obs";
		}
		else {
			print "$emp";
		}
	}
	print "\n";
}
