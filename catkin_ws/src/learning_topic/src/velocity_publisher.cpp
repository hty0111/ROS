//
// Created by hty on 2/21/22.
//

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "velocity_publisher");
    ros::NodeHandle node;

    ros::Publisher vel_pub = node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    ros::Rate rate = 10;

    while (ros::ok())
    {
        geometry_msgs::Twist vel_msg;
        vel_msg.linear.x = 0.5;
        vel_msg.angular.z = 0.2;
        vel_pub.publish(vel_msg);

        ROS_INFO("Publish turtle velocity: [x = %.2f, yaw = %.2f]",
                 vel_msg.linear.x, vel_msg.angular.z);
        rate.sleep();
    }

    return 0;
}