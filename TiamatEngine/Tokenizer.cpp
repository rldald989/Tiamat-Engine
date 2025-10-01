#include "Tokenizer.h"

TMT::Tokenizer::Tokenizer() : m_position(0)
{
}

TMT::Tokenizer::~Tokenizer()
{
}

void TMT::Tokenizer::load_file(const char* file_path)
{
    std::ifstream code;

    code.open(file_path);

    char c;
    while (code.get(c))
    {
        if (c == '\0') {

        }
        else {
            m_file.push_back(c);
        }
    }

    code.close();
}

std::vector<std::string> TMT::Tokenizer::tokenize()
{
    std::vector<std::string> tokens;

    std::string buffer;
    bool quote_flag = false;
    while (peek() != '\0') {
        if (std::isalpha(peek()))
        {
            buffer.push_back(consume());
            while (peek() != '\0' && (std::isalpha(peek()) || peek() == '_'))
            {
                buffer.push_back(consume());
            }

            tokens.push_back(buffer);

            buffer.clear();

        }
        else if (std::isdigit(peek()))
        {
            buffer.push_back(consume());
            while (peek() != '\0' && (std::isdigit(peek()) || peek() == '.'))
            {
                buffer.push_back(consume());
            }

            tokens.push_back(buffer);

            buffer.clear();

        }
        else if (std::ispunct(peek()))
        {
            buffer.push_back(consume());

            for (int i = 0; i < sizeof(punct_tokens) / sizeof(punct_tokens[0]); i++) {
                if (buffer[0] == punct_tokens[i]) {
                    tokens.push_back(buffer);
                    if (tokens.back() == "\"") {
                        quote_flag = !quote_flag;
                    }
                    buffer.clear();
                }
            }

        }
        else if (std::isspace(peek()))
        {
            buffer.push_back(consume());
            if (quote_flag) {
                tokens.push_back(buffer);
            }
            buffer.clear();
        }
        else if (peek() == '\n') {
            consume();
        }
    }
	return tokens;
}
