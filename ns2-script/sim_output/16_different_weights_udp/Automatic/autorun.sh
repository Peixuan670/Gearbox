#Autorun
#Put this in the Automatic directory

# HCS
cp ../a_1m_1m_01m_1m/HCS_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../a_1m_1m_01m_1m/HCS/

# AFQ10
cp ../a_1m_1m_01m_1m/AFQ10_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../a_1m_1m_01m_1m/AFQ10/

# AFQ100
cp ../a_1m_1m_01m_1m/AFQ100_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../a_1m_1m_01m_1m/AFQ100/

# AFQ1000
cp ../a_1m_1m_01m_1m/AFQ1000_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../a_1m_1m_01m_1m/AFQ1000/

# DropTail
cp ../a_1m_1m_01m_1m/DropTail_out.tr out.tr
bash parse_result.sh

sleep 5

mv ./results/* ../a_1m_1m_01m_1m/DropTail/

