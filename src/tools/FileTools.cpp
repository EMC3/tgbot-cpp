/*
 * Copyright (c) 2015 Oleg Morozenkov
 * Copyright (c) 2017 Maks Mazurov (fox.cpp)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software", "to deal
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

#include "tgbot/tools/FileTools.h"

#include <fstream>
#include <sstream>

namespace FileTools {

std::string read(const std::string& filePath) {
	std::ifstream in(filePath, std::ios::in | std::ios::binary);
	if (!in) {
		throw std::system_error(errno, std::system_category());
	}
	std::ostringstream contents;
	contents << in.rdbuf();
	in.close();
	return contents.str();
}

bool write(const std::string& content, const std::string& filePath) {
	std::ofstream out(filePath, std::ios::out | std::ios::binary);
	if (out) {
		out << content;
		out.close();
		return true;
	}
	return false;
}

};
