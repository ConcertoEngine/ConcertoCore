//
// Created by arthur on 01/08/2022.
//

#ifndef CONCERTO_CORE_CONFIG_HPP
#define CONCERTO_CORE_CONFIG_HPP

#include <algorithm>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>
#include "Concerto/Core/Types.hpp"
#include "Concerto/Core/Assert.hpp"

namespace cct::Config {
	struct nullNode {};
	class Node;

	using NodePtr = std::shared_ptr<Node>;

	template<typename T, typename Allocator = std::allocator<T>>
	//requires std::is_same_v<std::pair<std::string, NodePtr>, T>
	class Vector : public std::vector<T, Allocator>
	{
	public:
		Node& operator[](const std::string &key)
		{
			auto obj =
					std::find_if(this->begin(), this->end(),
							[&key](const auto &pair) { return pair.first == key; });
			if (obj == this->end())
				throw std::out_of_range("Key not found: " + key);
			return *obj->second;
		}

		const Node& operator[](const std::string &key) const
		{
			auto obj =
					std::find_if(this->cbegin(), this->cend(),
							[&key](const auto &pair) { return pair.first == key; });
			if (obj == this->end())
				throw std::out_of_range("Key not found: " + key);
			return *obj->second;
		}
	};


	using Array = std::vector<NodePtr>;
	/**
	 * @brief std::unordered_map<std::string, NodePtr> is not used because we want
	 * to conserve the insertion order
	 **/
	using Object = Vector<std::pair<std::string, NodePtr>>;

	using Double = double;
	using Bool = bool;
	using String = std::string;

	using Variant =
			std::variant<Bool, Int32, UInt32, Double, Array, Object, String, nullNode>;
	/**
	 * @brief The Node class
	 *
	 * This class is the base class of all the nodes of the config file.
	 **/
	class Node {
	public:
		explicit Node(const Array &array) : _variant(array) {}

		explicit Node(const Object &object) : _variant(object) {}
		
		explicit Node(const String &str) : _variant(str) {}
		
		explicit Node(Bool b) : _variant(b) {}
		
		explicit Node(Int32 i) : _variant(i) {}
		
		explicit Node(UInt32 u) : _variant(u) {}
		
		explicit Node(Double d) : _variant(d) {}
		
		Node(Node &&) = default;

		/**
	  	* @brief Cast the node as T
	 	* @return The type of the node
	  	**/
		template <typename T>
		T &As() { return std::get<T>(_variant); }

		Config::String &AsString() {return std::get<Config::String>(_variant);}

		Config::Object &AsObject() {return std::get<Config::Object>(_variant);}
		
		Config::Array &AsArray() {return std::get<Config::Array>(_variant);}

		/**
		* @brief Cast the node as const T
		* @return The type of the node
		**/
		template <typename T> [[nodiscard]]
		const T &As() const { return std::get<T>(_variant); }
		
		[[nodiscard]] const Config::String &AsString() const {return std::get<Config::String>(_variant);}
		
		[[nodiscard]] const Config::Object &AsObject() const {return std::get<Config::Object>(_variant);}
		
		[[nodiscard]] const Config::Array &AsArray() const {return std::get<Config::Array>(_variant);}

		/**
		* @brief Cast the node As an Object
		* @return The node contained at key
		**/
		Node &operator[](const String &key) const {
			auto node =
					std::find_if(As<Object>().begin(), As<Object>().end(),
							[&key](const auto &pair) { return pair.first == key; });
			if (node == As<Object>().end())
				throw std::out_of_range("Key not found: " + key);
			return *node->second;
		}

		/**
		* @brief Cast the node As an Array
		* @return The node contained at index
		**/
		Node &operator[](std::size_t index) const
		{
			auto array = AsArray();
			CCT_ASSERT(index < array.size(), "Index out of range");
			return *array[index];
		}

	private:
		Variant _variant;
	};
} // namespace Config
#endif //CONCERTO_CORE_CONFIG_HPP
