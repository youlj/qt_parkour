# qt_parkour

Qt跑酷游戏,支持基本按键操作,还可进行攻击

我的环境:win10+qt5.14.2(mingw64)

### 核心思路
通过开启一个定时器,然后在定时器里面对角色进行操作,之后角色的相关坐标会改变,其他障碍物也一样,然后刷新绘图事件,造成角色和障碍物在移动的假象,但是,这种方式缺点也很明显,仔细观察的话,会发现画面有闪烁的现象(只是轻微的闪烁,不留意的话察觉不到)

![scene1](https://user-images.githubusercontent.com/57586196/168960198-9ddec527-976d-4ad0-a45b-ebbc22d0b6ca.png)

![scene2](https://user-images.githubusercontent.com/57586196/168960212-6740649e-48e6-46f1-a8db-d2206e06c1c9.png)
