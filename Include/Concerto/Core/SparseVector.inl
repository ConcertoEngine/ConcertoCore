//
// Created by arthur on 12/10/2023.
//

#ifndef CONCERTOCORE_SPARSEVECTOR_INL
#define CONCERTOCORE_SPARSEVECTOR_INL

#include "Concerto/Core/SparseVector.hpp"

namespace Concerto
{
    template<typename value_type, typename allocator>
    SparseVector<value_type, allocator>::SparseVector(SparseVector::size_type size) :
        _container(size)
    {

    }

	template<typename value_type, typename allocator>
	SparseVector<value_type, allocator>::size_type SparseVector<value_type, allocator>::size() const
	{
		return _container.size();
	}

	template<typename value_type, typename allocator>
	[[nodiscard]] bool SparseVector<value_type, allocator>::empty() const
	{
		return _container.empty();
	}

	template<typename value_type, typename allocator>
	SparseVector<value_type, allocator>::iterator SparseVector<value_type, allocator>::begin()
	{
		return _container.begin();
	}
	
	template<typename value_type, typename allocator>
	SparseVector<value_type, allocator>::iterator SparseVector<value_type, allocator>::end()
	{
		return _container.end();
	}

	template<typename value_type, typename allocator>
	SparseVector<value_type, allocator>::const_iterator SparseVector<value_type, allocator>::begin() const
	{
		return _container.cbegin();
	}

	template<typename value_type, typename allocator>
	SparseVector<value_type, allocator>::const_iterator SparseVector<value_type, allocator>::end() const
	{
		return _container.cend();
	}

	template<typename value_type, typename allocator>
	SparseVector<value_type, allocator>::reference_type SparseVector<value_type, allocator>::operator[](size_type index)
	{
		CONCERTO_ASSERT(index >= _container.size() - 1)
			if (index >= _container.size())
				throw std::out_of_range("Index out of range");
			if (!Has(index))
				throw std::runtime_error("Index Has no value");
			return _container[index].value();
	}

	template<typename value_type, typename allocator>
	SparseVector<value_type, allocator>::const_reference_type SparseVector<value_type, allocator>::operator[](size_type index) const
	{
		CONCERTO_ASSERT(index >= _container.size() - 1)
		if (index >= _container.size())
			throw std::out_of_range("Index out of range");
		if (!Has(index))
			throw std::runtime_error("Index Has no value");
		return _container[index].value();
	}

    template<typename value_type, typename allocator>
    template<typename... Args>
    SparseVector<value_type, allocator>::reference_type SparseVector<value_type, allocator>::Emplace(SparseVector::size_type index, Args &&... args)
    {
        if (index >= _container.size())
            _container.resize(index + 1);
        _container[index] = std::make_optional<value_type>((std::forward<Args>(args))...);
        return _container.at(index).value();
    }

    template<typename value_type, typename allocator>
    void SparseVector<value_type, allocator>::Erase(SparseVector::size_type index)
    {
        CONCERTO_ASSERT(index >= _container.size() - 1 || !_container[index].has_value())
        _container[index].reset();
    }

    template<typename value_type, typename allocator>
    bool SparseVector<value_type, allocator>::Has(SparseVector::size_type index) const
    {
        return index < _container.size() && _container[index].has_value();
    }

    template<typename value_type, typename allocator>
    void SparseVector<value_type, allocator>::Clear()
    {
        _container.clear();
    }
}

#endif //CONCERTOCORE_SPARSEVECTOR_INL