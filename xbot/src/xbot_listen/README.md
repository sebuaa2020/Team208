## xbot_listen

本软件包内部为用户监听模块，目前包含了如下功能

- 监听用户手柄输入
- 监听用户键盘输入

### 介绍

该软件包中的用户监听功能会监听用户输入，并发送给`xbot_basic`或者其他软件包中。如果是用户对`移动`的控制，则将用户控制使用`xbot_basic`中`Movemsg`使用通道`/xbot/robot_move/vel`发送给`xbot_basic`软件包中的`robot_move`模块，转发给底层话题`/cmd_vel`。

### 使用方法

在使用前需确保`xbot_basic`和`xbot_listen`软件包编译成功

1. 手柄监听：

```sh
$ roslaunch xbot_listen user_joy_listen.launch
```

2. 键盘监听

```sh
$ roslaunch xbot_listen user_keyboard_listen.launch
```

此时在该终端中输入，则可以进行`键盘`控制，具体控制方法如下：

```txt
Control The Robot!
---------------------------
Moving around:
   q    w    e
   a    s    d
   z    x    c

w/W: go forward
x/X: go back
a/A: ture left
d/D: ture right
q/Q: go forward and turn left
e/E: go forward and turn right
z/Z: go back and turn left
c/C: go back and turn right

anything else : force stop

CTRL-C to quit
```

3. 如需使用避障功能，可以使用如下指令，分别启用手柄监听或键盘监听

   - 手柄监听：

   ```sh
   $ roslaunch xbot_listen user_joy_listen_with_avoidance.launch
   ```

   - 键盘监听

   ```sh
   $ roslaunch xbot_listen user_keyboard_listen_with_avoidance.launch
   ```

   