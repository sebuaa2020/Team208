## qtrosan

本软件包为界面软件，为robot2077项目提供交互界面。目前包含：

- qtrosam，机器人移动控制。操作方法：1.勾选Use environment variables选项；2.点击Connect按钮启动节点；3.点击右下角按钮向话题`/robot2077/robot_move/vel`中发送对机器人移动的控制指令(`robot2077_basic::Movemsg`类型)，同时在subscribe方框中会显示当前发送情况。


