# ShooterGameWithImGui

## 项目开发工具

Unreal Engine 4.27

JetBrains Rider 2023.2

## 项目简介

本项目在虚幻引擎官方示例项目ShooterGame基础上，加入ImGui 插件模块，利用ImGui模块制作ShooterGame的GM面板。

在单机和联网模式下GM面板都可以做到显示相关游戏数据以及响应修改，实现RunTime对游戏进行调试。

## 项目内容

一、**单机模式下实时显示游戏数据、修改游戏数据**

1、对每个AI或者player显示一个独立窗体，可以选择调试展开进行修改。
![image-20231108001346772](https://github.com/Z020912DY/shootergameWithImGui/assets/111844590/13b86454-2fab-4faa-a202-3816065de9e1)
2、面板中显示角色最大生命值、当前武器名称、最大子弹数等属性，可以对当前生命值、瞄准时最大速度、跑动最大速度、低生命值比例等状态属性修改，也可以对当前武器的当前装载子弹数目、总共拥有的子弹、弹夹子弹数量上限、攻击间隔时间、子弹散射、武器伤害等属性进行修改。
![image-20231108002619889](https://github.com/Z020912DY/shootergameWithImGui/assets/111844590/c2ee0e2f-4c89-416f-b003-4a200349def7)

在武器切换时，会动态切换属性面板，同时针对不同类型武器有不同的属性面板
![image-20231108002826762](https://github.com/Z020912DY/shootergameWithImGui/assets/111844590/b175b2d1-4407-4238-9b4e-495b779bd0be)

旁边的小面板名称有server的表示当前面板在服务器中显示，展示的是服务器端数据，带client的表示当前面板是客户端中显示，展示的是客户端数据。

二、**联网模式(Dedicated Server)下，区分客户端/服务器端数据，并实现修改**

1、设置联网模式

![image-20231108003441331](https://github.com/Z020912DY/shootergameWithImGui/assets/111844590/cec97763-0da0-4bb3-8231-eee34ccb2eef)

设置选择启动单独服务器，启动多线程，选择两个玩家，模拟出客户端和服务端。

2、修改服务端数据
![image-20231108004026282](https://github.com/Z020912DY/shootergameWithImGui/assets/111844590/1f21cb8d-a05e-4a09-9be9-b7b7217db8ba)

服务端拥有权限，所以在服务端修改数据属性之后通过网络同步，会让所有客户端的指定角色得到复制。

3、修改客户端数据

![image-20231108004249309](https://github.com/Z020912DY/shootergameWithImGui/assets/111844590/c3fa6299-e2e7-44bc-841f-10a0b251879b)

**客户端如果进行本地的单纯的修改，将不会生效**，因为客户端上的数据是从服务器上复制过来的。所以要实现客户端数据修改到服务器上，这里**采取的方法是在修改数据之后发出在服务器上运行的rpc，将本地数据传到服务器上进行修改**，实现了从客户端这里同步。

但是**客户端是无法修改simulator role的actor的**，修改这类actor的请求会被丢弃。只能修改本地控制的actor。而服务器端可以修改任何角色，因为所有角色都是在服务器端生成的，它拥有权限。

三、其他
![image](https://github.com/Z020912DY/shootergameWithImGui/blob/master/4bf0d9e4-9b7f-4c78-91a4-3c4007b6d50a.gif)

对于其他数据，如PlayerState，可以进行同类似的处理，加入GM面板中，实现RunTime对游戏进行调试。(gif图的闪烁是录制导致的，本地并没有闪烁)

## ImGui插件的引入与使用

Unreal Dear Imgui插件地址https://github.com/segross/UnrealImGui

插件的安装和编译参考插件项目的文档。

**注意事项**：

1、Imgui集成时候发生deprecated错误

解决：在ImGui.uplugin文件下将Type 属性的值改成 DeveloperTool

2、ImGui Text函数的使用

使用这个函数时要注意它用的是const char*类型，而UE常用的字符串是FString或者const TChar类型，要做一些转换。

类似如下：

`FString NameSafe = GetNameSafe(this);
WindowId = TCHAR_TO_ANSI(*NameSafe);`

