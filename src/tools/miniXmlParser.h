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
#ifndef _MINIXMLPARSER_H
#define _MINIXMLPARSER_H
#include <iostream>
#include "xmlNode.h"

class MiniXmlParser {
	public:
	MiniXmlParser();
	~MiniXmlParser();
	int parse(char* buffer, unsigned int bufferLength);
	XMLNode* getRootNode() { return rootNode; };
	int getXmlTagValue(XMLNode const* rootNode, char const *tag, unsigned int tagLen, char const* ns, unsigned int nsLen, char** value, unsigned int *valueLen);
	int getNSPrefix(XMLNode const* nonde, char const* uri, unsigned int uriLen, char **nsPrefix, unsigned int *nsPrefixLen);

	private:
	XMLNode* rootNode;
	XMLNode* _parse(char const* buffer, unsigned int bufferLength);
	/* Validates if the XML is well formed and sets up parent sibling pointers */
	int validateXML(XMLNode const* rootNode);
	void deleteXmlTree(XMLNode *root);
};
#endif
