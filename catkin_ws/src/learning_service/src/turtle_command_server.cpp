//
// Created by hty on 2/21/22.
//

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_srvs/Trigger.h>

ros::Publisher turtle_vel_pub;
bool pubCommand = false;

// service回调函数，输入req，输出res
bool commandCallback(std_srvs::Trigger::Request & req, std_srvs::Trigger::Response & res)
{
    pubCommand = !pubCommand;

    //显示请求数据
    ROS_INFO("Publish turtle velocity command: %s", pubCommand== true ? "Yes" : "No");

    // 设置反馈数据
    res.success = true;
    res.message = "Change turtle command state!";

    return true;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "turtle_command_server");
    ros::NodeHandle node;

    // 创建名为/turtle/command的server，注册回调函数
    ros::ServiceServer command_service = node.advertiseService("/turtle_command", commandCallback);

    // 创建Publisher，发布名为/turtle1/cmd_vel的topic，消息类型为geometry::Twist
    turtle_vel_pub = node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    // 循环等待回调函数
    ROS_INFO("Ready to receive turtle command.");
    ros::Rate loop_rate = 10;

    while (ros::ok())
    {
        // 查看一次回调函数队列
        ros::spinOnce();

        // 如果标志为true，发布速度指令
        if (pubCommand)
        {
            geometry_msgs::Twist vel_msg;
            vel_msg.linear.x = 0.5;
            vel_msg.angular.z = 0.2;
            turtle_vel_pub.publish(vel_msg);
        }

        loop_rate.sleep();
    }

    return 0;
}