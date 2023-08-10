//
// Created by arthur on 01/08/2022.
//



#ifndef CONCERTO_STRUCTUREDDATA_HPP
#define CONCERTO_STRUCTUREDDATA_HPP

#include <string>

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include "Concerto/Core/Config.hpp"
#include "Concerto/Core/Types.hpp"

namespace Concerto
{
	class CONCERTO_PUBLIC_API StructuredData
	{
		using json = nlohmann::ordered_json;
	public:
		explicit StructuredData(const std::string &file);
		explicit StructuredData(std::istream &stream);
		StructuredData(StructuredData&&) = default;
		[[nodiscard]] const Config::Object &GetConfig() const;
	private:
		Config::Object GetObject(const json &object);
		Config::Array GetArray(const json &array);
		Config::NodePtr GetPrimitive(const json &primitive);
		Config::Object _config;
	};
}
#endif //CONCERTO_STRUCTUREDDATA_HPP
