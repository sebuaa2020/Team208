# robot2077_navigation

导航功能包，本演示包包含以下内容：

* **amcl_demo**: map\_server+amcl 已知地图+自适应蒙特卡洛定位

## amcl示例运行方法

运行：

```sh
$ roslaunch robot2077_navigation robot2077_navi.launch 
```


## 注意事项

如果gazebo出现错误，比如无法查看摄像头换面，你需要升级gazebo到gazebo7及以上版本:

```sh
$ sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
$ wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
$ sudo apt-get update
$ sudo apt-get install gazebo7
```