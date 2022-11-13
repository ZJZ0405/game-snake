# 贪吃蛇小程序
## 前言
为什么要写这个呢，当然是视觉组的作业了
~~编不下去了~~
## 版权说明
本工程采用GPL3.0开源协议，如有转载，请遵守相关协议。具体内容详见LICENSE文件。
## 依赖
### 外部库
[OpenCV](https://opencv.org/) 4.6.0
### 测试环境
1. Cmake
2. ArchLinux x86_64
## 思路
### 底层数据
#### 蛇
建立一个二维坐标系，用Vector制作简单的队列以储存关键坐标，读取键盘输入来更改蛇的方向。如果蛇身未超过最大长度，则将蛇头位置分别存入两个储存x,y的队列;若蛇身达到最大长度，则蛇头入队，蛇尾出队。
#### 边界
单独使用Vector存储边界坐标用于绘图。
p.s. 挺傻的方法，但先用着。
#### 奖励机制
同样采用Vector队列存储，目前以颜色区分不同奖励。
### 前端思路
建立一个二维坐标系作为动系，以底层数据坐标系为静系作伽利略变换，以提高拓展性
### 图像
目前采用OpenCV进行输出，各实体采用circle函数画圆区分，后面会引入贴图等。
背景暂时为纯黑色
#### OOP
贪吃蛇为游戏的一个子类，便于以后加入其他游戏板块
~~强行解释OOP~~

## 游戏方法
1. 在贪吃蛇界面中，按`o`强制退出
2. 测试模式请使用命令行打开
