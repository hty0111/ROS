//
// Created by hty on 2/21/22.
//

#include <ros/ros.h>
#include "../include/learning_topic/Person.h"

void personInfoCallback(const learning_topic::Person::ConstPtr & msg)
{
    ROS_INFO("Subscribe Person Info:\n name: %s, age: %d, sex: %d",
             msg->name.c_str(), msg->age, msg->sex);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "person_subscriber");
    ros::NodeHandle n;
    ros::Subscriber person_info_sub = n.subscribe<learning_topic::Person>("/person_info", 10, personInfoCallback);
    ros::spin();

    return 0;
}