/*
The MIT License (MIT)

Copyright (c) 2019 RT-EGG.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#pragma once

#include <stdexcept>

class FileReadError : public std::runtime_error
{
public:
	FileReadError(const std::string& in_file_path)
		: std::runtime_error("read file \"" + in_file_path + "\" error.")
	{
		return;
	}
};

class ParseError : public std::runtime_error
{
public:
	ParseError(void)
		: std::runtime_error("parse error.")
	{
		return;
	}
};

class ValueOfNullElementError : public std::runtime_error
{
public:
	ValueOfNullElementError(const std::string& in_value_name)
		: std::runtime_error("read value \"" + in_value_name + "\" despite current element is not assigned.")
	{
		return;
	}
};

class EndOfNullElementError : public std::runtime_error
{
public:
	EndOfNullElementError(const std::string& in_end_name)
		: std::runtime_error("read end of element named \"" + in_end_name + "\" despite current element is not assigned.")
	{
		return;
	}
};

class EndOfInvalidElementError : public std::runtime_error
{
public:
	EndOfInvalidElementError(const std::string& in_current_element_name, const std::string& in_end_name)
		: std::runtime_error("read end of element named \"" + in_end_name + "\" despite current element is \"" + in_current_element_name + "\".")
	{
		return;
	}
};