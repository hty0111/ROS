/*
 * @Description: 
 * @version: v1.0
 * @Author: HTY
 * @Date: 2022-07-04 20:45:22
 */

#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "static_listener");
    ros::NodeHandle n;

    // 创建tf订阅节点
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);

    ros::Rate rate(1);
    while (ros::ok())
    {
        // 在子坐标系中生成坐标点
        geometry_msgs::PointStamped point_laser;
        point_laser.header.frame_id = "laser";
        point_laser.header.stamp = ros::Time::now();
        point_laser.point.x = 1;
        point_laser.point.y = 2;
        point_laser.point.z = 7.3;

        // 坐标点转换，可能由于缓存接收延迟导致失败
        try
        {
            // 新建坐标点用于接收转换结果
            geometry_msgs::PointStamped point_base;
            point_base = buffer.transform(point_laser, "base");
            ROS_INFO("Transformed point: (%.2f, %.2f, %.2f) | Frame: %s", point_base.point.x, point_base.point.y,
                     point_base.point.z, point_base.header.frame_id.c_str());
        }
        catch (const std::exception & ex)
        {
            ROS_ERROR("Fail to transform: %.s", ex.what());
        }

        rate.sleep();
        ros::spinOnce();
    }

    return 0;
}