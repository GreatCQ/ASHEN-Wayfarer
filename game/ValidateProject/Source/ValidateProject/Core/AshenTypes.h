// ASHEN 远行者 - 全局类型定义
// 作者: E5 框架工具程序 (WorkBuddy) | 供 E1/E3/E4 共享
// 说明: DEMO 阶段用的枚举与结构，集中定义，避免各模块重复。

#pragma once

#include "CoreMinimal.h"
#include "AshenTypes.generated.h"

/**
 * 神影类型（技能线 · 来自战胜神）
 * DEMO 只实现 Thor（索尔雷神影）。
 * 服务支柱 P3：神影是可视化战斗形态，切换改变攻击模组。
 */
UENUM(BlueprintType)
enum class EAshenGodShadow : uint8
{
	None    UMETA(DisplayName = "无（None）"),
	Thor    UMETA(DisplayName = "索尔·雷神影（Thor）"),
	// 后续: Freyja / Heimdall / Hel ...
};

/**
 * 异兽 Boss 可破坏部位（装备线 · 怪猎式狩猎）
 * 头/身/手三部位独立血量，分部位掉落不同素材。
 * 服务支柱 P4：异兽产素材、不产神影。
 */
UENUM(BlueprintType)
enum class EAshenBeastPart : uint8
{
	Head    UMETA(DisplayName = "头（Head）"),
	Body    UMETA(DisplayName = "身（Body）"),
	Arm     UMETA(DisplayName = "手（Arm）"),
};

/**
 * 攻击帧阶段（ARC 帧级标准）
 * 每个攻击招式明确 起手/判定/收招 三段。
 */
UENUM(BlueprintType)
enum class EAshenAttackPhase : uint8
{
	Startup   UMETA(DisplayName = "起手帧（Startup）"),
	Active    UMETA(DisplayName = "判定帧（Active）"),
	Recovery  UMETA(DisplayName = "收招帧（Recovery）"),
};

/**
 * 一个攻击招式的帧数据（供 E4 战斗系统填 DataTable）
 */
USTRUCT(BlueprintType)
struct FAshenAttackFrameData
{
	GENERATED_BODY()

	// 起手帧数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "帧数据")
	int32 StartupFrames = 6;

	// 判定帧数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "帧数据")
	int32 ActiveFrames = 3;

	// 收招帧数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "帧数据")
	int32 RecoveryFrames = 12;

	// 基础伤害
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "帧数据")
	float BaseDamage = 10.f;
};
