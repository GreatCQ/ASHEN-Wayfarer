// ASHEN 远行者 - 主角角色（横版手感）实现
// 作者: E3 角色控制程序 (WorkBuddy)

#include "Character/AshenCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

AAshenCharacter::AAshenCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// ── 横版约束: 锁定到 X-Z 平面（锁 Y 轴） ──
	if (UCharacterMovementComponent* Move = GetCharacterMovement())
	{
		if (bLockToSideScrollPlane)
		{
			Move->bConstrainToPlane = true;
			Move->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f));
		}
		Move->bOrientRotationToMovement = false;
		Move->RotationRate = FRotator(0.f, 720.f, 0.f);
		// 横版基础手感（E3 建议初值，制作人可调）
		Move->MaxWalkSpeed = 600.f;
		Move->JumpZVelocity = 900.f;
		Move->AirControl = 0.8f;         // 空中操控性高一些，横版跳台手感好
		Move->GravityScale = 2.0f;       // 重力略大，跳跃干脆不飘
		Move->BrakingDecelerationWalking = 2000.f;
	}

	// 角色不随控制器旋转（横版靠翻转朝向）
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// ── 摄像机: 固定侧视横版（关键：绝对旋转，永不随角色翻面而转） ──
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = CameraDistance;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bEnableCameraLag = false;
	// 关键: 绝对旋转 —— 弹簧臂朝向锁死世界坐标, 无视角色/父级怎么转,
	// 保证角色左右翻面时视角永远从固定侧面(沿世界 -Y 看向 +Y)拍摄。
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->SetUsingAbsoluteRotation(true);
	// 沿世界 -Y 方向看向角色所在的 X-Z 平面: Yaw = -90° 使镜头看向 +Y。
	CameraBoom->SetWorldRotation(FRotator(0.f, -90.f, 0.f));

	SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCamera->bUsePawnControlRotation = false;
	// 正交投影更贴近纯 2D 横版观感（可改回 Perspective 保留景深）。
	// 默认保留透视, 制作人可在编辑器细节面板切换 ProjectionMode。

	// ── 自动加载输入动作（免去建蓝图手动赋值） ──
	// 你只需在 Content/Input/ 下建同名 IA 资产即可自动引用；找不到为 null，不崩溃。
	static ConstructorHelpers::FObjectFinder<UInputAction> MoveFinder(TEXT("/Game/Input/IA_Move.IA_Move"));
	if (MoveFinder.Succeeded()) { MoveAction = MoveFinder.Object; }

	static ConstructorHelpers::FObjectFinder<UInputAction> JumpFinder(TEXT("/Game/Input/IA_Jump.IA_Jump"));
	if (JumpFinder.Succeeded()) { JumpAction = JumpFinder.Object; }

	static ConstructorHelpers::FObjectFinder<UInputAction> DodgeFinder(TEXT("/Game/Input/IA_Dodge.IA_Dodge"));
	if (DodgeFinder.Succeeded()) { DodgeAction = DodgeFinder.Object; }
}

void AAshenCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAshenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAshenCharacter::OnMove);
		}
		if (JumpAction)
		{
			EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &AAshenCharacter::OnJump);
		}
		if (DodgeAction)
		{
			EIC->BindAction(DodgeAction, ETriggerEvent::Started, this, &AAshenCharacter::OnDodge);
		}
	}
}

void AAshenCharacter::OnMove(const FInputActionValue& Value)
{
	if (bIsDodging)
	{
		return; // 闪避中不响应普通移动
	}

	// 横版: 只取一维输入（左右）
	const float AxisValue = Value.Get<float>();
	if (FMath::IsNearlyZero(AxisValue))
	{
		return;
	}

	// 沿世界 X 轴移动
	AddMovementInput(FVector(1.f, 0.f, 0.f), AxisValue);

	// 记录朝向并翻转「网格体」面向（横版翻面）。
	// 关键: 只转 Mesh, 不转整个 Actor —— 否则会把摄像机也一起甩到背面,
	// 导致视角随移动翻转, 破坏固定横版观感。
	LastFacingSign = (AxisValue > 0.f) ? 1.f : -1.f;
	UpdateFacing();
}

void AAshenCharacter::OnJump(const FInputActionValue& /*Value*/)
{
	if (!bIsDodging)
	{
		Jump();
	}
}

void AAshenCharacter::OnDodge(const FInputActionValue& /*Value*/)
{
	if (bIsDodging || bDodgeOnCooldown)
	{
		return;
	}

	bIsDodging = true;
	bIsInvincible = true;
	bDodgeOnCooldown = true;

	// 朝当前朝向冲刺
	const FVector DodgeDir = FVector(LastFacingSign, 0.f, 0.f);
	LaunchCharacter(DodgeDir * DodgeSpeed, true, false);

	// 定时结束闪避 / 无敌 / 冷却
	GetWorldTimerManager().SetTimer(DodgeTimerHandle, this, &AAshenCharacter::EndDodge, DodgeDuration, false);
	GetWorldTimerManager().SetTimer(InvincibleTimerHandle, this, &AAshenCharacter::EndInvincible, InvincibleDuration, false);
	GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &AAshenCharacter::ResetDodgeCooldown, DodgeCooldown, false);
}

void AAshenCharacter::UpdateFacing()
{
	// 横版翻面: 仅旋转网格体, 不动 Actor/摄像机。
	// 朝右 = Mesh 面向 +X (Yaw 0), 朝左 = 面向 -X (Yaw 180)。
	// 注意基础网格默认朝向可能是 -X, 若美术资产朝向不同, 调整 BaseMeshYaw 即可。
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		const float YawFacing = (LastFacingSign > 0.f) ? BaseMeshYaw : (BaseMeshYaw + 180.f);
		MeshComp->SetWorldRotation(FRotator(0.f, YawFacing, 0.f));
	}
}

void AAshenCharacter::EndDodge()
{
	bIsDodging = false;
}

void AAshenCharacter::EndInvincible()
{
	bIsInvincible = false;
}

void AAshenCharacter::ResetDodgeCooldown()
{
	bDodgeOnCooldown = false;
}

void AAshenCharacter::SetGodShadow(EAshenGodShadow NewShadow)
{
	// TODO(E4): 切换神影时改变攻击模组 + 触发可视化形态（P3）
	CurrentGodShadow = NewShadow;
}
