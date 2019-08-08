#Autorun
#Put this in the Automatic directory

# HCS
cp ../a_udp_stop_and_go/HCS_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../a_udp_stop_and_go/HCS/

# AFQ10
cp ../a_udp_stop_and_go/AFQ10_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../a_udp_stop_and_go/AFQ10/

# AFQ100
cp ../a_udp_stop_and_go/AFQ100_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../a_udp_stop_and_go/AFQ100/

# AFQ1000
cp ../a_udp_stop_and_go/AFQ1000_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../a_udp_stop_and_go/AFQ1000/

# DropTail
cp ../a_udp_stop_and_go/DropTail_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../a_udp_stop_and_go/DropTail/

