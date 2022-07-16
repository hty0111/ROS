# B站 《古月21讲》

2022.2.27

### 命令行工具

```shell
rostopic list	# 列出所有话题
rostopic pub -r 10 <topic> <msg>	# 以10Hz频率发布
rostopic echo <topic>
rostopic echo -b <bag> -p <topic> > <file>.csv/.txt  

rosmsg list
rosmsg show <msg>

rosservice list	# 列出所有服务
rosservice call <service> <srv>	# 调用服务
rosservice info <service>

rossrv list
rossrv show <srv>

rosbag record -a -O <file>	# 话题记录，全部保存+输出到文件
rosbag play <file>.bag		# 话题复现

roscd <pkg>		# 进入功能包
rosls <pkg>		# 列出功能包下的文件
rospack list	# 列出所有功能包
rospack find <pkg>
rosnode list	# 列出所有节点
rosnode info <node>		# 查看具体节点的信息

rqt_graph	# 可视化节点
```

### 工作空间与功能包

```shell
# 创建工作空间
mkdir ~/catkin_ws/src; cd ~/catkin_ws/src; [catkin_init_workspace]
# 编译工作空间，生成 devel/ & build/
cd ~/catkin_ws/; catkin_make
# 生成可执行文件 install/
catkin_make install
# 设置环境变量
echo "source ***catkin_ws/devel/setup.bash" >> ~/.bashrc
# 查看环境变量
echo $ROS_PACKAGE_PATH

# 创建功能包，同一工作空间下不能存在同名功能包
cd ~/catkin_ws/src; catkin_create_pkg <pkg> [dependencies]
# 编译功能包
cd ~/catkin_ws; catkin_make
```

### 话题模型

#### Publisher

1. 初始化 `ROS` 节点
2. 向 `ROS Master` 注册节点信息，包括发布的话题名和话题中的消息类型
3. 创建消息数据
4. 按照一定频率循环发布消息

#### Subscriber

1. 初始化 `ROS` 节点
2. 订阅需要的话题
3. 循环等待话题消息，接收到消息后进入回调函数
4. 在回调函数中完成消息处理

### 服务模型

#### 客户端

1. 初始化 `ROS` 节点
2. 创建一个 `Client` 实例
3. 发布服务请求数据
4. 等待 `Server` 处理之后的应答结果

### 自定义消息

1. 定义 `msg/srv` 文件

```shell
string name
uint8 age
uint8 sex

uint8 unknown = 0
uint8 male = 1
uint8 female = 2
---
string result
```

2. 在 `package.xml` 中添加功能包依赖

```xml
<build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend>
```

3. 在 `CMakeLists.txt` 中添加编译选项

```cmake
find_package(... message_generation)
add_message_files(FILES <file>.msg)
generate_messages(DEPENDENCIES std_msgs)
catkin_package(... message_runtime)
```

4. 编译生成相关文件

```shell
cd ~/catkin_ws; catkin_make
```

### CMakeLists配置

```cmake
# 设置需要编译的代码和生成的可执行文件
add_executable(${PROJECT_NAME}_node ${SRC_LISTS}.cpp)
# 设置链接库
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})
# 自定义消息或服务则需要添加依赖项
add_dependencies(${PROFECT_NAME}_node ${PROJECT_NAME}_generate_messages_cpp)	# 后者无需改动
```

### Launch文件

```xml
<launch>	<!-- 自动启动roscore -->
    <include file="$(fine <file_name>)/.launch"/>	<!-- 包含其他launch文件 -->
    <group ns="">
        <remap from "" to ""/>		<!-- 重映射ROS计算图资源的命名 -->
        <arg name="arg_name" default="arg_value"/>		<!-- launch文件内部的参数 -->
		<node name="" pkg="package_name" name="node_name" type="executable_name" output="screen" ns="" args="$(arg arg_name)" respawn="挂掉是否重启" required="是否必须运行成功">
        	<param name="" value=""/>	<!-- 设置参数 -->
            <rosparam file="file.yaml" command="load" ns="params"/>	<!-- 加载文件中的多个参数 -->
            <env name="" value=""/>
        </node>
    </group>
</launch>
```

