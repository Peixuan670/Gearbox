#Autorun
#Put this in the Automatic directory

# HCS
cp ../b_1m_and_10k/HCS_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../b_1m_and_10k/HCS/

# AFQ10
cp ../b_1m_and_10k/AFQ10_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../b_1m_and_10k/AFQ10/

# AFQ100
cp ../b_1m_and_10k/AFQ100_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../b_1m_and_10k/AFQ100/

# AFQ1000
cp ../b_1m_and_10k/AFQ1000_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../b_1m_and_10k/AFQ1000/

# DropTail
cp ../b_1m_and_10k/DropTail_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../b_1m_and_10k/DropTail/

