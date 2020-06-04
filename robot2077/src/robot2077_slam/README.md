# robot2077_slam

SLAM建图功能包，本包包含以下内容：

* **gmapping_demo**: gmapping SLAM

### gmapping示例运行方法

```sh
$ roslaunch robot2077_slam robot2077_slam.launch
```

然后用键盘控制小车运动，就能在rviz上看到地图的建立过程

在建立地图完成之后，可以调用`map_server`服务保存建立的地图

```sh
$ rosrun map_server map_saver -f map
```

`-f`参数决定保存地图的名称，地图保存形式为`map.yaml和map.pgm`形式保存路径为运行该命令行的路径


### 注意事项

如果gazebo出现错误，比如无法查看摄像头换面，你需要升级gazebo到gazebo7及以上版本:

```sh
$ sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
$ wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
$ sudo apt-get update
$ sudo apt-get install gazebo7
```