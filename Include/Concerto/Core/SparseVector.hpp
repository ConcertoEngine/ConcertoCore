//
// Created by arthur on 21/05/22.
//

#include <vector>
#include <optional>
#include <stdexcept>
#include "Types.hpp"
#ifndef CONCERTO_SPARSEVECTOR_HPP
#define CONCERTO_SPARSEVECTOR_HPP
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

	explicit SparseVector(size_type size) : _container(size)
	{
	}

	SparseVector(const SparseVector&) = delete;
	SparseVector(SparseVector&&) noexcept = default;
	~SparseVector() = default;
	SparseVector& operator=(const SparseVector&) = delete;
	SparseVector& operator=(SparseVector&&) noexcept = default;

	/**
	 * @brief Get the size of the SparseVector
	 * @return The size of the SparseVector
	 */
	size_type size() const
	{
		return _container.size();
	}

	/**
	 *  Returns true if the %SparseVector is empty.  (Thus begin() would equal end().)
	 * @return
	 */
	[[nodiscard]] bool empty() const
	{
		return _container.empty();
	}

	/**
	 * @return Returns a read/write iterator that points to the first element in the %SparseVector.
	 * Iteration is done in ordinary element order.
	 */
	iterator begin()
	{
		return _container.begin();
	}

	/**
	 * @return Returns a read/write iterator that points one past the last element in the %SparseVector.
	 * Iteration is done in ordinary element order.
	 */
	iterator end()
	{
		return _container.end();
	}

	/**
	 * @return Returns a read-only (constant) iterator that points to the first element in the %SparseVector.
	 * Iteration is done in ordinary element order.
	 */
	const_iterator begin() const
	{
		return _container.cbegin();
	}

	/**
	 * @return Returns a read-only (constant) iterator that points one past the last element in the %SparseVector.
	 * Iteration is done in ordinary element order.
	 */
	const_iterator end() const
	{
		return _container.cend();
	}

	/**
	 * @brief Subscript access to the data contained in the %SparseVector.
	 * @param index The index of the element for which data should be accessed.
	 * @return Returns a read/write reference to the element at specified location.
	 */
	reference_type operator[](size_type index)
	{
		CONCERTO_ASSERT(index >= _container.size())
		if (!Has(index))
			throw std::runtime_error("Index Has no value");
		return _container[index].value();
	}

	/**
	 * @brief Subscript access to the data contained in the %SparseVector.
	 * @param index The index of the element for which data should be accessed.
	 * @return Read-only (constant) reference to data.
	 */
	const_reference_type operator[](size_type index) const
	{
		CONCERTO_ASSERT(index >= _container.size())
		if (!Has(index))
			throw std::runtime_error("Index Has no value");
		return _container[index].value();
	}

	/**
	 * @brief Attempts to build and insert an element into the %SparseVector.
	 * @param index The index of the element to be inserted.
	 * @param args Arguments used to construct the element.
	 * @return
	 */
	template<typename... Args>
	reference_type Emplace(size_type index, Args&& ... args)
	{
		if (index >= _container.size())
			_container.resize(index + 1);
		_container[index] = std::make_optional<value_type>((std::forward<Args>(args))...);
		return _container.at(index).value();
	}

	/**
	 * @brief Removes the element at specified index from the %SparseVector.
	 * @param index The index of the element to be removed.
	 */
	void Erase(size_type index)
	{
		CONCERTO_ASSERT(index >= _container.size() || !_container[index].has_value())
		_container[index].reset();
	}

	/**
	 * @param index The index of the element to be tested.
	 * @return Returns true if the element at specified location Has a value.
	 */
	bool Has(size_type index) const
	{
		return index < _container.size() && _container[index].has_value();
	}

private:
	container_type _container;
};

#endif // CONCERTO_SPARSEVECTOR_HPP