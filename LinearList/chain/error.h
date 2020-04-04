#pragma once
#include <iostream>
#include <string>
void error(std::string s);
void error(std::string s1, std::string s2);
void error(std::string s) { throw std::runtime_error(s); };
void error(std::string s1, std::string s2) { error(s1 + s2); };
