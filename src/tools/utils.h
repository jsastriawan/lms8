/*******************************************************************************
 * Copyright (C) 2017 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  - Neither the name of Intel Corporation. nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL Intel Corporation. OR THE CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************/

#ifndef __UTILS_H
#define __UTILS_H
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdarg>

class CDataLen {
	public:
	char* data;
	int dataLength;
	CDataLen() { data = NULL; dataLength = 0; };
};

class Utils {
	public:
	static std::string NOTIFY_DESKTOP_SCRIPT;
	static std::string NOTIFY_DESKTOP_SCRIPT1;
	static std::string DEFAULT_NOTIFY_CMD;
	static std::vector<std::string> split(char const* str, char const * delim);
	static std::list<CDataLen> split(char const* str, unsigned int strLength, char const* delim, unsigned int delimLength);
	static char* strnstr(char const* haystack, unsigned int haystackLength, char const* needle, unsigned int needleLength);
	static void notifyDesktop(std::string header, std::string body, bool logInSyslog); 
	static std::string format(const char *format , ...);
};
#endif
