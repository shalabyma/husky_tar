#include <vector>
#include <map>
#include <ros/ros.h>

class AnchorSequenceTracker{
public:
    AnchorSequenceTracker();

    // TODO: add a service to end the teach step and start the repeat step

    std::vector<int> discover_tags();
    bool is_tag_in_current(int tag);
    bool drop_tag_from_current(int tag_id);
    bool add_tag_to_sequence(std::vector<float> tag_position, int tag_id, int sequence_id);
    
    std::vector<float> get_tag_position(int tag_id, int sequence_id);

private:
    ros::NodeHandle nh;
    
    void load_params();
    
    std::vector<int> anchor_ids;
    std::vector<int> current_sequence;

    // sequence_id -> (tag_position, tag_id)
    std::map<int, std::pair<std::vector<float>, int>> tag_map; 
};