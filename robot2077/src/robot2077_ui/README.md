## Robot2077_ui

本软件包内部为界面显示模块，目前包含了如下功能

- 主动控制
- SLAM建图
- 多点导航
- 目标检测

### 介绍



### 使用方法

1.需修改buildmap_dialog.cpp和navigation_dialog.cpp中的绝对路径;
2.在使用前需确保`robot2077_basic` `robot2077_navigation` `robot2077_objdetect` `robot2077_slam` `robot2077_ui` `wpb_sim`软件包编译成功

1. 程序启动：

```sh
$ roslaunch wpb_sim wpb_simple.launch
$ roslaunch robot2077_ui robot2077_ui.launch
```
