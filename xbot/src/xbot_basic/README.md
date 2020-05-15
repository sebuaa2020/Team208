## xbot_basic

本软件包为支持软件，为`xbot`项目提供支持。目前包含：

- `robot_move`，机器人移动控制。
- `robot_avoidance`，机器人避障模块。
- `msg：Movemsg`，上层应用使用该消息与机器人移动模块交互。
- `srv：IsAvoidance`，机器人避障模块提供的避障查询服务。

### 介绍

- #### robot_move

  该功能在话题`/xbot/robot_move/vel`中接收其他模块对机器人移动的控制指令(`xbot_basic::Movemsg`类型)，并通过包装后发布给话题`/cmd_vel`。在发布前，会向`robot_avoidance`模块确认是否有障碍物。该模块中有参数`LINEAR_VEL_MAX`，`ANGULAR_VEL_MAX`来控制机器人在各个方向移动速度的最大值

- #### robot_avoidance

  该模块实时监听`/scan`中`激光传感器`发布的距离数据，然后提供`避障查询服务`。避障使用一种缓冲方法，当机器人离障碍物小于一定距离(`AVOIDANCE_DIS_MAX`)时开始减速，当距离小于某一值(`AVOIDANCE_DIS_MIN`)时置为0。

### 使用方法

使用如下指令运行机器人移动控制模块：

```sh
$ rosrun xbot_basic robot_move
```

在不开启`robot_avoidance`节点时，不会启用避障功能。如需使用避障功能，可以在一般机器人控制基础上，运行该节点。也可使用如下指令：

```sh
$ roslaunch xbot_listen user_listen_with_avoidance.launch
```

### 注意

由于激光雷达传感器的扫描范围只有`-135° ~ +135°`，因此为了正常进行避障检测，我们禁止了向后运动的请求。