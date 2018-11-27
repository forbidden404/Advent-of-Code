#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdint>
#include <map>

struct InputVariable {
    InputVariable() : type(InputVariable::Number), number(0) {}
    ~InputVariable() {}
    InputVariable(const InputVariable& rhs);
    InputVariable& operator=(const InputVariable& rhs);
    enum UnionType { String, Number };
    UnionType type;
    union {
        std::string str;
        int number;
    };
};

InputVariable::InputVariable(const InputVariable& rhs) : type(rhs.type) {
    if (type == InputVariable::String)
        str = rhs.str;
    else
        number = rhs.number;
}

InputVariable& InputVariable::operator=(const InputVariable& rhs) {
    type = rhs.type;

    if (type == InputVariable::String)
        str = rhs.str;
    else
        number = rhs.number;

    return *this;
}

class OperationParsing {
    public: 
        std::string output_variable;
        enum OP { Assign, And, Or, LShift, RShift, Not };
        OP op;
        InputVariable input_variables[2];

        OperationParsing(std::string ov = "", OP op = OperationParsing::Assign, InputVariable *iv = NULL)
            : output_variable(ov), op(op) { 
                if (iv == NULL) {
                    input_variables[0] = InputVariable();
                    input_variables[1] = InputVariable();
                } else {
                    input_variables[0] = iv[0];
                    input_variables[1] = iv[1];
                }
            }
        OperationParsing(const OperationParsing& o)
            : output_variable(o.output_variable), op(o.op) {
                input_variables[0] = o.input_variables[0];
                input_variables[1] = o.input_variables[1];
            }
};

std::vector<std::string> splitWords(std::string str, std::vector<std::string> delimiters) {
    std::vector<std::string> result;
    std::string str2 = str;

    while (str2.length() > 0) {
        int delim_size = 0;
        std::size_t found = str2.length();
        for (auto delim : delimiters) {
            std::size_t cur_found = str2.find(delim);
            if (cur_found != std::string::npos && cur_found < found) {
                found = cur_found;
                delim_size = delim.length();
            }
        }

        std::string ins = str2.substr(0, found);
        if (!ins.empty())
            result.push_back(ins);
        str2 = str2.substr(found + delim_size);
    }

    return result;
}

bool isNumber(std::string input) {
    for (auto c : input) {
        if (c < '0' || c > '9')
            return false;
    }

    return true;
}

OperationParsing get_parsed_string(std::string input) {
    OperationParsing operationParsing;

    std::vector<std::string> delimiters;
    delimiters.push_back(" ");
    delimiters.push_back("->");
    auto words_vec = splitWords(input, delimiters);
    if (words_vec.size() == 2) {
        operationParsing.op = OperationParsing::Assign;

        if (isNumber(words_vec[0])) {
            operationParsing.input_variables[0].type = InputVariable::Number;
            operationParsing.input_variables[0].number = std::stoi(words_vec[0]); 
        } else {
            operationParsing.input_variables[0].type = InputVariable::String;
            operationParsing.input_variables[0].str = words_vec[0];
        }
    } else if (words_vec.size() == 3) {
        operationParsing.op = OperationParsing::Not;

        if (isNumber(words_vec[1])) {
            operationParsing.input_variables[0].type = InputVariable::Number;
            operationParsing.input_variables[0].number = std::stoi(words_vec[1]); 
        } else {
            operationParsing.input_variables[0].type = InputVariable::String;
            operationParsing.input_variables[0].str = words_vec[1];
        }
    } else if (words_vec.size() == 4) {
        if (words_vec[1].compare("AND") == 0) {
            operationParsing.op = OperationParsing::And;
        } else if (words_vec[1].compare("OR") == 0) {
            operationParsing.op = OperationParsing::Or;
        } else if (words_vec[1].compare("LSHIFT") == 0) {
            operationParsing.op = OperationParsing::LShift;
        } else if (words_vec[1].compare("RSHIFT") == 0) {
            operationParsing.op = OperationParsing::RShift;
        }

        if (isNumber(words_vec[0])) {
            operationParsing.input_variables[0].type = InputVariable::Number;
            operationParsing.input_variables[0].number = std::stoi(words_vec[0]); 
        } else {
            operationParsing.input_variables[0].type = InputVariable::String;
            operationParsing.input_variables[0].str = words_vec[0];
        }

        if (isNumber(words_vec[2])) {
            operationParsing.input_variables[1].type = InputVariable::Number;
            operationParsing.input_variables[1].number = std::stoi(words_vec[2]); 
        } else {
            operationParsing.input_variables[1].type = InputVariable::String;
            operationParsing.input_variables[1].str = words_vec[2];
        }

    }

    operationParsing.output_variable = words_vec[words_vec.size() - 1];

    return operationParsing;
}

