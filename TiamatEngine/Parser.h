#pragma once

#include "Tokenizer.h"
#include <iostream>
#include <sstream>

namespace TMT {

	enum class scene_type {
		SHADER,
		TEXTURE,
		MATERIAL,
		MESH_RENDERER
	};

	struct scene_component 
	{
		scene_type type;
		std::string* value;
	};

	template <typename F>
	struct file_viewer {

		file_viewer(std::vector<F> _t) : tokens(_t), position(0), string_flag(false) {}
		~file_viewer() {}

		std::vector<F> tokens;
		int position;
		bool string_flag;

		std::string peek(int ahead = 1) const
		{
			if (position + ahead > tokens.size()) {
				return "\0";
			}
			else {
				return tokens[position];
			}
		}

		std::string consume() {
			return tokens[position++];
		}

		void forward()
		{
			position++;
			if (peek() == "\"") {
				string_flag = !string_flag;
			}
		}

		std::string while_peek(std::string start, std::string end) 
		{
			std::string buffer;
			if (peek() == start) {
				forward();
				while (peek() != end)
				{
					buffer += consume();
				}
			}
			else {
				return {};
			}

			return buffer;
		}

		std::string detect_string() 
		{
			std::string buffer;
			if (peek() == "\"") {
				forward();
				while (string_flag)
				{
					buffer += consume();
				}
			}
			else {
				return {};
			}

			return buffer;
		}

		void continue_if(std::string to_find, bool is, std::string at) 
		{
			while ((peek() == to_find) == is) {
				forward();
				if (position >= tokens.size())
				{
					std::cout << "ERROR: Missing " << to_find << " at " << position << " " << at << std::endl;
					exit(EXIT_FAILURE);
				}
			}
		}
	};

	static std::vector<std::string> tokenize_string(std::string str) 
	{
		std::vector<std::string> result;
		for (auto& s : str) {
			result.push_back(str);
		}
		return result;
	}

	class Parser
	{
	public:
		Parser(std::vector<std::string>& tokens);
		~Parser();

		std::vector<scene_component*> parse();

	private:
		std::vector<std::string>& m_tokens;
		std::vector<scene_component> m_scene_tokens;
		file_viewer<std::string> m_viewer;
	};
}