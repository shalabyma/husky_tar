#include "AnchorSequenceTracker.h"
#include "uwb_msgs/InitiateTwr.h"

// TODO: do discover_tags only when current_sequence is empty

AnchorSequenceTracker::AnchorSequenceTracker(){
    load_params();

    std::string service_name("initiate_from_" + std::to_string(tag_ids[0]));
    twr_client = nh.serviceClient<uwb_msgs::InitiateTwr>(service_name);
}

void AnchorSequenceTracker::load_params(){
    nh.param("anchors", anchor_ids, std::vector<int>());
    nh.param("tags", tag_ids, std::vector<int>());
}

void AnchorSequenceTracker::discover_tags(){
    for (int anchor_id : anchor_ids){
        uwb_msgs::InitiateTwr srv;
        srv.request.target_id = anchor_id;
        if (twr_client.call(srv)){
            current_sequence.push_back(anchor_id);
        }
    }
}

bool AnchorSequenceTracker::is_tag_in_current(int* tag){
    return std::find(
        current_sequence.begin(), 
        current_sequence.end(), 
        *tag
    ) != current_sequence.end();
}

void AnchorSequenceTracker::drop_tag_from_current(int* tag_id){
    current_sequence.erase(
        std::remove(
            current_sequence.begin(), 
            current_sequence.end(), 
            *tag_id
        ), 
        current_sequence.end()
    );
}

void AnchorSequenceTracker::add_tag_to_sequence(
    std::vector<float> tag_position, 
    int tag_id, 
    int sequence_id
){
    tag_map[sequence_id] = std::make_pair(tag_position, tag_id);
}

void AnchorSequenceTracker::start_repeat_sequence(){
    current_sequence_id = 0;
}

std::vector<float> AnchorSequenceTracker::get_tag_position(
    int tag_id, int sequence_id
){
    if (tag_id != tag_map[sequence_id].second){
        ROS_ERROR("Tag ID %d does not match tag ID %d in sequence %d", 
            tag_id, tag_map[sequence_id].second, sequence_id);
    }
    return tag_map[sequence_id].first;
}

