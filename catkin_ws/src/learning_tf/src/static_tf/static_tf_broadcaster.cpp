/*
 * @Description: Broadcast pose in laser frame
 * @version: v1.0
 * @Author: HTY
 * @Date: 2022-07-04 20:38:20
 */

#include "ros/ros.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "static_broadcaster");

    // 创建静态坐标转换广播器
    tf2_ros::StaticTransformBroadcaster broadcaster;

    // 创建坐标系信息
    geometry_msgs::TransformStamped ts;
    ts.header.seq = 100;    // 序列号
    ts.header.stamp = ros::Time::now();     // 时间戳
    ts.header.frame_id = "base";
    ts.child_frame_id = "laser";

    ts.transform.translation.x = 0.2;
    ts.transform.translation.y = 0.0;
    ts.transform.translation.z = 0.5;

    tf2::Quaternion quaternion;
    quaternion.setRPY(0, 0, 0);
    ts.transform.rotation.x = quaternion.getX();
    ts.transform.rotation.y = quaternion.getY();
    ts.transform.rotation.z = quaternion.getZ();
    ts.transform.rotation.w = quaternion.getW();

    // 广播器发布坐标系信息
    broadcaster.sendTransform(ts);
    ros::spin();

    return 0;
}

