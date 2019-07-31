#parse the trace of each UDP agents

BEGIN {
}
{
   	action = $1;
   	time = $2;
   	from_node = $3;
   	to_node = $4;
   	type = $5;
   	flow_id = $8; 
   	src_address = $9;
   	dst_address = $10; 
   	seq_no = $11;
   	packet_id = $12;
   	#if ( packet_id > highest_packet_id )
   	#	highest_packet_id = packet_id;
  	#if ( start_time[packet_id] == 0 )  
        #	start_time[packet_id] = time;
  	#if ( flow_id == 2 && action != "d" ) {
        #	if ( action == "r" ) {
        #		end_time[packet_id] = time;
        #	}
   	#}else{
        #	end_time[packet_id] = -1;
   	#}
	printf("Packet %d from Node %d\n", seq_no, src_address)
}                                                                                                           
END {   	
	#for ( packet_id = 0; packet_id <= highest_packet_id; packet_id++ ) {
        #	start = start_time[packet_id];
        #	end = end_time[packet_id];
        #	packet_duration = end - start;
        #	if ( start < end ) printf("%f %f\n", start, packet_duration);
   	#}
}
