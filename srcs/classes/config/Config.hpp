//
// Created by Gilberto Dougal on 4/26/21.
//

#ifndef HELLO_SFML_CONFIG_HPP
#define HELLO_SFML_CONFIG_HPP

#include <unordered_map>
#include <any>
#include <fstream>
#include <istream>

class Config
{
	class Section;
public:

	explicit Config(const std::string& config_name) {
		std::ifstream ifs(config_name);
		create_config(ifs);
	}

	const std::unordered_map<std::string, Section>	&getSections()																																const { return sections; }
	const std::unordered_map<std::string, std::any>	&getSection(const std::string& section_name)																	const { return sections.find(section_name)->second.getContent(); }
	const std::any																	&getAnyValue(const std::string& section_name, const std::string& value_name)	const { return getSection(section_name).find(value_name)->second; }

private:
	std::unordered_map<std::string, Section> sections;

	class Section {
		std::unordered_map<std::string, std::any> content;
	public:
		Section() {}
		const std::unordered_map<std::string, std::any> &getContent() const { return content; }
		void setContent(const std::string& key, const std::string& value) {
			auto a = value.find_first_not_of(' ');
			if (a > value.size())
				throw "atata";
			Section::content[key] = value.substr(a);
		}
	};

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
				if (delimiter_iterator == line.end())
					continue;
				auto key = std::string(line.begin(), delimiter_iterator);
				auto value = std::string(delimiter_iterator + 1, line.end());
				sections[section_name].setContent(key, value);
			}
		}
	}
};



#endif //HELLO_SFML_CONFIG_HPP
