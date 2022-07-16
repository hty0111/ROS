/*
 * @Description: 
 * @version: v1.0
 * @Author: HTY
 * @Date: 2022-07-02 15:41:02
 */

#include "ros/ros.h"

int main(int argc, char * argv[])
{
    ros::init(argc, argv, "hello_world");
    ros::NodeHandle n;
    ROS_INFO("Hello World!");
    
    return 0;
}

