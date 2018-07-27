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
#include "httpParser.h"
#include "utils.h"
#include "types.h"

int HttpParser::parse(char *buffer) {

	std::vector<std::string> headerBody;
	std::vector<std::string> header;
	int rc = 0;
	do {
		if (buffer == NULL) {
			rc = -1;
			break;
		}

		headerBody = Utils::split(buffer, "\r\n\r\n"); 
		if (headerBody.size() < 2)
		{
			PRINT("Failed to process httpHeader\n");
			rc = -1;
			break;
		}

		/* Entries in Header are seperated by \r\n */
	 	header = Utils::split((char*)headerBody[0].c_str(), "\r\n");

		/* First line in header is the the header line
		 * e.g. POST <path> HTTP/1.1
		 * e.g  GET <path> HTTP/1.1
		 */
		headerLine = header[0];

		/* After headerline are the Fields
		 * e.g Content-Length:2204
		 */
		for (unsigned int i=1; i< header.size(); i++) {
			std::vector<std::string> field = Utils::split((char*)header[i].c_str(), ":");
			if (field.size() < 2) {
				rc = -1;
				break;
			}
			headerFields.insert(std::pair<std::string, std::string>(field[0], field[1]));
		}

		if (rc) break;	

		body = headerBody[1];
	} while(0);

	return rc;
}

std::string HttpParser::getHeaderLine() {
	return headerLine;
}

std::string HttpParser::getHeaderField(std::string field) {
	std::map<std::string,std::string>::iterator it;
	std::string fieldValue = ""; 
 
	it = headerFields.find(field);
	if (it != headerFields.end())
	{
		fieldValue = it->second;
	}

	return fieldValue;
}

std::string HttpParser::getBody() {
	return body;
}
