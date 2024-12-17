# 程序设计范式期末项目
——基于cocos2dx开发塔防类游戏《保卫萝卜》

# 小组成员及分工




<table>
  <tbody>
    <tr>
      <th>小组成员</th>
      <th>主要负责内容</th>
    </tr>
    <tr>
      <td>2250691&nbsp;<br>吴雨辰</td>
      <td><br>UI及触摸事件监听部分<br>开始界面（MainScene）的设计<br>选关界面（SelectScene）的设计<br>触摸事件监听层（TouchLayer）的设计<br>炮塔基座（Terrains）的设计<br>炮塔升级和拆除的实现<br>音效的插入（SoundManager）<br>保存通关进度的实现</td>
    </tr>
    <tr>
      <td>2250693&nbsp;<br>朱昱瑾</td>
      <td><br>调度器（schedule）部分<br>定时器（update）部分<br>两张地图的设计<br>怪物（Monster）的设计<br>子弹（Bullet）的设计以及攻击的实现<br>萝卜（Carrot）的设计<br>游戏管理类（GameManager）的设计<br>界面的美化</td>
    </tr>
  </tbody>
  <colgroup>
    <col>
    <col>
  </colgroup>
</table>             






# 成员贡献
<table>
  <tbody>
    <tr>
      <th>成员</th>
      <th>贡献度</th>
    </tr>
    <tr>
      <td>2250691&nbsp;<br>吴雨辰</td>
      <td>50%</td>
    </tr>
    <tr>
      <td>2250693&nbsp;<br>朱昱瑾&nbsp;&nbsp;</td>
      <td>50%</td>
    </tr>
  </tbody>
  <colgroup>
    <col>
    <col>
  </colgroup>
</table>



# 项目实现功能
## 基础功能

- [x] 支持至少3种防御塔和防御塔的删除
- [x] 每种防御塔的攻击特效
- [x] 怪物、萝卜生命值显示
- [x] 支持资源功能，资源可用于购买防御塔，资源可通过击杀怪物获得
- [x] 支持每种防御塔的升级，至少可升级2次
- [x]  支持萝卜的升级，至少可升级2次
- [x] 支持3种怪物
- [x] 支持2张地图
- [x] 支持背景音乐
- [x] 关卡选择界面和保存通关进度记录功能（未完成第一关第二关无法解锁，每关完成后记录所得成绩）






## 拓展功能

- [x] 支持攻击、建造、击杀、防御塔升级和拆除时的音效
- [x] 支持选定攻击目标
- [x] 支持特殊技能（AOE群体伤害/减速及范围伤害）
- [x] 暂停游戏功能




## 加分项
* 版本控制和团队合作
- [x] 合理使用Git 控制版本，将项目开源至GitHub
- [x] 团队成员分工合理平等

* 功能和架构
- [x] 界面精美，还原度高
- [x] 项目目录结构清晰

* 其他
- [x] 没有内存泄漏
- [x] 运行游戏时不会发生崩溃情况
- [x] 尽可能多的使用了c++11特性（如STL容器、迭代器、lambda表达式、auto、类的继承体系和多态等）
