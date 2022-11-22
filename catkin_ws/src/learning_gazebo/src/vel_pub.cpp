/**
 * @Description: 
 * @version: v1.0
 * @Author: HTY
 * @Date: 2022-11-22 16:11:04
 */

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>


int main(int argc, char* argv[])
{
    ros::init(argc, argv, "roamer");
    ros::NodeHandle node;
    ros::Publisher vel_pub = node.advertise<geometry_msgs::Twist>("cmd_vel", 10);

    while (ros::ok())
    {
        geometry_msgs::Twist vel_msg;
        vel_msg.linear.x = 1;
        vel_pub.publish(vel_msg);

        ros::Duration(0.01);
    }

    return 0;
}

