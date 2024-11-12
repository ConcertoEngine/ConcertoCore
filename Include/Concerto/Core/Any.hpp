//
// Created by arthur on 16/11/2023.
//

#ifndef CONCERTO_CORE_ANY_HPP
#define CONCERTO_CORE_ANY_HPP

#include "Concerto/Core/Types.hpp"

#include <memory>

namespace cct
{
	/**
	 * @brief A class that can store any type of data.
	 * Use Any::Make to create an Any object.
	 */
	class CONCERTO_CORE_PUBLIC_API Any
	{
	 private:
		Any(std::size_t id, std::unique_ptr<void*> data);
	 public:
		Any();
		~Any();
		Any(const Any& other) = delete;
		Any(Any&& other) noexcept = default;

		Any& operator=(Any&&) = default;
		Any& operator=(const Any&) = delete;

		template<typename T, typename... Args>
		Any& operator=(Args&&... args);

		template<typename T>
		Any& operator=(const T& data);

		template<typename T>
		Any& operator=(T&& data);


		/**
		 * @brief Checks if the type of the data is the same as the template type.
		 * @tparam T The type to check.
		 * @return True if the type is the same, false otherwise.
		 */
		template<typename T>
		[[nodiscard]] bool Is() const;

		/**
		 * @brief Returns the data as the template type.
		 * @tparam T The type to return.
		 * @return The data as the template type.
		 * @throw std::bad_cast if the type contained is not the same as the template type.
		 */
		template<typename T>
		T As();

		/**
		 * @brief Creates an Any object with the given arguments.
		 * @tparam T The type of the object to create.
		 * @tparam Args The types of the arguments.
		 * @param args The arguments to pass to the constructor of the object.
		 * @return An Any object containing the created object.
		 */
		template<typename T, class... Args>
		static inline Any Make(Args&&... args);

		void Reset();

		inline bool HasValue() const;

	 private:
		std::size_t _id;
		std::unique_ptr<void*> _data;

		template<typename T>
		class AnyImpl
		{
		 public:
			template<typename... Args>
			explicit AnyImpl(Args&&... args);

			explicit AnyImpl(T& data);

			explicit AnyImpl(T&& data);

			AnyImpl(const AnyImpl&) = default;

			AnyImpl(AnyImpl&&) = default;

			~AnyImpl() = default;

			AnyImpl& operator=(const AnyImpl& other);

			AnyImpl& operator=(AnyImpl&& other) noexcept;

			T* operator->();

		 private:
			T _data;
		};
	};


}
#include "Concerto/Core/Any.inl"
#endif //CONCERTO_CORE_ANY_HPP
