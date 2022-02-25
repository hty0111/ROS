//
// Created by hty on 2/21/22.
//

#include <ros/ros.h>
#include "../include/learning_topic/Person.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Person_publisher");
    ros::NodeHandle n;
    ros::Publisher person_info_pub = n.advertise<learning_topic::Person>("/person_info", 10);
    ros::Rate loop_rate = 1;

    while (ros::ok())
    {
        learning_topic::Person person_msg;
        person_msg.name = "HTY";
        person_msg.age = 22;
        person_msg.sex = learning_topic::Person::male;

        person_info_pub.publish(person_msg);
        ROS_INFO("Publish Person Info:\n"
                 "name: %s, age: %d, sex: %d",
                 person_msg.name.c_str(), person_msg.age, person_msg.sex);

        loop_rate.sleep();
    }
}
