#include <iostream>
#include <vector>

class Token {
public:
    int64_t value;
    bool is_operation;

    Token(int64_t value, bool is_operation) :
            value(value),
            is_operation(is_operation)
    {};
};

class Lexer {
public:
    std::vector<Token> tokens;
    std::string operation_tokens = "()+-*";
    int ptr = 0;

    Lexer(const std::string& s) {
        std::string num;
        for (const char& c : s) {
            if (c == '.') {
                if (!num.empty()) {
                    tokens.emplace_back(std::stoi(num.data()), false);
                    num = "";
                }
                break;
            }
            if (operation_tokens.find(c) != -1) {
                if (!num.empty()) {
                    tokens.emplace_back(std::stoi(num), false);
                    num = "";
                }
                tokens.emplace_back(c, true);
            }
            else {
                num += c;
            }
        }
    }

    Token next_token() {
        if (ptr >= tokens.size()) {
            return {'.', true};
        }
        Token res = tokens[ptr];
        ptr++;
        return res;
    }
};

int main() {
    std::string input;
    std::cin >> input;
    Lexer lexer(input);
    while(true) {
        auto el = lexer.next_token();
        if (el.value == '.') {
            break;
        }
        if (el.is_operation) {
            std::cout << char(el.value) << '\n';
        }
        else {
            std::cout << el.value << '\n';
        }
    }
    return 0;
}
