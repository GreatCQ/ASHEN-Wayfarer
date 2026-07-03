// ASHEN 远行者 - 玩家控制器骨架实现
// 作者: E5 框架工具程序 (WorkBuddy)

#include "Core/AshenPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "UObject/ConstructorHelpers.h"

AAshenPlayerController::AAshenPlayerController()
{
	// 自动按固定路径加载 IMC_Ashen（你只需在 Content/Input/ 下建同名资产即可，无需建蓝图/手动赋值）
	// 找不到时为 null，不会崩溃；BeginPlay 里会判空。
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>
		IMCFinder(TEXT("/Game/Input/IMC_Ashen.IMC_Ashen"));
	if (IMCFinder.Succeeded())
	{
		DefaultMappingContext = IMCFinder.Object;
	}
}

void AAshenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 把默认输入映射上下文加入本地玩家的增强输入子系统
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, MappingPriority);
		}
	}
}
