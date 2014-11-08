#!/usr/bin/perl
use Data::Dumper;
use List::Util qw(min max);
use Storable qw(dclone);
use warnings;
use strict;

if (@ARGV != 1) {
    die "Usage: $0 <file>\n";
}

my %E = ();
my %UE = ();
my $m = 0;

open my $fh, '<', $ARGV[0]
    or die "$!\n";
while (my $line = <$fh>) {
    my ($v, @U) = split /\s+/, $line;
    foreach my $u (@U) {
        my $min = min($v, $u);
        my $max = max($v, $u);

        $E{$u}->{$v}++;
        ++$m unless exists $UE{$min}->{$max};
        $UE{$min}->{$max} = 1;
    }
}
close $fh;

my $n = keys %E;

print $n, " vertices and ", $m, " edges\n";

my $res = 100000;
for my $i (1..($n*$n)) {
    my %tE = %{ dclone \%E};
    my %tUE = %{ dclone \%UE };

    $res = min($res, min_cut(\%tE, \%tUE, $n, $m));
    if ($i % 100 == 0) {
        print time().": $i (result is $res)\n";
    }
}

print $res."\n";

exit(0);


sub min_cut {
    my ($E, $UE, $n, $m) = @_;
    srand();

    # print Dumper($E);
    # print Dumper($UE);
    # print "---------------------------\n";

    while (keys %$E > 2) {
        my $r = int(rand($m));
        my ($u, $v);
        my $i = 0;
        for my $k1 (keys %{$UE}) {
            for my $k2 (keys %{$UE->{$k1}}) {
                $i += $UE->{$k1}->{$k2};
                if ($i >= $r) {
                    $u = $k1;
                    $v = $k2;
                    last;
                }
            }
        }

        # print $n, " vertices and ", $m, " edges\n";
        # print "merging $u and $v\n";

        $m -= $E->{$u}->{$v};
        delete $E->{$u}->{$v};
        delete $E->{$v}->{$u};
        my @arr = keys %{$E->{$v}};
        foreach my $key (@arr) {
            my $val = $E->{$v}->{$key};
            $E->{$u}->{$key} += $val;
            $E->{$key}->{$u} += $E->{$key}->{$v};
            my $min = min($u, $key);
            my $max = max($u, $key);
            # $UE->{$min}->{$max} += $E->{$key}->{$v};
            delete $E->{$key}->{$v};
        }
        delete $E->{$v};
        delete $UE->{$u}->{$v};
        unless (keys %{$UE->{$u}}) {
            delete $UE->{$u};
        }

        @arr = keys %{$UE};
        foreach my $key (@arr) {
            my $val = $UE->{$key};
            my $min = min($u, $key);
            my $max = max($u, $key);
            if (($key != $v) && exists $UE->{$key}->{$v}) {
                # print "2:\n";
                # print "add $key:$v ($UE->{$key}->{$v}) to $min:$max\n";
                $UE->{$min}->{$max} += $UE->{$key}->{$v};
                delete $UE->{$key}->{$v};
                unless (keys %{$UE->{$key}}) {
                    delete $UE->{$key};
                }
                # print "2 END\n";
            }
            if ($key == $v) {
                my @arr1 = keys %{$UE->{$v}};
                foreach my $key1 (@arr1) {
                    # print "1:\n";
                    my $val1 = $UE->{$v}->{$key1};
                    my $min = min($u, $key1);
                    my $max = max($u, $key1);
                    # print Dumper($UE);
                    # print "add $v:$key1 ($val1) to $min:$max\n";
                    $UE->{$min}->{$max} += $UE->{$v}->{$key1};
                    # print Dumper($UE);
                    # print "1 END\n";
                }
                delete $UE->{$v};
            }
        }

        --$n;

        # print Dumper($E);
        # print Dumper($UE);
        # print "---------------------------\n";
    }

    for my $t1 (keys %$UE) {
        for my  $t2 (keys %{$UE->{$t1}}) {
            return $UE->{$t1}->{$t2};
        }
    }
}

sub rm_self_loops {
}
