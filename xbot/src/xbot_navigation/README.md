# navigation\_sim\_demo

导航演示功能包，本演示包包含以下内容：

* **amcl_demo**: map\_server+amcl 已知地图+自适应蒙特卡洛定位
* **odometry\_navigation\_demo**: 已知地图+仅用里程计（编码器）定位

## amcl示例运行方法

运行：

```sh
$ roslaunch xbot_navigation robot_navigation.launch 
```



## odometry navigation示例运行方法

	roslaunch xbot_sim robot_spawn.launch
	rosrun xbot_sim robot_keyboard_teleop.py
	roslaunch navigation_sim_demo odometry_localization_demo.launch
	roslaunch navigation_sim_demo view_navigation.launch


## 注意事项
如果gazebo出现错误，比如无法查看摄像头换面，你需要升级gazebo到gazebo7及以上版本:
```sh
$ sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
$ wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
$ sudo apt-get update
$ sudo apt-get install gazebo7
```
