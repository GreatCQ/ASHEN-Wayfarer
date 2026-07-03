// ASHEN 远行者 - 主角角色基类骨架
// 作者: E5 框架工具程序 (WorkBuddy)
// 说明: 只搭骨架，不实现手感。
//   - E3 角色控制程序: 在此实现 移动/跳跃/闪避 手感（增强输入回调）
//   - E4 战斗系统程序: 在此接入 普攻连段/神影切换/命中判定
// 横版约束: 角色沿 X-Z 平面移动（Y 轴锁定），2.5D 横版。

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/AshenTypes.h"
#include "AshenCharacter.generated.h"

UCLASS()
class VALIDATEPROJECT_API AAshenCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAshenCharacter();

protected:
	virtual void BeginPlay() override;

	// 当前装备的神影（DEMO: None → 战胜索尔后变 Thor）
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "神影（GodShadow）")
	EAshenGodShadow CurrentGodShadow = EAshenGodShadow::None;

	// ── 横版约束参数（E3 可调） ──────────────────
	// 是否把移动锁定到 X-Z 平面（横版）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "横版（SideScroll）")
	bool bLockToSideScrollPlane = true;

public:
	// 供 E4 调用: 切换神影（DEMO 战胜索尔后调用一次）
	UFUNCTION(BlueprintCallable, Category = "神影（GodShadow）")
	void SetGodShadow(EAshenGodShadow NewShadow);

	// 读取当前神影
	UFUNCTION(BlueprintCallable, Category = "神影（GodShadow）")
	EAshenGodShadow GetGodShadow() const { return CurrentGodShadow; }
};
