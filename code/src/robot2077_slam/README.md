# robot2077_slam

SLAM演示功能包，本演示包包含以下内容：

* **gmapping_demo**: gmapping SLAM演示
* **karto_demo**: karto SLAM演示
* **hector_demo**: hector SLAM演示
* **cartographer_demo**: Google catographer演示


### gmapping示例运行方法

首先运行gazebo仿真场景

```sh
$ roslaunch robot2077_slam robot_spawn.launch
```

然后运行键盘控制程序

```sh
$ rosrun robot2077_slam robot_keyboard_teleop.py
```

再运行建图程序gmapping

```sh
$ roslaunch robot2077_slam gmapping_demo.launch
```

最后，启动rviz可视化工具，这里已经添加了一些必须模块，如LaserScan，Map等等

```sh
$ roslaunch robot2077_slam view_slam.launch
```

然后用键盘控制小车运动，就能在rviz上看到地图的建立过程

在建立地图完成之后，可以调用`map_server`服务保存建立的地图

```sh
$ rosrun map_server map_saver -f map
```

`-f`参数决定保存地图的名称，地图保存形式为`map.yaml和map.pgm`形式保存路径为运行该命令行的路径

**简化版**

1. 启动`gazebo,rviz,gmapping`:

   ```sh
   $ roslaunch robot2077_slam robot_slam.launch
   ```

2. 启动键盘控制节点：

   ```sh
   $ rosrun robot2077_slam robot_keyboard_teleop.py
   ```

3. 保存地图

   ```sh
   $ rosrun map_server map_saver -f map
   ```

   


### karto示例运行方法

与gmapping启动方法类似

	roslaunch robot2077_slam robot_spawn.launch
	rosrun robot2077_slam robot_keyboard_teleop.py
	roslaunch robot2077_slam karto_demo.launch
	roslaunch robot2077_slam view_slam.launch

### hector示例运行方法

	roslaunch robot2077_slam robot_spawn.launch
	rosrun robot2077_slam robot_keyboard_teleop.py
	roslaunch robot2077_slam hector_demo.launch
	roslaunch robot2077_slam view_slam.launch


### 注意事项
如果gazebo出现错误，比如无法查看摄像头换面，你需要升级gazebo到gazebo7及以上版本:
```sh
$ sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
$ wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
$ sudo apt-get update
$ sudo apt-get install gazebo7
```
