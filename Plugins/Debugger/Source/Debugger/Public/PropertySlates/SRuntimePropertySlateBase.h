#pragma once

class SRuntimePropertySlateBase : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRuntimePropertySlateBase)
		{
		}

	SLATE_END_ARGS()

	virtual void SetProperty(FProperty* InProperty, UObject* InObject)
	{
		Property = InProperty;
		Object = InObject;
	}

	FProperty* Property = nullptr;
	TWeakObjectPtr<UObject> Object;
};

template <typename T>
class TSRuntimePropertySlateBase : public SRuntimePropertySlateBase
{
public:
	DECLARE_DELEGATE_OneParam(FOnPropertySet, T);

	SLATE_BEGIN_ARGS(SRuntimePropertySlateBase)
		{
		}

		SLATE_ATTRIBUTE(T, Get)
		SLATE_EVENT(FOnPropertySet, Set)
	SLATE_END_ARGS()

	void SetValue(const T& InValue);
	T GetValue() const;

	TAttribute<T> Get;
	FOnPropertySet Set;

	virtual void Construct(const FArguments& InArgs);
};

template <typename T>
void TSRuntimePropertySlateBase<T>::SetValue(const T& InValue)
{
	if (Set.IsBound())
	{
		Set.Execute(InValue);
	}
}

template <typename T>
T TSRuntimePropertySlateBase<T>::GetValue() const
{
	return Get.Get();
}

template <typename T>
void TSRuntimePropertySlateBase<T>::Construct(const FArguments& InArgs)
{
	Get = InArgs._Get;
	Set = InArgs._Set;
}
