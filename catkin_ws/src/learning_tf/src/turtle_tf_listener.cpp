//
// Created by hty on 2/22/22.
//

#include <ros/ros.h>
#include <turtlesim/Spawn.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_listener.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_tf_listener");
    ros::NodeHandle node;

    // 产生turtle2
    ros::service::waitForService("/spawn");
    ros::ServiceClient add_turtle = node.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn srv;
    add_turtle.call(srv);

    // 创建速度指令发布者
    ros::Publisher pub_vel = node.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);

    // 创建tf监听者
    tf::TransformListener listener;

    ros::Rate rate = 10;

    while (node.ok())
    {
        tf::StampedTransform transform;

        try
        {
            listener.waitForTransform("/turtle2", "/turtle1", ros::Time(0), ros::Duration(3));
            listener.lookupTransform("/turtle2", "/turtle1", ros::Time(0), transform);
        }
        catch (tf::TransformException & ex)
        {
            ROS_ERROR("%s", ex.what());
            ros::Duration(1).sleep();
            continue;
        }

        geometry_msgs::Twist vel_msg;
        vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) + pow(transform.getOrigin().y(), 2));
        vel_msg.angular.z = 4 * atan2(transform.getOrigin().y(), transform.getOrigin().x());
        pub_vel.publish(vel_msg);

        rate.sleep();
    }

    return 0;
}