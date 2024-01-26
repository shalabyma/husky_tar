#include "AnchorSequenceTracker.h"

// TODO: do discover_tags only when current_sequence is empty

AnchorSequenceTracker::AnchorSequenceTracker(){
    load_params();
}

void AnchorSequenceTracker::load_params(){
    nh.param("anchors", anchor_ids, std::vector<int>());
}