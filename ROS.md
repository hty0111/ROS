### 核心概念

话题：发布 & 订阅

服务：服务器 & 客户端

### 命令行工具

```shell
rqt_graph	# 可视化节点
rosnode list	# 列出所有节点
rosnode info <node>		# 查看具体节点的信息
rostopic list	# 列出所有话题
rostopic pub -r 10 <topic_name> <msg_struct>	# 以10Hz频率发布
rosmsg show <msg_struct>
rosservice list	# 列出所有服务
rosservice call <service_name> <struct>	# 调用服务
rosbag record -a -O <file>	# 话题记录，全部保存+输出到文件
rosbag play <file>.bag		# 话题复现
```

### 工作空间与功能包

```shell
# 创建工作空间
mkdir ~/catkin_ws/src; cd ~/catkin_ws/src; catkin_init_workspace
# 编译工作空间，生成 devel/ & build/
cd ~/catkin_ws/; catkin_make
# 生成可执行文件 install/
catkin_make install
# 设置环境变量
source devel/setup.bash
# 查看环境变量
echo $ROS_PACKAGE_PATH

# 创建功能包，同一工作空间下不能存在同名功能包
cd ~/catkin_ws/src; catkin_create_pkg <pkg> [depend]
# 编译功能包
cd ~/catkin_ws; catkin_make; source devel/setup.bash
