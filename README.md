# Runaway 🎮

一个使用 C++17 和 OpenGL 开发的2D横版跑酷射击游戏，是CS100课程的大作业项目。

## 📖 游戏背景

很久以前，曾经祥和的艾弗林小镇被一股神秘的哥布林潮席卷而过。你是一名年轻的发明家，偶然发现了一个古老的机械装置，隐藏着能够操控哥布林的力量。这一发现使得你成为了哥布林首领的头号目标。你只能携带着装置，在森林中逃亡，寻找方法解开装置的秘密，并用它反击哥布林的侵略。

## 🎯 游戏特性

- **横版跑酷**：玩家在不断滚动的背景中奔跑
- **射击系统**：使用枪械攻击追来的哥布林
- **跳跃机制**：通过跳跃规避敌人攻击和斧头
- **敌人AI**：哥布林会追踪玩家并投掷斧头攻击
- **计分系统**：击杀哥布林获得分数

## 🎮 操作说明

| 按键 | 功能 |
|------|------|
| `K` / `Space` | 跳跃 |
| `J` / 鼠标左键 | 射击 |

## 🛠️ 编译环境

### 依赖项

- **CMake** >= 3.16
- **C++17** 兼容编译器
  - Windows: MinGW-w64 或 Visual Studio 2019+
  - macOS: Xcode Command Line Tools 或 Clang
  - Linux: GCC 9+

### 第三方库（已包含）

- [FreeGLUT](third_party/freeglut/) - OpenGL实用工具库
- [SOIL](third_party/SOIL/) - Simple OpenGL Image Library

## 🚀 编译与运行

### Windows (MinGW-w64)

```cmd
# 创建并进入build目录
mkdir build && cd build

# 配置CMake
cmake -G "MinGW Makefiles" -DCMAKE_POLICY_VERSION_MINIMUM=3.5 ..

# 编译
mingw32-make -j4

# 运行（从项目根目录）
cd ..
build\bin\Runaway.exe
```

### Windows (Visual Studio)

```cmd
# 创建并进入build目录
mkdir build && cd build

# 配置CMake
cmake ..

# 编译
cmake --build . --config Release

# 运行
.\bin\Release\Runaway.exe
```

### macOS / Linux

```bash
# 创建并进入build目录
mkdir build && cd build

# 配置并编译
cmake .. && make -j

# 运行
./bin/Runaway
```

## 📁 项目结构

```
Runaway/
├── assets/                 # 游戏素材（图片资源）
├── include/runaway/        # 头文件
│   ├── Framework/          # 游戏框架核心
│   ├── GameObject/         # 游戏对象定义
│   └── GameWorld/          # 游戏世界管理
├── src/                    # 源代码
│   ├── Framework/          # 框架实现
│   ├── GameObject/         # 游戏对象实现
│   │   ├── Background.cpp  # 背景滚动
│   │   ├── Player.cpp      # 玩家控制
│   │   ├── Enemies.cpp     # 敌人AI
│   │   └── Projectiles.cpp # 子弹和斧头
│   └── GameWorld/          # 游戏世界逻辑
├── third_party/            # 第三方库
│   ├── freeglut/          # FreeGLUT库
│   └── SOIL/              # 图像加载库
├── CMakeLists.txt         # CMake配置
└── README.md              # 本文件
```

## 🏗️ 架构设计

### 核心类

- **`GameWorld`**: 游戏世界管理器，负责对象生命周期、碰撞检测、游戏状态
- **`GameObject`**: 所有游戏对象的基类，定义了通用的属性和行为
- **`Player`**: 玩家角色，处理移动、跳跃、射击
- **`Goblin`**: 敌人角色，实现追踪和攻击AI
- **`Bullet`/`Axe`**: 投射物类，处理飞行和碰撞

### 设计模式

- **面向对象设计**: 使用继承和多态实现不同游戏对象的行为
- **智能指针管理**: 使用`std::shared_ptr`和`std::unique_ptr`管理对象生命周期
- **组件化架构**: 游戏对象独立更新，通过GameWorld统一调度

## 🎯 游戏机制

### 玩家属性
- **生命值**: 3 HP
- **射击冷却**: 10帧
- **跳跃初速度**: 23像素/帧
- **重力加速度**: 2像素/帧²

### 敌人属性
- **哥布林HP**: 5
- **移动速度**: 3像素/帧（向左）
- **生成间隔**: 每240帧（8秒）
- **投斧间隔**: 100帧

### 碰撞检测
使用AABB（轴对齐包围盒）进行碰撞检测，支持：
- 子弹vs哥布林
- 斧头vs玩家
- 哥布林vs玩家

## 📝 开发说明

### 代码规范

- 使用C++17标准
- 遵循面向对象设计原则
- 使用`enum class`代替魔法数字
- 成员变量使用`m_`前缀
- 智能指针代替原始指针

### 添加新内容

1. 在`utils.hpp`中定义新的`ImageID`和`AnimID`
2. 在`SpriteManager.cpp`中注册新素材
3. 创建继承自`GameObject`的新类
4. 在`GameWorld`中实现生成逻辑

## 📄 许可证

本项目仅用于学习和教育目的。

## 🙏 致谢

- 课程框架代码由CS100课程组提供
- 游戏素材来自课程资源

---

*Made with ❤️ for CS100 Homework 7*
打包上传和Readme编写由GLM-5完成，代码为纯人工编写
