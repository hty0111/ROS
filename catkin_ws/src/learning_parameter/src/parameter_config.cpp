//
// Created by hty on 2/21/22.
//

#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <string>

int main(int argc, char** argv)
{
    int blue_org;
    int blue_set = 100;

    ros::init(argc, argv, "parameter_config");
    ros::NodeHandle node;

    ros::param::get("/turtlesim/background_b", blue_org);
    ROS_INFO("Get background color for blue: %d", blue_org);

    ros::param::set("/turtlesim/background_b", blue_set);
    ROS_INFO("Set background color for blue: %d", blue_set);

    ros::service::waitForService("/clear");
    ros::ServiceClient clear_background = node.serviceClient<std_srvs::Empty>("/clear");
    std_srvs::Empty srv;
    clear_background.call(srv);

    sleep(1);

    return 0;
}