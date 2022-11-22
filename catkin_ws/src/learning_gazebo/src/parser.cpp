/**
 * @Description: 解析urdf模型
 * @version: v1.0
 * @Author: HTY
 * @Date: 2022-11-21 13:45:42
 */


#include <urdf/model.h>
#include <ros/ros.h>

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "parser");
    if (argc != 2)
    {
        ROS_ERROR("Need a urdf file as input.");
        return -1;
    }
    std::string urdf_file = argv[1];

    urdf::Model model;
    if (!model.initFile(urdf_file))
    {
        ROS_ERROR("Fail to parse the urdf file.");
        return -1;
    }

    ROS_INFO("Successfully parsed the urdf file");
    return 0;
}
