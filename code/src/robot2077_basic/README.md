## Robot2077_basic

本软件包为支持软件，为`robot2077`项目提供支持。目前包含：

- `robot_move`，机器人移动控制。该功能在话题`/robot2077/robot_move/vel`中接收其他模块对机器人移动的控制指令(`robot2077_basic::Movemsg`类型)，并通过包装后发布给话题`/cmd_vel`。在发布前，会向`robot_avoidance`模块确认是否有障碍物。
- `robot_avoidance`，机器人避障模块。该模块实时监听`/scan`中`激光传感器`发布的距离数据，然后提供`避障查询服务`。

### 使用方法

在不开启`robot_avoidance`节点时，不会启用避障功能。如需使用避障功能，可以在一般机器人控制基础上，运行该节点。也可使用如下指令：

```sh
$ roslaunch robot2077_listen user_listen_with_avoidance.launch
```

### 注意

由于激光雷达传感器的扫描范围只有`-135° ~ +135°`，因此为了正常进行避障检测，我们禁止了向后运动的请求。