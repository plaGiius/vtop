
set ns [new Simulator]

set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
global ns nf
$ns flush-trace
close $nf
exec nam out.nam &
exit 0
}

set A [$ns node]
set B [$ns node]
set C [$ns node]
set D [$ns node]
set E [$ns node]

$A color red
$B color blue
$C color yellow
$D color black
$E color green

$ns color 0 green
$ns color 1 red

$ns simplex-link $A $B 2Mb 10ms DropTail
$ns simplex-link $B $C 2Mb 10ms DropTail
$ns simplex-link $C $D 2Mb 10ms DropTail
$ns simplex-link $D $E 2Mb 10ms DropTail
$ns simplex-link $E $A 2Mb 10ms DropTail

set udp0 [new Agent/UDP]
$ns attach-agent $B $udp0

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 1000
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0
$udp0 set fid_ 1

set tcp0 [new Agent/TCP]
$ns attach-agent $A $tcp0 

set ftp [new Application/FTP]
$ftp set maxpkts_ 1000
$ftp attach-agent $tcp0
$tcp0 set fid_ 0

set null0 [new Agent/Null]
$ns attach-agent $D $null0

set sink [new Agent/TCPSink]
$ns attach-agent $E $sink

$ns connect $tcp0 $sink
$ns connect $udp0 $null0



$ns at 3.0 "$cbr0 start"
$ns at 1.0 "$ftp start"
$ns at 3.0 "$ftp stop"
$ns at 5.0 "$cbr0 stop"


$ns at 5.0 "finish"


#puts "CBR packet size = [$cbr0 set packet_size_]"

#puts "CBR interval = [$cbr0 set interval_]"

$ns run
