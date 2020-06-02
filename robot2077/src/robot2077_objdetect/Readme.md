#### 功能

​	该软件包主要用于启智ROS机器人模拟器的目标检测。

#### 使用方法

- 首先确保所有编译已经完成；
- 接着首先运行模拟器模块，`roslaunch robot2077_objdetect obj_test.launch`和`roslaunch wpr_simulation wpb_rviz.launch`；
- 然后先运行命令`rosrun wpr_simulation keyboard_vel_ctrl `将机器人移动到桌子正前方；
- 随后在另一个终端中运行目标检测节点`rosrun robot2077_objdetect obj_detect`；
- 最后在打开的Rviz中选择展示/robot2077/obj_detect/下的若干主题的点云信息即可。

#### 接口说明

该模块会发布五个主题：

- /robot2077/obj_detect/obj_pc：最终检测出的目标点云；
- /robot2077/obj_detect/obj_mark：最终检测出的目标用矩形框表示出的点云；
- /robot2077/obj_detect/segment_objs：被分割出的目标点云表示；
- /robot2077/obj_detect/segment_planes：被分割出的平面点云表示；
- /robot2077/obj_detect/obj_count：检测出的物体编号列表；