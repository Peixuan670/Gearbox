#Autorun
#Put this in the Automatic directory

# HCS
cp ../udp-cbr/HCS_udp_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../udp-cbr/HCS/

# AFQ10
cp ../udp-cbr/AFQ10_udp_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../udp-cbr/AFQ10/

# AFQ100
cp ../udp-cbr/AFQ100_udp_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../udp-cbr/AFQ100/

# AFQ1000
cp ../udp-cbr/AFQ1000_udp_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../udp-cbr/AFQ1000/

# DropTail
cp ../udp-cbr/DropTail_udp_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../udp-cbr/DropTail/

