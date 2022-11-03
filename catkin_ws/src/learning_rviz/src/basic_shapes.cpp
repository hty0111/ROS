/*
 * @Description: 绘制基本图形
 * @version: v1.0
 * @Author: HTY
 * @Date: 2022-11-02 12:11:15
 */

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "basic_shapes");
    ros::NodeHandle node;
    ros::Publisher marker_pub = node.advertise<visualization_msgs::Marker>("visualization_marker", 1);  // rviz默认的接收topic

    // set initial shape type
    int shape = visualization_msgs::Marker::CUBE;

    ros::Rate rate(1);
    while (ros::ok())
    {
        visualization_msgs::Marker marker;

        // frame ID & time stamp
        marker.header.frame_id = "base";
        marker.header.stamp = ros::Time::now();

        // ns & id make the marker the unique one
        marker.ns = "basic_shapes";
        marker.id = 0;

        marker.type = shape;

        // ADD, DELETE
        marker.action = visualization_msgs::Marker::ADD;

        // set pose
        marker.pose.position.x = 0;
        marker.pose.position.y = 0;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0;
        marker.pose.orientation.y = 0;
        marker.pose.orientation.z = 0;
        marker.pose.orientation.w = 1;

        // set scale -- 1x1x1 means 1m on a side
        marker.scale.x = 1;
        marker.scale.y = 1;
        marker.scale.z = 1;

        // set color
        marker.color.r = 0;
        marker.color.g = 1;
        marker.color.b = 0;
        marker.color.a = 1;

        marker.lifetime = ros::Duration();  // never auto delete

        // publish the marker
        while (marker_pub.getNumSubscribers() < 1)
        {
            if (!ros::ok())
                return 0;
            ROS_WARN_ONCE("Please create a subscriber for marker.");
            sleep(1);
        }
        marker_pub.publish(marker);

        // change shapes
        switch (shape)
        {
            default:
            case visualization_msgs::Marker::CUBE:
                shape = visualization_msgs::Marker::SPHERE;
                break;
            case visualization_msgs::Marker::SPHERE:
                shape = visualization_msgs::Marker::ARROW;
                break;
            case visualization_msgs::Marker::ARROW:
                shape = visualization_msgs::Marker::CYLINDER;
                break;
            case visualization_msgs::Marker::CYLINDER:
                shape = visualization_msgs::Marker::CUBE;
                break;
        }

        rate.sleep();
    }
}

