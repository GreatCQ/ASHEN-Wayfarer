# E3 白盒角色手感 · 编辑器设置指引（制作人操作）

> 代码已写好（AshenCharacter 移动/跳跃/闪避）。但增强输入资产是 .uasset 蓝图资产，
> 必须在 UE5 编辑器里手动创建并赋值。下面是双语操作步骤。全部在 UE5 中文界面里做。

## 前置：拉取 + 编译
```powershell
git pull
# 右键 ValidateProject.uproject → Generate Visual Studio project files
# VS2022 生成(Build) → 成功后打开 UE5
```

## 第 1 步：创建增强输入资产（内容浏览器 Content Browser）
在内容浏览器空白处右键 → 输入（Input）：

1. 建 4 个 **输入操作（Input Action）**：
   - `IA_Move`：值类型（Value Type）选 **Axis1D（浮点/float）**
   - `IA_Jump`：值类型 **Digital（bool）**
   - `IA_Dodge`：值类型 **Digital（bool）**
2. 建 1 个 **输入映射上下文（Input Mapping Context）**：命名 `IMC_Ashen`

## 第 2 步：在 IMC_Ashen 里绑定按键
双击打开 `IMC_Ashen`，添加映射（Mappings）：
- **IA_Move**：
  - 加按键 `D`（或右方向键）→ 修饰符（Modifiers）无
  - 加按键 `A`（或左方向键）→ 修饰符加 **取反（Negate）**
- **IA_Jump**：加按键 `空格（Space Bar）`
- **IA_Dodge**：加按键 `左 Shift（Left Shift）`

## 第 3 步：把 IMC 赋给玩家控制器
方式 A（改蓝图）：基于 `AshenPlayerController` 建一个蓝图 `BP_AshenPlayerController`，
在其 **默认（Class Defaults）** 里把 `Default Mapping Context` 设为 `IMC_Ashen`。

方式 B（更快，直接在 C++ 类默认值设）：暂不推荐，先用蓝图方式可视化调。

## 第 4 步：把 IA 赋给角色
基于 `AshenCharacter` 建蓝图 `BP_AshenCharacter`，在其默认里：
- Move Action = `IA_Move`
- Jump Action = `IA_Jump`
- Dodge Action = `IA_Dodge`

## 第 5 步：设置 GameMode 使用这些蓝图
项目设置（Project Settings）→ 地图和模式（Maps & Modes）：
- Default GameMode = `AshenGameMode`（或基于它的蓝图）
- 若用了 BP_ 版本，在 AshenGameMode 蓝图里把 DefaultPawn/PlayerController 指向 BP 版本

## 第 6 步：搭个白盒测试关卡
1. 新建关卡（Level），放一块地板（静态网格 Cube 拉大当地面）
2. 放 PlayerStart
3. 运行（Play / Alt+P）

## ✅ 验证目标
- A/D（或方向键）左右移动，角色翻面
- 空格跳跃（手感干脆不飘）
- 左 Shift 朝当前朝向闪避冲刺（有短暂无敌帧 + 冷却）

## 手感调参（都在 BP_AshenCharacter 默认值里）
- 移动速度：CharacterMovement → Max Walk Speed（默认 600）
- 跳跃高度：Jump Z Velocity（默认 900）
- 闪避：Dodge Speed / Dodge Duration / Invincible Duration / Dodge Cooldown

> 调完手感，把你觉得舒服的数值告诉我，我写回代码默认值。
