set ns [new Simulator]

$ns color 0 Red
$ns color 1 Blue
$ns color 2 Green
$ns color 3 Yellow

$ns color 4 Orange
$ns color 5 Pink
$ns color 6 Brown

set tr [ open "out.tr" w]
$ns trace-all $tr

set ftr [open "out.nam" w]
$ns namtrace-all $ftr

proc finish { } {
	global ns tr ftr
	$ns flush-trace
	close $tr
	close $ftr
	exec nam out.nam &
	}


#create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

set n4 [$ns node]
$n4 shape box
$n4 color green

set n5 [$ns node]
$n5 shape box
$n5 color red

#create link
$ns duplex-link $n0 $n4 2Mb 3ms DropTail
$ns duplex-link $n1 $n4 2Mb 3ms DropTail
$ns duplex-link $n2 $n4 2Mb 3ms DropTail
$ns duplex-link $n3 $n4 2Mb 3ms DropTail
#$ns duplex-link $n4 $n5 4Mb 3ms HRCC
$ns duplex-link $n4 $n5 4Mb 3ms AFQ10
#$ns duplex-link $n4 $n5 4Mb 3ms AFQ100
#$ns duplex-link $n4 $n5 4Mb 3ms AFQ1000
#$ns duplex-link $n4 $n5 4Mb 3ms DropTail

#set nodes position
$ns duplex-link-op $n0 $n4 orient right-up
$ns duplex-link-op $n1 $n4 orient up
$ns duplex-link-op $n2 $n4 orient right-down
$ns duplex-link-op $n3 $n4 orient down
$ns duplex-link-op $n4 $n5 orient right

#for n0 and n5
set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
set null0 [new Agent/Null]
$ns attach-agent $n5 $null0
$ns connect $udp0 $null0
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
$cbr0 set type_ CBR
$cbr0 set packet_size_ 1000
$cbr0 set rate_ 1mb
$cbr0 set random_ false
$udp0 set fid_ 0

#for n1 and n5
set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1
set null1 [new Agent/Null]
$ns attach-agent $n5 $null1
$ns connect $udp1 $null1
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set type_ CBR
$cbr1 set packet_size_ 1000
$cbr1 set rate_ 1mb
$cbr1 set random_ false
$udp1 set fid_ 1


#for n2 and n5
set udp2 [new Agent/UDP]
$ns attach-agent $n2 $udp2
set null2 [new Agent/Null]
$ns attach-agent $n5 $null2
$ns connect $udp2 $null2
set cbr2 [new Application/Traffic/CBR]
$cbr2 attach-agent $udp2
$cbr2 set type_ CBR
$cbr2 set packet_size_ 1000
$cbr2 set rate_ 1mb
$cbr2 set random_ false
$udp2 set fid_ 4

#for n3 and n5
set udp3 [new Agent/UDP]
$ns attach-agent $n3 $udp3
set null3 [new Agent/Null]
$ns attach-agent $n5 $null3
$ns connect $udp3 $null3
set cbr3 [new Application/Traffic/CBR]
$cbr3 attach-agent $udp3
$cbr3 set type_ CBR
$cbr3 set packet_size_ 1000
$cbr3 set rate_ 10mb
$cbr3 set random_ false
$udp3 set fid_ 3

#event
$ns at .1 "$cbr0 start"
$ns at .1 "$cbr1 start"
$ns at .1 "$cbr2 start"
$ns at .1 "$cbr3 start"

$ns at 12 "$cbr0 stop"
$ns at 12 "$cbr1 stop"
$ns at 12 "$cbr2 stop"
$ns at 12 "$cbr3 stop"

$ns at 15.1 "finish"

$ns run
