## Robot2077_basic

本软件包为支持软件，为robot2077项目提供支持。目前包含：

- robot_move，机器人移动控制。该功能在话题`/robot2077/robot_move/vel`中接收其他模块对机器人移动的控制指令(`robot2077_basic::Movemsg`类型)，并通过包装后发布给话题`/cmd_vel`


