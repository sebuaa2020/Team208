# 导航模块单元测试文档

## API测试

1. 运动信息重定向函数`trans`测试：

   * 函数功能：将导航模块确定的控制机器人运动信息导入自定义的`move`模块进行统一处理

   * 输入：`Twist.msg`类型数据

     |      字段       |     含义     |
     | :-------------: | :----------: |
     | Vector3 linear  | 水平运动控制 |
     | Vector3 angular | 转动角度控制 |

   * 输出：`Movemsg.msg`类型

     |   字段    |    含义     |
     | :-------: | :---------: |
     | float32 x | x轴方向速度 |
     | float32 y | y轴方向速度 |
     | float32 z | z轴方向速度 |

     保证：

     1. 二者之间的转化正确
     2. 输出的`x,y <= 0.8`
     3. 输出的`z <= 0.7`

## 节点功能测试

1. `/robot2077/robot_move/vel`主题：

   * 数据要求

     数据格式为上述`Twist.msg`格式

     1. `linear.z` = 0
     2. `angular.x = 0, angular.y =0`

2. `move_base_simple/goal`主题：

   * 数据要求

     |          字段          |           |           含义           |
     | :--------------------: | :-------: | :----------------------: |
     |     Point position     | float64 x |         目标坐标         |
     |                        | float64 y |                          |
     |                        | float64 z |                          |
     | Quaternion orientation | float64 x | 机器人到达目标位置的姿态 |
     |                        | float64 y |                          |
     |                        | float64 z |                          |
     |                        | float64 w |                          |

     1. `0 < position.x < width`
     2. `0 < position.y < height`
     3. `position.z = 0`

## 模块功能测试

该部分主要通过用户运行导航模块操作测试：

要测试：

* 导航的地图是否可以正常加载
* 导航的目的点是否可以正常设置
* 导航的路径是否可以正确规划
* 导航过程中是否可以主动避障并重新规划路径