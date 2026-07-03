// ASHEN 远行者 - 游戏模式骨架
// 作者: E5 框架工具程序 (WorkBuddy)
// 说明: DEMO 游戏模式，指定默认 Pawn / Controller。手感与战斗后续由 E3/E4 填充。

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AshenGameMode.generated.h"

/**
 * ASHEN DEMO 游戏模式
 * 负责: 指定玩家角色类、玩家控制器类。
 */
UCLASS()
class VALIDATEPROJECT_API AAshenGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAshenGameMode();
};
