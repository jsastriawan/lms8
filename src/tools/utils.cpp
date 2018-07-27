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
#include <string.h>
#include "utils.h"
#include <syslog.h>
#include <unistd.h>

std::vector<std::string> Utils::split(char const * str, char const * delim) {
	char* tok = (char*)str;
	char* ptok = tok;
	int delimLength = 0;
	std::vector<std::string> splittedStrings;
	
	do {
		if (str == NULL) {
			break;
		}

		if (delim == NULL) {
			splittedStrings.push_back(std::string(str));
			break;
		}

		delimLength = strlen(delim);
		tok = strstr(ptok, delim);
		while (tok) {
			if (ptok != tok) {
				splittedStrings.push_back(std::string(ptok, tok-ptok));
			}
			ptok = tok + delimLength;
			tok = strstr(ptok, delim);
		}

		if (ptok != str+strlen(str)) {
			splittedStrings.push_back(std::string(ptok, strlen(ptok)));
		}
	} while(0);
	return splittedStrings;
}


char* Utils::strnstr(char const* haystack, unsigned int haystackLength, char const* needle, unsigned int needleLength) {

	char* needleInHaystack = NULL;
	unsigned int  j;
	do {
		if (haystack == NULL || needle == NULL) {
			break;
		}

		for (unsigned int i = 0; i < haystackLength; i++) {
			if (haystack[i] == '\0' || ((haystackLength - i) < needleLength)) {
				break;
			}
		
			for (j = 0; j < needleLength; j++) {
				if (haystack[i + j] != needle[j]) {
					break;
				}
			}

			if (j == needleLength) {
				//Found needle in haystack
				needleInHaystack = (char*)&haystack[i];
				break;
			}
		}
	} while(0);
	return needleInHaystack;
}

std::list<CDataLen> Utils::split(char const* str, unsigned int strLength, char const* delim, unsigned int delimLength) {
        char* tok = (char*)str;
        char* ptok = tok;
        std::list<CDataLen> splittedStrings;
	CDataLen dataLen;

	do {
		if (str == NULL) {
			break;
		}

		if (delim == NULL) {
			dataLen.data = (char*)str;
			dataLen.dataLength = strLength;
			splittedStrings.push_back(dataLen);
			break;
		}

		tok = Utils::strnstr(str, strLength, delim, delimLength);
		while (tok) {
			dataLen.data = ptok;	
			dataLen.dataLength = tok-ptok;
			if (ptok!=tok) {
				splittedStrings.push_back(dataLen);
			}
			ptok = tok + delimLength;
			tok = Utils::strnstr(ptok, (str + strLength - ptok), delim, delimLength);
		}

		if (ptok != (str + strLength)) {
			dataLen.data = ptok;	
			dataLen.dataLength = str + strLength - ptok;
			splittedStrings.push_back(dataLen);
		}
	} while (0);
	return splittedStrings;
}

std::string Utils::DEFAULT_NOTIFY_CMD="export DISPLAY=:0; notify-send -u critical -t 2000 ";
std::string Utils::NOTIFY_DESKTOP_SCRIPT="/usr/local/bin/notifyDesktop.sh";
std::string Utils::NOTIFY_DESKTOP_SCRIPT1="/usr/bin/notifyDesktop.sh";

void Utils::notifyDesktop(std::string header, std::string body, bool logInSyslog) {

	std::string notifyCMD;
	
	if (! access (NOTIFY_DESKTOP_SCRIPT.c_str(), X_OK)) {
		notifyCMD = NOTIFY_DESKTOP_SCRIPT + " '" + header + "' '" + body + "'";
	} else if (! access (NOTIFY_DESKTOP_SCRIPT1.c_str(), X_OK)) {
		notifyCMD = NOTIFY_DESKTOP_SCRIPT1 + " '" + header + "' '" + body + "'";
	} else {
		notifyCMD = DEFAULT_NOTIFY_CMD + " '" + header + "' '" + body + "'"; 
	}

	if (logInSyslog) {
		syslog(LOG_INFO, "%s %s\n", header.c_str(), body.c_str());
	}

	system(notifyCMD.c_str());
}


std::string Utils::format(const char *format , ...) {
	char*   buffer        = NULL;
	int     bufferLength  = 512;
	int     _bufferLength = 0;
	va_list vl;
	std::string formattedString("");

	buffer = new char[bufferLength];
	if (buffer) {
		va_start(vl, format);

		_bufferLength = vsnprintf(buffer, bufferLength, format, vl);
		if (bufferLength <= _bufferLength) { 
			delete[] buffer;
			buffer = new char[_bufferLength + 1];
			_bufferLength = vsnprintf(buffer, _bufferLength, format, vl);
		}

		formattedString = std::string(buffer);
		va_end(vl);
		delete[] buffer;
	}

	return formattedString;
}
