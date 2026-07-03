// ASHEN 远行者 - 主角角色基类骨架实现
// 作者: E5 框架工具程序 (WorkBuddy)

#include "Character/AshenCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AAshenCharacter::AAshenCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 横版约束: 锁定到 X-Z 平面（角色朝向沿 X 轴左右）
	if (UCharacterMovementComponent* Move = GetCharacterMovement())
	{
		if (bLockToSideScrollPlane)
		{
			Move->bConstrainToPlane = true;
			Move->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f)); // 锁 Y 轴
		}
		// 横版手感基础值（E3 后续精调）
		Move->bOrientRotationToMovement = false;
		Move->RotationRate = FRotator(0.f, 720.f, 0.f);
	}
}

void AAshenCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAshenCharacter::SetGodShadow(EAshenGodShadow NewShadow)
{
	// TODO(E4): 切换神影时改变攻击模组 + 触发可视化形态（P3）
	CurrentGodShadow = NewShadow;
}
