## Robot2077_ui

本软件包内部为界面显示模块，目前包含了如下功能

- 主动控制
- SLAM建图
- 定点导航
- 目标检测

### 介绍

该软件包中的主动控制功能会监听用户输入，并发送给`robot2077_basic`软件包中；同时监听底层话题 /cmd_vel，并在界面中实时反馈。

### 使用方法

在使用前需确保`robot2077_basic` `robot2077_navigation` `robot2077_objdetect` `robot2077_slam` `robot2077_ui` `wpb_sim`软件包编译成功

1. 程序启动：

```sh
$ roslaunch robot2077_objdetect obj_test.launch
$ roslaunch robot2077_ui robot2077_ui
```
