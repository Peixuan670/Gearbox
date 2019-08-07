#Autorun
#Put this in the Automatic directory

# HCS
cp ../udp-cbr/HCS_udp_large_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../udp-cbr-large/HCS/

# AFQ10
cp ../udp-cbr/AFQ10_udp_large_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../udp-cbr-large/AFQ10/

# AFQ100
cp ../udp-cbr/AFQ100_udp_large_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../udp-cbr-large/AFQ100/

# AFQ1000
cp ../udp-cbr/AFQ1000_udp_large_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../udp-cbr-large/AFQ1000/

# DropTail
cp ../udp-cbr/DropTail_udp_large_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../udp-cbr-large/DropTail/

