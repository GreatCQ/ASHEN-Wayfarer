// ASHEN 远行者 - 主角角色（横版手感）
// 作者: E3 角色控制程序 (WorkBuddy) | 地基由 E5 提供
// 说明: 横版 2.5D 主角，实现 移动/跳跃/闪避 手感。战斗(连段/神影)由 E4 后续接入。
//   - 横版约束: 锁定 Y 轴，角色沿 X-Z 平面运动
//   - 闪避: 带无敌帧(i-frame) + 冷却，是战斗手感命脉
//   - 手感参数全部暴露编辑器，制作人可无代码微调

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/AshenTypes.h"
#include "AshenCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class VALIDATEPROJECT_API AAshenCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAshenCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ── 摄像机（横版侧视） ─────────────────────────
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "摄像机（Camera）")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "摄像机（Camera）")
	TObjectPtr<UCameraComponent> SideViewCamera;

	// 摄像机与角色的距离（越大画面越远，横版建议 800~1500）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "摄像机（Camera）")
	float CameraDistance = 900.f;

	// 网格体基础朝向 Yaw（角色朝右时 Mesh 的 Yaw；若美术资产默认朝向不同请改此值）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "横版（SideScroll）")
	float BaseMeshYaw = 0.f;

	// ── 输入动作（编辑器里赋 IA 资产） ──────────────
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "输入（Input）")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "输入（Input）")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "输入（Input）")
	TObjectPtr<UInputAction> DodgeAction;

	// ── 横版约束 ───────────────────────────────────
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "横版（SideScroll）")
	bool bLockToSideScrollPlane = true;

	// ── 闪避手感参数（可调） ───────────────────────
	// 闪避冲刺速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "闪避（Dodge）")
	float DodgeSpeed = 1200.f;

	// 闪避持续时间（秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "闪避（Dodge）")
	float DodgeDuration = 0.25f;

	// 无敌帧持续时间（秒，通常略短于闪避时长）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "闪避（Dodge）")
	float InvincibleDuration = 0.2f;

	// 闪避冷却（秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "闪避（Dodge）")
	float DodgeCooldown = 0.6f;

	// ── 神影（战斗线，E4 用） ──────────────────────
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "神影（GodShadow）")
	EAshenGodShadow CurrentGodShadow = EAshenGodShadow::None;

	// ── 运行时状态 ─────────────────────────────────
	// 是否处于无敌帧（供 E4 战斗判定读取）
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "闪避（Dodge）")
	bool bIsInvincible = false;

	bool bIsDodging = false;
	bool bDodgeOnCooldown = false;
	float LastFacingSign = 1.f; // 朝向: +1 右, -1 左

	// 输入回调
	void OnMove(const FInputActionValue& Value);
	void OnJump(const FInputActionValue& Value);
	void OnDodge(const FInputActionValue& Value);

	// 更新横版翻面（仅转网格体，不动摄像机）
	void UpdateFacing();

	// 闪避计时结束回调
	void EndDodge();
	void EndInvincible();
	void ResetDodgeCooldown();

	FTimerHandle DodgeTimerHandle;
	FTimerHandle InvincibleTimerHandle;
	FTimerHandle CooldownTimerHandle;

public:
	UFUNCTION(BlueprintCallable, Category = "神影（GodShadow）")
	void SetGodShadow(EAshenGodShadow NewShadow);

	UFUNCTION(BlueprintCallable, Category = "神影（GodShadow）")
	EAshenGodShadow GetGodShadow() const { return CurrentGodShadow; }

	// 供 E4 战斗系统查询是否无敌
	UFUNCTION(BlueprintCallable, Category = "闪避（Dodge）")
	bool IsInvincible() const { return bIsInvincible; }
};
