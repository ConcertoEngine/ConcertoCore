//
// Created by arthur on 21/05/22.
//

#ifndef CONCERTOCORE_SPARSEVECTOR_HPP
#define CONCERTOCORE_SPARSEVECTOR_HPP

#include <vector>
#include <optional>
#include <stdexcept>
#include "Concerto/Core/Types.hpp"

namespace Concerto
{
	/**
	* @brief SparseVector
	* A container which offers fixed time access to individual elements in any order, its indices can contain gaps.
	* @tparam value_type Type of the elements
	* @tparam allocator Allocator used to allocate the elements
	*/
	template<typename value_type, typename allocator = std::allocator<std::optional<value_type>>>
	class SparseVector
	{
	public:
		using container_type = std::vector<std::optional<value_type>, allocator>;
		using reference_type = value_type&;
		using const_reference_type = const value_type&;
		using size_type = typename container_type::size_type;
		using iterator = typename container_type::iterator;
		using const_iterator = typename container_type::const_iterator;

		SparseVector() = default;
		explicit SparseVector(size_type size);
		SparseVector(const SparseVector&) = default;
		SparseVector(SparseVector&&) noexcept = default;
		~SparseVector() = default;
		SparseVector& operator=(const SparseVector&) = default;
		SparseVector& operator=(SparseVector&&) noexcept = default;

		// STL Container Interface
		size_type size() const;
		[[nodiscard]] bool empty() const;
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		/**
		* @brief Subscript access to the data contained in the %SparseVector.
		* @param index The index of the element for which data should be accessed.
		* @return Returns a read/write reference to the element at specified location.
		*/
		reference_type operator[](size_type index);

		/**
		* @brief Subscript access to the data contained in the %SparseVector.
		* @param index The index of the element for which data should be accessed.
		* @return Read-only (constant) reference to data.
		*/
		const_reference_type operator[](size_type index) const;

		/**
		* @brief Attempts to build and insert an element into the %SparseVector.
		* @param index The index of the element to be inserted.
		* @param args Arguments used to construct the element.
		* @return
		*/
		template<typename... Args>
		reference_type Emplace(size_type index, Args&& ... args);

		/**
		* @brief Removes the element at specified index from the %SparseVector.
		* @param index The index of the element to be removed.
		*/
		void Erase(size_type index);

		/**
		* @param index The index of the element to be tested.
		* @return Returns true if the element at specified location Has a value.
		*/
		bool Has(size_type index) const;

		/**
		* @brief Removes all elements from the %SparseVector.
		*/
		void Clear();
	private:
		container_type _container;
	};
}

#include "Concerto/Core/SparseVector.inl"
#endif // CONCERTOCORE_SPARSEVECTOR_HPP