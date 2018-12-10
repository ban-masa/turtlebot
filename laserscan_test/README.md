- /scan topicをsubscribeするテスト
  - scan_sample.cpp: サンプルコード。range_maxを取得して表示するだけ。
  - scan_visualizer.cpp: 可視化用コード。
  ```
  roslaunch laserscan_test scan_visualize.launch
  ```
  で見えるはず。
- build方法
  ```
  source ~/catkin_ws/devel/setup.bash
  cd ~/catkin_ws/src/turtlebot/laserscan_test
  catkin bt
  ```
