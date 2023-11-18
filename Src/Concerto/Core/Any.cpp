//
// Created by arthur on 18/11/2023.
//

#include "Concerto/Core/Any.hpp"

namespace Concerto
{
    Any::Any(std::size_t id, std::unique_ptr<void*> data) :
        _id(id), _data(std::move(data))
    {
    }

    Any::~Any() { }
}