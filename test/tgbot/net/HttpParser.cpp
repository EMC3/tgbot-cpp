/*
 * Copyright (c) 2015 Oleg Morozenkov
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

#include <boost/test/unit_test.hpp>

#include <tgbot/net/HttpParser.h>

#include "utils.h"

using namespace TgBot;

BOOST_AUTO_TEST_SUITE(tHttpParser)

BOOST_AUTO_TEST_CASE(generateRequest) {
	std::vector<HttpReqArg> args = { HttpReqArg("email", "test@example.com"), HttpReqArg("text", "Hello, world!") };
	std::string t = HttpParser::getInstance().generateRequest(Url("http://example.com/index.html"), args, true);
	std::string e = ""
		"POST /index.html HTTP/1.1\r\n"
		"Host: example.com\r\n"
		"Connection: keep-alive\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n"
		"Content-Length: 49\r\n"
		"\r\n"
		"email=test%40example.com&text=Hello%2C%20world%21";
	BOOST_CHECK_MESSAGE(t == e, diffS(t, e));
}

BOOST_AUTO_TEST_CASE(generateMultipartFormData) {
	std::vector<HttpReqArg> args = { HttpReqArg("email", "test@example.com"), HttpReqArg("text", "Hello, world!", true) };
	std::string boundary = HttpParser::getInstance().generateMultipartBoundary(args);
	std::string t = HttpParser::getInstance().generateMultipartFormData(args, boundary);
	std::string e = ""
		"--" + boundary + "\r\n"
		"Content-Disposition: form-data; name=\"email\"\r\n"
		"\r\n"
		"test@example.com\r\n"
		"--" + boundary + "\r\n"
		"Content-Disposition: form-data; name=\"text\"; filename=\"\"\r\n"
		"Content-Type: text/plain\r\n"
		"\r\n"
		"Hello, world!\r\n"
		"--" + boundary + "--\r\n";
	BOOST_CHECK_MESSAGE(t == e, diffS(t, e));
}

BOOST_AUTO_TEST_CASE(generateWwwFormUrlencoded) {
	std::vector<HttpReqArg> args = { HttpReqArg("email", "test@example.com"), HttpReqArg("text", "Hello, world!") };
	std::string t = HttpParser::getInstance().generateWwwFormUrlencoded(args);
	std::string e = "email=test%40example.com&text=Hello%2C%20world%21";
	BOOST_CHECK_MESSAGE(t == e, diffS(t, e));
}

BOOST_AUTO_TEST_CASE(generateResponse) {
	std::string t = HttpParser::getInstance().generateResponse("testdata");
	std::string e = ""
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/plain\r\n"
		"Content-Length: 8\r\n"
		"\r\n"
		"testdata";
	BOOST_CHECK_MESSAGE(t == e, diffS(t, e));
}

BOOST_AUTO_TEST_CASE(parseRequest) {
	std::string data = ""
		"POST /index.html HTTP/1.1\r\n"
		"Host: example.com\r\n"
		"Connection: keep-alive\r\n"
		"Content-Type: text/plain\r\n"
		"Content-Length: 8\r\n"
		"\r\n"
		"testdata";

	std::map<std::string, std::string> tHeaders;
	std::string t = HttpParser::getInstance().parseRequest(data, tHeaders);

	std::map<std::string, std::string> eHeaders = {
		{ "method", "POST" },
		{ "path", "/index.html" },
		{ "host", "example.com" },
		{ "connection", "keep-alive" },
		{ "content-type", "text/plain" },
		{ "content-length", "8" }
	};
	std::string e = "testdata";

	BOOST_CHECK_MESSAGE(t == e, diffS(t, e));
	BOOST_CHECK_MESSAGE(tHeaders == eHeaders, diff(tHeaders, eHeaders, [](const std::pair<const std::string, std::string>& item) -> std::string {
		return item.first + '=' + item.second;
	}));
}

BOOST_AUTO_TEST_CASE(parseResponse) {
	std::string data = ""
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/plain\r\n"
		"Content-Length: 8\r\n"
		"\r\n"
		"testdata";

	std::map<std::string, std::string> tHeaders;
	std::string t = HttpParser::getInstance().parseResponse(data, tHeaders);

	std::map<std::string, std::string> eHeaders = {
		{ "status", "200" },
		{ "content-type", "text/plain" },
		{ "content-length", "8" }
	};
	std::string e = "testdata";

	BOOST_CHECK_MESSAGE(t == e, diffS(t, e));
	BOOST_CHECK_MESSAGE(tHeaders == eHeaders, diff(tHeaders, eHeaders, [](const std::pair<const std::string, std::string>& item) -> std::string {
		return item.first + '=' + item.second;
	}));
}

BOOST_AUTO_TEST_SUITE_END()
