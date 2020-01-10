#!/usr/bin/perl
use v5.16.0;
use warnings FATAL => 'all';

use Test::Simple tests => 10;

ok(-e "screenshot.jpg", "screenshot included");
ok(-e "ps-output.txt", "process list from login.ccs included");

sub run {
    my ($cmd, $arg) = @_;
    my $vv = `timeout -s 9 5 "./$cmd" "$arg"`;
    $vv =~ s/result\s*=//;
    chomp $vv;
    return int($vv);
}

sub sq {
    my ($xx) = @_;
    return run("square", $xx);
}

sub cu {
    my ($xx) = @_;
    return run("cube", $xx);
}

if (-x "./square") {
    ok(-x "./square", "square binary executable");
    ok(sq(0) == 0, "sq(0)");
    ok(sq(2) == 4, "sq(2)");
    ok(sq(10) == 100, "sq(100)");
}
else {
    for (1..4) {
        ok(-x "./square", "square binary executable");
    }
}

if (-x "./cube") {
    ok(-x "./cube", "cube binary executable");
    ok(cu(0) == 0, "cu(0)");
    ok(cu(3) == 27, "cu(2)");
    ok(cu(10) == 1000, "cu(100)");
}
else {
    for (1..4) {
        ok(-x "./cube", "cube binary executable");
    }
}


