## 目标检测模块单元测试文档

### API测试

1、检测到的物体矩形框绘制函数`DrawBox`测试：

- 函数功能：根据传入的坐标和颜色绘制出`visualization_msgs::Marker`矩形框。

- 输入：

    |  字段  | 类型  |     含义      |
    | :----: | :---: | :-----------: |
    | inMinx | float | X轴矩形框起点 |
    | inMaxX | float | X轴矩形框终点 |
    | inMinY | float | Y轴矩形框起点 |
    | inMaxY | float | Y轴矩形框终点 |
    | inMinZ | float | Z轴矩形框起点 |
    | inMaxZ | float | Z轴矩形框终点 |
    |  inR   | float | 红色颜色分量  |
    |  inG   | float | 绿色颜色分量  |
    |  inB   | float | 蓝色颜色分量  |

- 输出：函数无输出，但会发布`robot2077/obj_detect/obj_mark`主题，该主题的信息为`visulization_msgs/Marker.msg`类型：

    |     字段     |         类型          |      含义      |
    | :----------: | :-------------------: | :------------: |
    |    header    |        Header         |    头部信息    |
    |      ns      |        string         |     名字域     |
    |      id      |         int32         |  名字域内的id  |
    |     type     |         int32         | 标示物体的类型 |
    |    action    |         int32         |  对物体的操作  |
    |     pose     |  geometry_msgs/Pose   |   物体的姿态   |
    |    scale     | geometry_msgs/Vector3 |   物体的尺度   |
    |    color     |  std_msgs/ColorRGBA   |                |
    |   lifetime   |       duration        |    持续时间    |
    | frame_locked |         bool          |    是否锁定    |
    |    points    | geometry_msgs/Point[] |    点云信息    |
    |    colors    | std_msgs/ColorRGBA[]  |    颜色信息    |

- 要求：

    - 对于正确的输入，能够发布出正确的矩形框，并能在Rviz中可视化。

2、跟矩形框配套的文字描述绘制函数`DrawText`测试：

- 函数功能：根据传入的坐标和颜色添加出`visualization_msgs::Marker`文字描述。

- 输入：

    |  字段   |    类型     |         含义          |
    | :-----: | :---------: | :-------------------: |
    | inText  | std::string |    展示的文字内容     |
    |   inX   |    float    |        X轴坐标        |
    |   inY   |    float    |        Y轴坐标        |
    |   inZ   |    float    |        Z轴坐标        |
    |   inR   |    float    |     红色颜色分量      |
    |   inG   |    float    |     绿色颜色分量      |
    |   inB   |    float    |     蓝色颜色分量      |
    | inScale |    float    | 在Z轴上的文字放缩比例 |

- 输出：函数无输出，但会发布`robot2077/obj_detect/obj_mark`主题，该主题的信息为`visulization_msgs/Marker.msg`类型，该类型信息上面已给出。

- 要求：

    - 文字能够正确显示，且应该显示在对应矩形框的正上方。

3、辅助信息清除函数`RemoveBoxes`测试：

- 输入：无
- 输出：函数无输出，但会发布两条信息在`robot2077/obj_detect/obj_mark`主题上，该主题的信息为`visulization_msgs/Marker.msg`类型，该类型信息上面已给出。两条信息分别是删除矩形框和删除文字描述的。
- 要求：
    - 能够将Rviz上显示出的矩形框和文字描述全部清空。

4、通过订阅的点云识别平面和物体的函数`pc2_callback`测试：

- 输入：`sensor_msgs/PointCloud2.msg`信息

    |     字段     |     类型     |             含义             |
    | :----------: | :----------: | :--------------------------: |
    |    header    |    Header    |           头部信息           |
    |    height    |    uint32    |         点云的总长度         |
    |    width     |    uint32    |         点云的总宽度         |
    |    fields    | PointField[] | 描述点云的通道数和它们的结构 |
    | is_bigendian |     bool     |          是否为大端          |
    |  point_step  |    uint32    |      一个点占据多少字节      |
    |   row_step   |    uint32    |       一行占据多少字节       |
    |     data     |   uint8[]    |           点云数据           |
    |   is_dense   |     bool     |         是否有非法点         |

- 输出：函数无输出，但是会通过上述的三个函数发布相关信息。

- 要求：

    - 对于输入的原始点云信息，能够正确变换到`/base_footprint`坐标轴下；
    - 在剩余点云不足总点云的30%时自动跳出；
    - 要求只能检测高度在0.6米-1.5米之间的平面，若未找到一个以上的平面，则自动跳出；
    - 检测到物体后，能够通过调用上述三个函数给物体正确编号，并在Rviz中实现可视化。

### 节点功能测试

1、`/robot2077/obj_detect/obj_pc`主题：

- 数据要求：格式为`sensor_msgs/PointCloud2.msg`信息；

2、`/robot2077/obj_detect/obj_mark`主题：

- 数据要求：格式为`sensor_msgs/PointCloud2.msg`信息；

3、`/robot2077/obj_detect/segment_objs`主题：

- 数据要求：格式为`sensor_msgs/PointCloud2.msg`信息；

4、`/robot2077/obj_detect/segment_planes`主题：

- 数据要求：格式为`sensor_msgs/PointCloud2.msg`信息；

### 模块功能测试

该部分主要通过运行目标检测模块，主动控制模块和UI模块测试：

- 平面是否可以正确检测；
- 平面上的物体是否可以正确检测；
- 检测到物体后矩形框和文字描述的标注是否正确；

