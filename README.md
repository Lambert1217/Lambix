# Lambix
这个项目用于学习制作游戏引擎
- 现用于本科毕业设计，实现引擎的渲染部分
- 现阶段先使用OpenGL实现，保留拓展Vulkan的可能

## 构建步骤

### 前置要求
- 已安装 [vcpkg](https://vcpkg.io/) 包管理器
- CMake 3.20+
- Visual Studio 2022 构建工具

### 配置预设
1. 创建用户预设文件 `CMakeUserPresets.json`（基于现有预设）

#### 注意事项
将路径替换为实际安装路径：
   - `[你的CMake路径]` → 指向CMake可执行文件路径
   - `[你的vcpkg根目录]` → 指向vcpkg安装根目录

### 构建命令
```bash
# 配置项目（使用继承的用户预设）
cmake --preset=vs2022_x86_64

# 构建项目（Release模式）
cmake --build --preset=vs2022_x86_64-release
```

#### 注意事项
到可执行文件所在目录再执行程序（out/build/vs2022_x86_64/Editor/Release）

## 截图
- Lambert光照
![alt text](<ScreenShot/屏幕截图 2025-03-24 191202.png>)
