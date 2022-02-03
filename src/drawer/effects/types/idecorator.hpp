#pragma once

#include <memory>

namespace drawer::effects::types
{

/**
 * @brief Базовый интерфейс описания декоратора
 * @details См. https://refactoring.guru/ru/design-patterns/decorator
 * @tparam T Тип декорируемого класса, T должен обладать возможностью наследования (в том числе виртуальный деструктор)
 */
	template< typename T, typename TPointer = std::shared_ptr< T > >
	class IDecorator : public T
	{
	public:
		using PointerType = TPointer;
		using Type = IDecorator< T, PointerType >;

		~IDecorator() override = default;

		/**
		 * @brief Установить указатель на декорируемый класс
		 * @details По возможности используйте метод Apply() как наиболее универсальный
		 * @param base Указатель на декорируемый класс
		 */
		void SetBase( PointerType const& base ) noexcept
		{
			mBase = base;
		}

		void SetBase( PointerType&& base ) noexcept
		{
			mBase = std::move( base );
		}

		/**
		 * @brief Установить указатель на декорируемый класс (цепочка обязанностей)
		 * @details См. https://refactoring.guru/ru/design-patterns/chain-of-responsibility/cpp/example
		 * @details Цепь вызовов: декоратор1 -> декоратор2 -> базовый класс
		 * @param base_or_decorator Указатель на декорируемый класс или целевой декоратор
		 */
		Type& Apply( PointerType const& base_or_decorator ) noexcept
		{
			if( base_or_decorator )
			{
				GetApplyResult().SetBase( base_or_decorator );
			}

			return GetApplyResult();
		}

		Type& Apply( PointerType&& base_or_decorator ) noexcept
		{
			if( base_or_decorator )
			{
				GetApplyResult().SetBase( std::move( base_or_decorator ) );
			}

			return GetApplyResult();
		}

	private:
		Type& GetApplyResult() noexcept
		{
			auto as_decorator = dynamic_cast< Type* >( mBase.get() );
			if( as_decorator )
			{
				return as_decorator->GetApplyResult();
			}

			return *this;
		}

	protected:
		PointerType mBase{};
	};

	template< typename T, typename TDeleter >
	class IDecorator< T, std::unique_ptr< T, TDeleter > > : public T
	{
	public:
		using PointerType = std::unique_ptr< T, TDeleter >;
		using Type = IDecorator< T, PointerType >;

		~IDecorator() override = default;

		void SetBase( PointerType&& base ) noexcept
		{
			mBase = std::move( base );
		}

		Type& Apply( PointerType&& base_or_decorator ) noexcept
		{
			if( base_or_decorator )
			{
				GetApplyResult().SetBase( std::move( base_or_decorator ) );
			}

			return GetApplyResult();
		}

	private:
		Type& GetApplyResult() noexcept
		{
			auto as_decorator = dynamic_cast< Type* >( mBase.get() );
			if( as_decorator )
			{
				return as_decorator->GetApplyResult();
			}

			return *this;
		}

	protected:
		PointerType mBase{};
	};

} // namespace sbis::devices::generic::types
