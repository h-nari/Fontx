#!/usr/bin/perl

use strict;
use warnings;

my $usage = "$0 fontx_file\n";

die $usage if @ARGV != 1;

my $line_len = 8;
my $file = shift;

my $name = $file;
$name =~ s/\.\w+$//;

open(my $ifp, $file) or die "$file not found.\n";
binmode($ifp);

print "const uint8_t ${name}[] PROGMEM = {\n";

my $data;
do {
    read($ifp, $data,$line_len);
    my @list = unpack("C*", $data);
    print "  ";
    for my $d (@list) {
	printf(" 0x%02x,",$d);
    }
    print "\n";
} while(length($data) == $line_len);

print "};\n";
close($ifp);

    
