#pragma once

#include <vector>
#include <string>
#include <fstream>

namespace TMT {

    static std::string alpha_tokens[] =
    {
        "int",
        "string",
        "float",
        "print",
        "read",
        "printl",
        "readl"
    };

    static char punct_tokens[] = {
        ':',
        ';',
        '?',
        '!',
        '.',
        '[',
        ']',
        '#',
        '(',
        ')',
        '\"'
    };

	class Tokenizer
	{
	public:
		Tokenizer();
		~Tokenizer();
        
        void load_file(const char* file_path);
        std::vector<std::string> tokenize();

	private:
        std::string m_file;
        int m_position;

        char peek(int ahead = 1) const {
            if (m_position + ahead > m_file.length()) {
                return '\0';
            }
            else
            {
                return m_file[m_position];
            }
        }

        char consume()
        {
            return m_file[m_position++];
        }

	};
}