// ASHEN 远行者 - 玩家控制器骨架（增强输入宿主）
// 作者: E5 框架工具程序 (WorkBuddy)
// 说明: 提供增强输入 IMC 挂载点。具体 InputAction 绑定逻辑由 E3(移动/闪避) 与 E4(攻击/神影) 实现。

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AshenPlayerController.generated.h"

class UInputMappingContext;

/**
 * ASHEN DEMO 玩家控制器
 * 负责: 在 BeginPlay 时把默认 InputMappingContext 加入增强输入子系统。
 */
UCLASS()
class VALIDATEPROJECT_API AAshenPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// 构造函数: 自动按固定路径加载 IMC_Ashen，免去建 PlayerController 蓝图
	AAshenPlayerController();

	// DEMO 默认输入映射上下文（构造函数自动加载 /Game/Input/IMC_Ashen；也可在编辑器覆盖）
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "输入（Input）")
	TObjectPtr<UInputMappingContext> DefaultMappingContext = nullptr;

	// 映射优先级
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "输入（Input）")
	int32 MappingPriority = 0;

protected:
	virtual void BeginPlay() override;
};
