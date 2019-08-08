#Autorun
#Put this in the Automatic directory

# HCS
cp ../c_tcp_1m_and_100k/HCS_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../c_tcp_1m_and_100k/HCS/

# AFQ10
cp ../c_tcp_1m_and_100k/AFQ10_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../c_tcp_1m_and_100k/AFQ10/

# AFQ100
cp ../c_tcp_1m_and_100k/AFQ100_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../c_tcp_1m_and_100k/AFQ100/

# AFQ1000
cp ../c_tcp_1m_and_100k/AFQ1000_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../c_tcp_1m_and_100k/AFQ1000/

# DropTail
cp ../c_tcp_1m_and_100k/DropTail_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../c_tcp_1m_and_100k/DropTail/

