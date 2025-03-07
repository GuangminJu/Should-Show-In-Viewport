// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "RuntimeDebuggerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

USTRUCT(Blueprintable)
struct FMyStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	FVector MyLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	FRotator MyRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	int32 MyInt;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	FString MyString;
};

UCLASS()
class UMyClass : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	int32 MyInt;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	FMyStruct MyStruct;
};

UCLASS(config=Game)
class ARuntimeDebuggerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	FVector MyLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	bool MyBool;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	FRotator MyRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	TArray<int32> MyIntArray{1, 2, 3, 4, 5};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
	meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	TArray<FVector> MyVectorArray{ FVector(1, 2, 3), FVector(4, 5, 6) };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	int32 MyInt;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	FString MyString;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	float MyFloat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	FMyStruct MyStruct;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	TArray<FMyStruct> MyStructArray{FMyStruct(), FMyStruct()};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	UMyClass* MyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera,
		meta = (AllowPrivateAccess = "true", ShouldShowInViewport = true, Debugger))
	TArray<UMyClass*> MyClassArray;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true", Debugger))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true", Debugger))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	ARuntimeDebuggerCharacter();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
