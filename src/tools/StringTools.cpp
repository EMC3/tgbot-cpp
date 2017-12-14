/*
 * Copyright (c) 2015 Oleg Morozenkov
 * Copyright (c) 2017 Maks Mazurov (fox.cpp)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "tgbot/tools/StringTools.h"

#include <stdlib.h>
#include <iomanip>
#include <stdio.h>

namespace StringTools {

bool startsWith(const std::string& str1, const std::string& str2) {
	if (str1.length() < str2.length()) {
		return false;
	}
	std::string::const_iterator it1(str1.begin());
	std::string::const_iterator end1(str1.end());
	std::string::const_iterator it2(str2.begin());
	std::string::const_iterator end2(str2.end());
	while (it1 != end1 && it2 != end2) {
		if (*it1 != *it2) {
			return false;
		}
		++it1;
		++it2;
	}
	return true;
}

bool endsWith(const std::string& str1, const std::string& str2) {
	if (str1.length() < str2.length()) {
		return false;
	}
	std::string::const_iterator it1(str1.end());
	std::string::const_iterator begin1(str1.begin());
	std::string::const_iterator it2(str2.end());
	std::string::const_iterator begin2(str2.begin());
	--begin1;
	--begin2;
	while (it1 != begin1 && it2 != begin2) {
		if (*it1 != *it2) {
			return false;
		}
		--it1;
		--it2;
	}
	return true;
}

void split(const std::string& str, char delimiter, std::vector<std::string>& dest) {
	std::stringstream stream(str);
	std::string s;
	while (getline(stream, s, delimiter)) {
		dest.push_back(s);
	}
}

std::string generateRandomString(size_t length) {
	static const std::string chars("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890-=[]\\;',./!@#$%^&*()_+{}|:\"<>?`~");
	static const size_t charsLen = chars.length();
	std::string result;
	for (size_t i = 0; i < length; ++i) {
		result += chars[rand() % charsLen];
	}
	return result;
}


std::string urlEncode(const std::string& value, const std::string& additionalLegitChars) {
	static const std::string legitPunctuation = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_.-~:";
	std::stringstream ss;
	for (auto const &c : value) {
		if ((legitPunctuation.find(c) == std::string::npos)
			&& (additionalLegitChars.find(c)==std::string::npos)) {
			ss << '%' << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)(unsigned char)c;
		} else {
			ss << c;
		}
	}

	return ss.str();
}

std::string urlDecode(const std::string& value) {
	std::string result;
	for (size_t i = 0, count = value.length(); i != count; ++i) {
		const char c = value[i];
		if (c == '%') {
			int t = 0;
			sscanf(value.substr(i + 1, 2).c_str(), "%x", &t);
			result += (char) t;
			i += 2;
		} else {
			result += c;
		}
	}
	return result;
}

}
