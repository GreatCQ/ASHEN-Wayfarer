// ASHEN 远行者 - 游戏模式骨架实现
// 作者: E5 框架工具程序 (WorkBuddy)

#include "Core/AshenGameMode.h"
#include "Core/AshenPlayerController.h"
#include "Character/AshenCharacter.h"

AAshenGameMode::AAshenGameMode()
{
	// 默认玩家控制器（增强输入在此挂载）
	PlayerControllerClass = AAshenPlayerController::StaticClass();

	// 默认玩家角色（横版主角骨架，手感由 E3 填充）
	DefaultPawnClass = AAshenCharacter::StaticClass();
}