std::map<std::string, int> evaluated_values;
uint16_t evaluate(std::map<std::string, OperationParsing> &variables, std::string variable) {
    uint16_t result = 0;
    OperationParsing current = variables[variable];

    auto it = evaluated_values.find(variable);
    if (it != evaluated_values.end()) {
        return evaluated_values[variable];
    }

    uint16_t a = 0, b = 0;
    switch (current.op) {
        case OperationParsing::And:
            if (current.input_variables[0].type == InputVariable::String) {
                a = evaluate(variables, current.input_variables[0].str);
            } else {
                a = current.input_variables[0].number;
            }

            if (current.input_variables[1].type == InputVariable::String) {
                b = evaluate(variables, current.input_variables[1].str);
            } else {
                b = current.input_variables[1].number;
            }

            result = a & b;
            break;
        case OperationParsing::Or:
            if (current.input_variables[0].type == InputVariable::String) {
                a = evaluate(variables, current.input_variables[0].str);
            } else {
                a = current.input_variables[0].number;
            }

            if (current.input_variables[1].type == InputVariable::String) {
                b = evaluate(variables, current.input_variables[1].str);
            } else {
                b = current.input_variables[1].number;
            }

            result = a | b;
            break;
        case OperationParsing::Not:
            if (current.input_variables[0].type == InputVariable::String) {
                a = evaluate(variables, current.input_variables[0].str);
            } else {
                a = current.input_variables[0].number;
            }

            result = ~a;
            break;
        case OperationParsing::LShift:
            if (current.input_variables[0].type == InputVariable::String) {
                a = evaluate(variables, current.input_variables[0].str);
            } else {
                a = current.input_variables[0].number;
            }

            if (current.input_variables[1].type == InputVariable::String) {
                b = evaluate(variables, current.input_variables[1].str);
            } else {
                b = current.input_variables[1].number;
            }

            result = a << b;
            break;
        case OperationParsing::RShift:
            if (current.input_variables[0].type == InputVariable::String) {
                a = evaluate(variables, current.input_variables[0].str);
            } else {
                a = current.input_variables[0].number;
            }

            if (current.input_variables[1].type == InputVariable::String) {
                b = evaluate(variables, current.input_variables[1].str);
            } else {
                b = current.input_variables[1].number;
            }

            result = a >> b;
            break;
        case OperationParsing::Assign:
            if (current.input_variables[0].type == InputVariable::String) {
                result = evaluate(variables, current.input_variables[0].str);
            } else {
                result = current.input_variables[0].number;
            }

            break;
    }

    evaluated_values[variable] = result;
    return result;
}

int main() {
    std::string input;
    std::map<std::string, OperationParsing> variables;

    while (std::getline(std::cin, input)) {
        auto parsed_string = get_parsed_string(input);
        uint16_t a = 0, b = 0;
        variables.emplace(parsed_string.output_variable, parsed_string);
    }

    int a = evaluate(variables, "a");
    std::cout << a << std::endl;

    std::ostringstream stringStream;
    stringStream << a << " -> b";

    evaluated_values.clear();
    auto parsed_string = get_parsed_string(stringStream.str());

    variables["b"] = parsed_string;
    a = evaluate(variables, "a");
    std::cout << a << std::endl;

    return 0;
}
