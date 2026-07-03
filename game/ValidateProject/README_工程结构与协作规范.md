# ASHEN 远行者 · 工程结构与协作规范（E5 框架工具程序 维护）

> 本文件由 E5 框架工���程序维护，是全体程序专家的工程约定。

## 一、Source 目录结构

```
Source/ValidateProject/
├── ValidateProject.cpp/.h        模块入口（勿动）
├── Core/                         框架层（E5 维护）
│   ├── AshenTypes.h              全局枚举/结构（神影/部位/帧数据）
│   ├── AshenGameMode.cpp/.h      游戏模式：指定 Pawn/Controller
│   └── AshenPlayerController.*   玩家控制器：增强输入 IMC 挂载
├── Character/                    角色层（E3 手感 / E4 战斗接入）
│   └── AshenCharacter.cpp/.h     主角基类骨架（横版约束 + 神影槽）
├── Combat/                       战斗层（E4 后续新建）
└── Level/                        关卡逻辑层（E1/E3 后续新建）
```

## 二、命名规范
- 类名统一前缀 `Ashen`（如 `AAshenCharacter`）。
- 模块 API 宏用 `VALIDATEPROJECT_API`（工程名暂沿用 ValidateProject）。
- 枚举 `EAshenXxx`，结构 `FAshenXxx`。
- 编辑器可见属性用中文（English）双语 Category，方便制作人中文界面识别。

## 三、分工接口约定（谁往哪写）
| 专家 | 负责文件 | 说明 |
|------|---------|------|
| E5 框架 | `Core/*` | 地基、类型、输入宿主，勿被他人改 |
| E3 角色控制 | `Character/AshenCharacter` | 实现移动/跳跃/闪避手感（增强输入回调） |
| E4 战斗系统 | `Combat/*` + `AshenCharacter` 战斗部分 | 连段/神影/多部位HitBox/BossAI |
| E1 关卡 | `Level/*` + DataTable | 关卡逻辑、数值表 |

## 四、增强输入（Enhanced Input）待建资产（编辑器内，E3 建）
在 UE5 编辑器里创建（内容浏览器 Content Browser）：
- `IMC_Ashen`（Input Mapping Context）
- `IA_Move` / `IA_Jump` / `IA_Dodge`（E3）
- `IA_Attack` / `IA_SwitchGodShadow` / `IA_Interact`（E4）
建好后把 `IMC_Ashen` 赋给 `AshenPlayerController.DefaultMappingContext`。

## 五、Git 协作铁律
- 编译产物 **绝不提交**：Binaries / Intermediate / Saved / DerivedDataCache（已由 .gitignore 排除）
- 大资产（.uasset/.umap/.fbx/.png）走 **Git LFS**
- 提交信息格式：`feat/fix/docs(模块): 简述`，如 `feat(Character): 实现闪避无敌帧`
- 分支：DEMO 期主干 `main` 直推；复杂功能可开 `feature/xxx` 分支
- 云端(WorkBuddy)写代码 → push → 本地 pull → VS2022 编译 → UE5 验证

## 六、编译验证（制作人本地）
1. `git pull` 拉取最新
2. 右键 `.uproject` → Generate Visual Studio project files（若新增了 .cpp/.h）
3. VS2022 选 `Development Editor` / `Win64` → 生成 ValidateProject
4. 打开 UE5 验证
