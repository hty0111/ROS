//
// Created by hty on 2/22/22.
//

#include <ros/ros.h>
#include <turtlesim/Pose.h>

void poseCallback(const turtlesim::Pose::ConstPtr & msg)
{
    ROS_INFO("Turtle pose: [x: %.2f, y: %.2f]", msg->x, msg->y);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pose_subscriber");
    ros::NodeHandle node;

    ros::Subscriber pose_sub = node.subscribe<turtlesim::Pose>("/turtle1/pose", 10, poseCallback);
    ros::spin();

    return 0;
}