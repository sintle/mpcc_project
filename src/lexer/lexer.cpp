#pragma once

#include "lexer/lexer.hpp"
#include "program/vm_options.hpp"

#include <functional>

void reserved_err(std::string _res) {
    err_begin();
    std::cerr << "Cannot use reserved word \"" << _res << "\" to be an identifier.";
    err_end();
}

void Lexer::break_whitespace() {
    while (_at < _input.length() && isspace(_input.at(_at))) {
        if (_input.at(_at) == '\n') {
            _line++;
            _column = 0;
        }
        else {
            _column++;
        }
        _at++;

    }
}

std::string Lexer::read_identifier() {
    std::string res = "";
    while (isalnum(_input.at(_at)) || _input.at(_at) == '_') {
        res += _input.at(_at);
        _column++;
        _at++;
    }
}

std::pair<std::string, Token::Type> Lexer::read_number() {
    std::function<bool(char)> isValid = [](char ch)->bool {
        return isdigit(ch) || ch == '.';
    };
    std::string res;
    if (_input.at(_at) == '0') {
        if (_input.at(_at + 1) == 'x') {
            isValid = [](char ch)->bool {
                return isdigit(ch) || ('a' <= ch && ch <= 'f') || ('A' <= ch && ch <= 'F');
            };
            _column += 2;
            _at += 2;
            res = "0x";
        }
        else if (_input.at(_at + 1) == 'b') {
            isValid = [](char ch)->bool {
                return ch == '0' || ch == '1';
            };
            _column += 2;
            _at += 2;
            res = "0b";
        }
        else if (isdigit(_input.at(_at + 1))) {
            isValid = [](char ch)->bool {
                return '0' <= ch && ch <= '7';
            };
            _column++;
            _at++;
            res = "0";
        }
        else if (_input.at(_at + 1) != '.') {
            return std::make_pair("0", Token::Type::Integer);
        }
    }
    while (isValid(_input.at(_at))) {
        res += _input.at(_at);
        _column++;
        _at++;
    }
    if (res.at(res.length() - 1) == '.') {
        res = res.substr(0, res.length() - 1);
        _at--;
        _column--;
    }
    return std::make_pair(res, (res.find('.') != res.npos) ? Token::Type::Float : Token::Type::Integer);
}

std::string Lexer::read_string() {
    std::string res = "\"";
    _column++;
    _at++;
    while (_input.at(_at) != '"') {
        if (_input.at(_at) == '\\') {
            res += '\\';
            res += _input.at(_at + 1);
            _column += 2;
            _at += 2;
            continue;
        }
        res += _input.at(_at);
        _column++;
        _at++;
    }
    _column++;
    _at++;
    return res + '"';
}

