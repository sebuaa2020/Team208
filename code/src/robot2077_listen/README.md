## Robot2077_listen

本软件包内部为用户监听模块，目前包含了如下功能

- 监听用户手柄输入
- 监听用户键盘输入

该软件包中的用户监听功能会监听用户输入，并发送给`robot2077_basic`或者其他软件包中。如果是用户对`移动`的控制，则通过`robot2077_basic`软件包中的`robot_move`模块，转发给底层话题`/cmd_vel`。

### 使用方法

在使用前需确保`robot2077_basic`和`robot2077_listen`软件包编译成功

在一个终端控制台中输入如下指令，可以开启`用户监听`功能

```sh
$ roslaunch robot2077_listen user_listen_test.launch
```

此时只能监听用户`手柄`输入，如需监听用户`键盘`输入，则需在另一个终端中，输入

```sh
$ rosrun robot2077_listen keyboard_listen.py
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