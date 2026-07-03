// ASHEN 远行者 - 玩家控制器骨架实现
// 作者: E5 框架工具程序 (WorkBuddy)

#include "Core/AshenPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

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
