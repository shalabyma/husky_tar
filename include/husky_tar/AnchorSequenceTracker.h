#include <vector>
#include <map>
#include <ros/ros.h>

class AnchorSequenceTracker{
public:
    AnchorSequenceTracker();

    void discover_tags();
    bool is_tag_in_current(int* tag);
    void drop_tag_from_current(int* tag_id);
    void add_tag_to_sequence(
        std::vector<float> tag_position, 
        int tag_id, 
        int sequence_id
    );

    void start_repeat_sequence();
    
    std::vector<float> get_tag_position(
        int tag_id, int sequence_id
    );

private:
    ros::NodeHandle nh;
    
    // Service client for initiating TWR transactions from one
    // of the tags on the Husky
    ros::ServiceClient twr_client;
    
    void load_params();
    
    int current_sequence_id;
    std::vector<int> anchor_ids;
    std::vector<int> tag_ids;
    std::vector<int> current_sequence;

    // sequence_id -> (tag_position, tag_id)
    std::map<int, std::pair<std::vector<float>, int>> tag_map; 
};