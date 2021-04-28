//
// Created by Gilberto Dougal on 4/26/21.
//

#include "Config.hpp"

Config::Config(const std::string &config_name) {
	std::ifstream ifs(config_name);
	create_config(ifs);
}

void Config::create_config(std::ifstream &ifs) {
	std::string line, section_name;

	while (std::getline(ifs, line))
	{
		if (line[0] == '#') {
			section_name = std::string(line.c_str() + 1);
		}
		else {
			auto delimiter_iterator = std::find(line.begin(), line.end(), ':');
			if (delimiter_iterator == line.end() && !line.empty())
				throw (std::invalid_argument("Wrong config!"));
			else if (delimiter_iterator == line.end())
				continue;
			auto key = std::string(line.begin(), delimiter_iterator);
			auto value = std::string(delimiter_iterator + 1, line.end());
			sections[section_name].setContent(key, value);
		}
	}
}

const Config::Section	&Config::getSection(const std::string &section_name) const {
	auto find_res = sections.find(section_name);
	if(find_res == sections.end())
		throw std::out_of_range("Not found section");
	return find_res->second;
}




void							Config::Section::setContent(const std::string &key, const std::string &value) {
	auto pos = value.find_first_not_of(" \t");
	auto str = value.substr(pos);
	if (pos > value.size() || str.empty())
		throw std::length_error("Empty value field!");
	Section::content[key] = str;
}

const							std::string &Config::Section::throw_or_not(const std::string &Key) const {
	auto find_res = content.find(Key);
	if(find_res == content.end())
		throw std::out_of_range("Not found parameter");
	return find_res->second;
}

bool				Config::Section::getBoolVal(const std::string &Key) const {
	std::string str(throw_or_not(Key));
	bool ret;
	if ( str.size() != 1 || str.at(0) < '0' || str.at(0) > '1' )
		throw std::length_error("Empty value field!");
	ret = ( str.at(0) == '1' );
	return  ret;
}
int 							Config::Section::getIntVal(const std::string &Key) const { return std::stoi(throw_or_not(Key)); }
float 						Config::Section::getFloatVal(const std::string &Key) const { return std::stof( throw_or_not(Key)); }
const std::string	Config::Section::getStringVal(const std::string &Key) const { return throw_or_not(Key); }
