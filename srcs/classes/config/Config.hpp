//
// Created by Gilberto Dougal on 4/26/21.
//

#ifndef HELLO_SFML_CONFIG_HPP
#define HELLO_SFML_CONFIG_HPP

#include <unordered_map>
#include <any>
#include <fstream>
#include <istream>
#include <exception>



class Config
{
public:
	class Section;
	explicit Config(const std::string& config_name) {
		std::ifstream ifs(config_name);
		create_config(ifs);
	}

	const Section																		&getSection(const std::string& section_name)																	const { return sections.find(section_name)->second; }

	class Section {
		friend Config;
		std::unordered_map<std::string, std::string> content;
		void setContent(const std::string& key, const std::string& value) {
			auto pos = value.find_first_not_of(" \t");
			auto str = value.substr(pos);
			if (pos > value.size() || str.empty())
				throw std::length_error("Empty value field!");
			Section::content[key] = str;
		}
	public:
		Section() {}
		const std::string	getStringVal(const std::string& Key)	const { return content.find(Key)->second; }
		const float				getFloatVal(const std::string& Key)		const { return std::stof(content.find(Key)->second); }
		const int					getIntVal(const std::string& Key)			const { return std::stoi(content.find(Key)->second); }

		const bool				getBoolVal(const std::string& Key)		const {
			std::string str(content.find(Key)->second);
			bool a;
			if ( str.size() != 1 || str.at(0) < '0' || str.at(0) > '1' )
				throw std::length_error("Empty value field!");
			a = ( str.at(0) == '1' );
			return  a;
		}
	};
private:
	std::unordered_map<std::string, Section> sections;

	void create_config(std::ifstream & ifs)
	{
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
};



#endif //HELLO_SFML_CONFIG_HPP
