# robot2077_navigation

导航功能包，本演示包包含以下内容：

* **amcl_demo**: map\_server+amcl 已知地图+自适应蒙特卡洛定位

## amcl示例运行方法

运行：

```sh
$ roslaunch robot2077_navigation robot2077_navi.launch 
```

1. 设置导航点：在`rviz`的工具栏中选择`Add Waypoint`,注：如果没有则在点击最后的加号添加这个工具

2. 在设置完所有的导航点之后保存导航点

   ```sh
   $ rosrun waterplus_map_tools wp_saver
   ```

3. 开始巡航：

   ```sh
   $ rosrun waterplus_map_tools wp_nav_test
   ```

   

## 注意事项

如果gazebo出现错误，比如无法查看摄像头换面，你需要升级gazebo到gazebo7及以上版本:

```sh
$ sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
$ wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
$ sudo apt-get update
$ sudo apt-get install gazebo7
```