std::shared_ptr<Token> Lexer::parseNext() {
    // Break whitespace
    break_whitespace();
    // Return "End" when end.
    if (_input.length() == _at) {
        return std::make_shared<Token>("", Token::Type::End);
    }
    // Ignore comments.
    if (_input.length() > _at + 1 && _input.at(_at) == '#' && _input.at(_at + 1) == '!') {
        while (_input.length() > _at && _input.at(_at) != '\n') {
            _at++;
        }
        _at++;
        _line++;
        _column = 0;
    } // UNIX <#!/path/to/mpcc>
    if (_input.length() > _at + 1 && _input.at(_at) == '/') {
        if (_input.at(_at + 1) == '/') {
            while (_input.length() > _at && _input.at(_at) != '\n') {
                _at++;
            }
            _at++;
            _line++;
            _column = 0;
        } // In-line comment
        else if (_input.at(_at + 1) == '*') {
            _at += 2;
            _column += 2;
            while (_input.length() > _at) {
                if (_input.at(_at) == '*' && _input.length() > (_at + 1)) {
                    if (_input.at(_at + 1) == '/') {
                        _at += 2;
                        break;
                    }
                }
                if (_input.at(_at) == '\n') {
                    _line++;
                    _column = 0;
                }
                else {
                    _column++;
                }
                _at++;
            }
        } // Out-line comment
    }
    // Try non-identifier tokens.
    switch (_input.at(_at)) {
    case '~':
        _column++;
        _at++;
        return std::make_shared<Token>("~", Token::Type::BitwiseNot);
    case '!':
        if (_input.length() > _at + 1 && _input.at(_at + 1) == '=') {
            _column += 2;
            _at += 2;
            return std::make_shared<Token>("!=", Token::Type::NotEqual);
        }
        _column++;
        _at++;
        return std::make_shared<Token>("!", Token::Type::LogicalNot);
    case '$':
        _column++;
        _at++;
        return std::make_shared<Token>("$", Token::Type::Lambda);
    case '%':
        if (_input.length() > _at + 1 && _input.at(_at + 1) == '=') {
            _column += 2;
            _at += 2;
            return std::make_shared<Token>("%=", Token::Type::ModulusAssign);
        }
        _column++;
        _at++;
        return std::make_shared<Token>("%", Token::Type::Modulus);
    case '^':
        if (_input.length() > _at + 1 && _input.at(_at + 1) == '=') {
            _column += 2;
            _at += 2;
            return std::make_shared<Token>("^=", Token::Type::BitwiseXorAssign);
        }
        _column++;
        _at++;
        return std::make_shared<Token>("^", Token::Type::BitwiseXor);
    case '&':
        if (_input.length() > _at + 1) {
            if (_input.at(_at + 1) == '&') {
                _column += 2;
                _at += 2;
                return std::make_shared<Token>("&&", Token::Type::LogicalAnd);
            }
            if (_input.at(_at + 1) == '=') {
                _column += 2;
                _at += 2;
                return std::make_shared<Token>("&=", Token::Type::BitwiseAndAssign);
            }
        }
        _column++;
        _at++;
        return std::make_shared<Token>("&", Token::Type::BitwiseAnd);
    case '*':
        if (_input.length() > _at + 1 && _input.at(_at + 1) == '=') {
            _column += 2;
            _at += 2;
            return std::make_shared<Token>("*=", Token::Type::AsteriskAssign);
        }
        _column++;
        _at++;
        return std::make_shared<Token>("*", Token::Type::Asterisk);
    case '(':
        _column++;
        _at++;
        return std::make_shared<Token>("(", Token::Type::LParan);
    case ')':
        _column++;
        _at++;
        return std::make_shared<Token>(")", Token::Type::RParan);
    case '-':
        if (_input.length() > _at + 1) {
            if (_input.at(_at + 1) == '=') {
                _column += 2;
                _at += 2;
                return std::make_shared<Token>("-=", Token::Type::MinusAssign);
            }
            if (_input.at(_at + 1) == '-') {
                _column += 2;
                _at += 2;
                return std::make_shared<Token>("--", Token::Type::Decrement);
            }
        }
        _column++;
        _at++;
        return std::make_shared<Token>("-", Token::Type::Minus);
    case '=':
        if (_input.length() > _at + 1 && _input.at(_at + 1) == '=') {
            _column += 2;
            _at += 2;
            return std::make_shared<Token>("==", Token::Type::Equal);
        }
        _column++;
        _at++;
        return std::make_shared<Token>("=", Token::Type::NotEqual);
    case '+':
        if (_input.length() > _at + 1) {
            if (_input.at(_at + 1) == '=') {
                _column += 2;
                _at += 2;
                return std::make_shared<Token>("+=", Token::Type::PlusAssign);
            }
            if (_input.at(_at + 1) == '+') {
                _column += 2;
                _at += 2;
                return std::make_shared<Token>("++", Token::Type::Increment);
            }
        }
        _column++;
        _at++;
        return std::make_shared<Token>("+", Token::Type::Plus);
    case '{':
        _column++;
        _at++;
        return std::make_shared<Token>("{", Token::Type::LBrace);
    case '}':
        _column++;
        _at++;
        return std::make_shared<Token>("}", Token::Type::RBrace);
    case '[':
        _column++;
        _at++;
        return std::make_shared<Token>("[", Token::Type::LBracket);
    case ']':
        _column++;
        _at++;
        return std::make_shared<Token>("]", Token::Type::RBracket);
    case '|':
        if (_input.length() > _at + 1) {
            if (_input.at(_at + 1) == '=') {
                _column += 2;
                _at += 2;
                return std::make_shared<Token>("|=", Token::Type::BitwiseOrAssign);
            }
            if (_input.at(_at + 1) == '|') {
                _column += 2;
                _at += 2;
                return std::make_shared<Token>("||", Token::Type::LogicalOr);
            }
        }
        _column++;
        _at++;
        return std::make_shared<Token>("|", Token::Type::BitwiseOr);
    case ',':
        _column++;
        _at++;
        return std::make_shared<Token>(",", Token::Type::Comma);
    case '.':
        if (_input.length() > _at + 2 && _input.at(_at + 1) == '.' && _input.at(_at + 2) == '.') {
            _column += 3;
            _at += 3;
            return std::make_shared<Token>("...", Token::Type::More);
        }
        _column++;
        _at++;
        return std::make_shared<Token>(".", Token::Type::Extand);
    case ';':
        _column++;
        _at++;
        return std::make_shared<Token>(";", Token::Type::Semicolon);
    case '/':
        if (_input.length() > _at + 1 && _input.at(_at + 1) == '=') {
            _column += 2;
            _at += 2;
            return std::make_shared<Token>("/=", Token::Type::SlashAssign);
        }
        _column++;
        _at++;
        return std::make_shared<Token>("/", Token::Type::Slash);
    case '<':
        if (_input.length() > _at + 1) {
            if (_input.at(_at + 1) == '<') {
                if (_input.length() > _at + 2 && _input.at(_at + 2) == '=') {
                    _column += 3;
                    _at += 3;
                    return std::make_shared<Token>("<<=", Token::Type::BitwiseLeftAssign);
                }
                _column += 2;
                _at += 2;
                return std::make_shared<Token>("<<", Token::Type::BitwiseLeft);
            }
            if (_input.at(_at + 1) == '=') {
                _column += 2;
                _at += 2;
                return std::make_shared<Token>("<=", Token::Type::LessEqual);
            }
        }
        _column++;
        _at++;
        return std::make_shared<Token>("<", Token::Type::Less);
    case '>':
        if (_input.length() > _at + 1) {
            if (_input.at(_at + 1) == '>') {
                if (_input.length() > _at + 2 && _input.at(_at + 2) == '=') {
                    _column += 3;
                    _at += 3;
                    return std::make_shared<Token>(">>=", Token::Type::BitwiseRightAssign);
                }
                _column += 2;
                _at += 2;
                return std::make_shared<Token>(">>", Token::Type::BitwiseRight);
            }
            if (_input.at(_at + 1) == '=') {
                _column += 2;
                _at += 2;
                return std::make_shared<Token>(">=", Token::Type::GreaterEqual);
            }
        }
        _column++;
        _at++;
        return std::make_shared<Token>(">", Token::Type::Greater);
    case ':':
        _column++;
        _at++;
        return std::make_shared<Token>(":", Token::Type::As);
    case '?':
        _column++;
        _at++;
        return std::make_shared<Token>("?", Token::Type::Ternary);
    }
    if (isdigit(_input.at(_at))) {
        auto _result = read_number();
        return std::make_shared<Token>(_result.first, _result.second);
    }
    if (_input.at(_at) == '"') {
        return std::make_shared<Token>(read_string(), Token::Type::String);
    }
    std::string id = read_identifier();
    if (reserved.count(id) > 0) {
        reserved_err(id);
        return std::make_shared<Token>(id, Token::Type::Error);
    }
    return std::make_shared<Token>(id, lookup(id));
}

std::set<std::string> Lexer::reserved = {
    "__level__",
    "__builtin__",
    "__null__"
};