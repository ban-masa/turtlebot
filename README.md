turtlebot
=========

The turtlebot stack provides all the basic drivers for running and using a [TurtleBot](http://turtlebot.com) with [ROS](http://www.ros.org).

ROS Wiki : (http://www.ros.org/wiki/Robots/TurtleBot)




![TurtleBot Logo](http://www.turtlebot.com/assets/images/turtlebot_logo.png)

#メモ

1. 必要なパッケージ
  - (ros-indigoの環境がかなり整っている状態で検証したため、defaultではインストールされていないパッケージを忘れている可能性大)
  - ` sudo aptitude install ros-indigo-turtlebot-create-desktop `

2. 実行方法
  ```
  export TURTLEBOT_BASE="kobuki"
  export TURTLEBOT_STACKS="hexagons"
  export TURTLEBOT_3D_SENSOR="hokuyo"
  source ~/catkin_ws/devel/setup.bash
  roslaunch turtlebot_gazebo turtlebot_world.launch
  ```

3. 要点
  - roslaunch turtlebot_gazebo turtlebot_world.launch でturtlebot_description/robots/<TURTLEBOT_BASE>_<TURTLEBOT_STACKS>_<TURTLEBOT_3D_SENSOR>.urdf.xacroが呼ばれる
  - センサーの交換に関係しそうな部分は以下
  - urdf/sensors/hokuyo.urdf.xacro: hokuyoの外観、物理パラメータ、親リンク（取付部）からの相対位置といった要素を設定する+urdf/turtlebot_gazebo.urdf.xacroを読み込む
  - urdf/turtlebot_gazebo.urdf.xacro: センサーの仕様、性能が定義されている。hokuyo_link以下のpropertyタグの値を変えることによりレンジや視野角の性能が変わる
  - 参考にしたページではgpu_rayおよびlibgazebo_ros_gpu_laser.soを使用していたが、うまく動かなかったのでrayとlibgazebo_ros_laserに変更

