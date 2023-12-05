# Rebirth

Developed with Unreal Engine 4

UE4 DEMO 
演示版本：0.01/学习版/待重构版
策划案：《Rebirth》

首先非常感谢朋友CM无偿提供的策划案来供本人进行UE4的学习
《Rebirth》这个策划案首先本身已经设计地非常完整，主要包含7个场景14个关卡，故事设定也完整且非常厉害，但我毕竟只是个还在找实习/正职的游戏客户端程序人，没有充分的资源，所以只实现了极小一部分游戏与需求内容，以后有机会的话还是希望能完成此策划案吧。

此代码版本为最早的版本，很多实现的代码写地不够设计模式，所以比起继续完成关卡设计，下一步会先进行项目整体的重构。

此项目构建的过程中，官方示例《ActionRPG》是本人学习与参考的核心项目。

此版本基本没有注释，原因是在之前已经进行过重构的代码中使用了不少中文注释，导致反射出现严重问题，所以把注释全删了，对于暂时没有注释我感到十分抱歉，下一个重构版本会尽快加上便于理解的英文注释，同时下一个版本也会附上详细的代码文档。

此版本实现的功能如下，代码仅供参考，欢迎各位读者提出宝贵的意见：

视角自定义(俯视角Pitch) - TopSideView
ARPG系统(基于GAS) - Ability Character
角色受击、死亡、复生逻辑 - Character
复活待机画面
物件交互 - Interaction
摄像机动画
休息点(生命值恢复)
无缝(流送关卡)
存档系统
对话系统
攻击Combo
遮挡角色的模型自动淡化(纹理抖动为时间线性，此处的实际效果一般，感兴趣可自行实验) - TopSideView
锁定敌人
演出系统-Act
蓝图资产与C++单例实现

