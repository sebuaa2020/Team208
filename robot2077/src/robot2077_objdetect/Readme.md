#### 功能

​	该软件包主要用于启智ROS机器人模拟器的目标检测。

#### 使用方法

- 首先确保所有编译已经完成；
- 接着首先运行模拟器模块，`roslaunch wpr_simulation wpb_simple.launch`和`roslaunch wpr_simulation wpb_rviz.launch`；
- 随后在另一个终端中运行目标检测节点`rosrun robot2077_objdetect obj_detect`；
- 最后在打开的Rviz中选择展示/robot2077/obj_detect/下的若干主题的点云信息即可。

#### 测试用例

尚未撰写。