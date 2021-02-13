# 背景
小W加入到一个游戏团队，它们要开发一款装修房屋的游戏，需要你来设计房子类

# stage1
经过讨论，你得到如下需求:
1. 一个房屋有门、墙、窗户、房间

# analyse
由于房子是多样化的，但是组成房子的部件基本不变，因此可以将以上提到的全部写为基类

# solution1
创建House、Door、Wall、Windows、Room基类
具体见stage1.h

# stage2
由于房子构建比较复杂，导致房子类显得比较恶心，于是需要你将房子的构造独立出去

# solution2
这个时候就可以使用builder模式，将表示和构建分离
具体见stage2.h、builder.h