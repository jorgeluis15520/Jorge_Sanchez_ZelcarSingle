#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
    ECS_Unoccupied UMETA(DisplayName = "Unoccupied"),
    ECS_Occupied UMETA(DisplayName = "Occupied"),
};