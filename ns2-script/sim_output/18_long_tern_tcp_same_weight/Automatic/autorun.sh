#Autorun
#Put this in the Automatic directory

# HCS
cp ../HCS/18_a_HCS_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../HCS/

# AFQ10
cp ../AFQ10/18_a_AFQ10_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../AFQ10/

# AFQ100
cp ../AFQ100/18_a_AFQ100_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../AFQ100/

# AFQ1000
cp ../AFQ1000/18_a_AFQ1000_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../AFQ1000/

# DropTail
cp ../DropTail/18_a_DropTail_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../DropTail/

