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
#include "miniXmlParser.h"
#include "utils.h"
#include <string.h>
#include <list>
#include <stack>
#include "types.h"

MiniXmlParser::MiniXmlParser() {
	rootNode = NULL;
}

MiniXmlParser::~MiniXmlParser() {
	if (rootNode) {
		deleteXmlTree(rootNode);
		rootNode = NULL;	
	}
}

void MiniXmlParser::deleteXmlTree(XMLNode* rootNode) {
	XMLNode* node     = rootNode;
	XMLNode* tempNode = NULL;

	while (node != NULL) {
		tempNode = node->childNode;
		delete node;
		node = tempNode;
	}
}

int MiniXmlParser::validateXML(XMLNode const* rootNode) {
	int rc = 0;
	XMLNode* current = (XMLNode *)rootNode;
	XMLNode* temp    = NULL;
	std::stack<XMLNode*> tagStack;

	while (current != NULL) {
		if (current->tagName == NULL) { 
			PRINT("ValidateXML failed, foung a empty tag\n");
			rc = -1;
			break;
		}

		if (memcmp(current->tagName, "!", 1) == 0) {
			temp = current;
			current = tagStack.empty()?NULL:tagStack.top();
			if (current != NULL) {
				current->childNode = temp->childNode;
			} else {
				current = temp;
			}
		} else if (current->startTag) {
			current->parentNode = tagStack.empty()?NULL:tagStack.top();
			tagStack.push(current);
		} else {
			if (tagStack.empty() == false) {
				temp = tagStack.top(); 
				tagStack.pop(); 
			} else {
				temp = NULL;
			}
			if (temp != NULL) {
				if (temp->tagLength == current->tagLength && memcmp(temp->tagName, current->tagName, current->tagLength) == 0) {
					if (current->childNode != NULL) {
						if (current->childNode->startTag != 0) {
							temp->siblingNode = current->childNode;
						}
					}
					temp->closingTag = current;
					current->startingTag = temp;
				} else {
					PRINT("ValidateXML failed, Illegal tag\n");
					rc = -1;
					break;
				}
			} else {
				PRINT("ValidateXML failed, Illegal closing tag\n");
				rc = -1;
				break;
			}
		}
		current = current->childNode;
	}

	if (tagStack.empty() == false) {
		PRINT("ValidateXML failed, Incomplete XML\n");
		rc = -1;
	}

	return rc;
}

int MiniXmlParser::parse(char* buffer, unsigned int bufferLength) {
	int      validXml  = -1;
	XMLNode* node      = NULL;

	node = _parse(buffer, bufferLength);
	if (node) {
		validXml = validateXML(node);
	}
	rootNode = node;
	return validXml;
}

XMLNode* MiniXmlParser::_parse(char const* buffer, unsigned int bufferLength) {

	char* tagName      = NULL;
	char* nsTag        = NULL;
	char* CommentEnd   = NULL;

	int   tagLength    = 0;
	int   startTag     = 0;
	int   emptyTag     = 0;
	int   nsLength     = 0;
	int   i            = 0;
	int   CommentIndex = 0;

	std::list<CDataLen> xmlFields;
	std::list<CDataLen> temp2;
	std::list<CDataLen> tagValue;

	XMLNode *rootNode = NULL;;
	XMLNode *current  = NULL;
	XMLNode *newNode  = NULL;
	std::list<CDataLen>::iterator it;

	if (buffer == NULL || bufferLength == 0) {
		return NULL; 
	}

	xmlFields = Utils::split(buffer, bufferLength, "<", 1);
	for (CDataLen xmlField: xmlFields) {
		if (xmlField.dataLength != 0 && memcmp(xmlField.data, "?", 1) != 0 && (xmlField.data > CommentEnd)) {
			/*Parse XML comments and ignore it.*/
			if (xmlField.dataLength > 3 && memcmp(xmlField.data, "!--", 3)==0) {
				CommentIndex = 3;
				while (((xmlField.data + CommentIndex) < (buffer + bufferLength)) && memcmp(xmlField.data + CommentIndex, "-->", 3) != 0) {
					CommentIndex++;
				}
				CommentEnd = xmlField.data + CommentIndex;
				continue;
			} else {
				emptyTag = 0;
				/*if the first char is / after < then its ending tag, otherwise starting tag. ("</....") */
				if (memcmp(xmlField.data, "/", 1) == 0) {
					startTag = 0;
					xmlField.data = xmlField.data + 1;
					xmlField.dataLength -= 1;
					temp2 = Utils::split(xmlField.data, xmlField.dataLength, ">", 1);
				} else {
					
					startTag = 1;
					temp2 = Utils::split(xmlField.data, xmlField.dataLength, ">", 1);
					if (temp2.front().dataLength > 0 && *(char*)(temp2.front().data-1) == '/') {
						//".../>"  are empty tags
						emptyTag = 1;
					}
				}
			}
			/*split on ":" to get namespace:tagName*/
			tagValue = Utils::split(temp2.front().data, temp2.front().dataLength, ":", 1);
			if (tagValue.size() == 1) {
				nsTag = NULL;
				nsLength = 0;
				tagName = tagValue.front().data;
				tagLength = tagValue.front().dataLength;
			} else {
				it = tagValue.begin();
				nsTag = it->data;
				nsLength = it->dataLength;
				it++;
				tagName = it->data;
				tagLength = it->dataLength;
			}
			tagValue.clear();
			temp2.clear();

			/*Parse for multiple ns:tags and recompute the first tagLength*/
			for(i=0; i<tagLength; i++) {
				if ((tagName[i] == ' ')||(tagName[i] == '/')||(tagName[i] == '>')||(tagName[i] == '\t')||(tagName[i] == '\r')||(tagName[i] == '\n')) {
					if (i != 0) {
						if (tagName[i]=='/') {
							emptyTag = 1;
						}
						tagLength = i;
						break;
					}
				}
			}

			/*Create XML Node, populate properties and add it to the list*/
			if (tagLength != 0) {
				newNode = new XMLNode();	
				newNode->tagName = tagName;
				newNode->tagLength = tagLength;
				newNode->startTag = startTag;
				newNode->nsTag = nsTag;
				newNode->nsLength = nsLength;				


				if (rootNode == NULL) {
					rootNode = newNode;
				}
				else {
					current->childNode = newNode;
				}
				current = newNode;

				if (emptyTag) {
					newNode = new XMLNode();	
					newNode->tagName = tagName;
					newNode->tagLength = tagLength;
					newNode->nsTag = nsTag;
					newNode->nsLength = nsLength;

					current->emptyTag = 1;
					current->childNode = newNode;
					current = newNode;
				}
			}

		}
	}

	xmlFields.clear();
	return rootNode;
}

/*
 * Parse the XML Tree from rootNode and retrive value of a given key.
 * If rootNode is passed as NULL, parsing resumes from last key retrieved node.
 * Return 0 on Success , -1 otherwise.
 * Inputs : XMLNode *rootNode, char *tag, unsigned int tagLen, char *ns, unsigned int nsLen
 * Outputs: char** value, unsigned int *valueLen 
 */
int MiniXmlParser::getXmlTagValue(XMLNode const* rootNode, char const* tag, unsigned int tagLen, char const* ns, unsigned int nsLen, char** value, unsigned int *valueLen)
{

	static XMLNode *cur    = (XMLNode*) rootNode;
	static XMLNode *pcur   = cur;
	char           *pValue = NULL;
	bool           found   = false;

	if (tag == NULL) {
		return -1;
	}

	if (rootNode != NULL) {
		cur  = (XMLNode *) rootNode;
		pcur = cur;
	}

	while (cur != NULL) {
		while (pcur != NULL) {
			if (pcur->closingTag && memcmp((pcur->tagName), tag, tagLen) == 0) {
				if (ns) {
					if (memcmp(pcur->nsTag, ns, pcur->nsLength) == 0) {
						found = true;
					}
				} else {
					found = true;
				}

				if (found) {
					pValue = strstr(pcur->tagName, ">") + 1;
					if (pcur->closingTag->nsLength) {
						*valueLen = pcur->closingTag->nsTag - pValue - 2;
					} else {
						*valueLen = pcur->closingTag->tagName - pValue - 2;
					}
					*value = pValue;
					pcur = pcur->childNode;
					return 0;
				}
			}
			pcur = pcur->childNode;
		}
		cur = cur->siblingNode;
		pcur = cur;
	}

	return -1;
}

/* Returns Namespace prefix of given URI namespace
 * Inputs : XMLNode *node, char *uri, unsigned int uriLen
 * Outputs: char **nsPrefix, unsigned int *nsPrefixLen
 */
int MiniXmlParser::getNSPrefix(XMLNode const* node, char const* uri, unsigned int uriLen, char **nsPrefix, unsigned int *nsPrefixLen) {

	bool foundNS = false;;
	char *tagEnd = NULL;
	int  rc      = 0;
	CDataLen tempNS;
	CDataLen tempURI;
	std::list<CDataLen> tags;
	std::list<CDataLen> temp;
	std::list<CDataLen> temp2;
	std::list<CDataLen>::iterator it;

	if (node == NULL || uri == NULL) {
		rc = -1;
		return rc;
	}

	tagEnd = strstr(node->tagName, ">");
	if (tagEnd && nsPrefix != NULL && nsPrefixLen != NULL) {
		tags = Utils::split(node->tagName, tagEnd - node->tagName, " ", 1);
		for (CDataLen tag: tags) {
			temp = Utils::split(tag.data, tag.dataLength, ":", 1);
			if (temp.size() >= 2) {
				it = temp.begin();
				tempNS.data = it->data;
				tempNS.dataLength = it->dataLength;
				it++;
				
				if (memcmp(tempNS.data, "xmlns", 5) == 0) {
					temp2 = Utils::split(it->data, it->dataLength, "=", 1);
					if (temp2.size() >= 2) {
						it = temp2.begin();
						tempNS.data = it->data;
						tempNS.dataLength = it->dataLength;
						it++;
					}
				}
				//Ignore if first character is " or ' 
				if (it->data[0] == 34 || it->data[0] == 39) {
					it->data = it->data + 1;
				}

				if (memcmp(it->data, uri, uriLen) == 0) {
					foundNS = true;
					break;
				}
			}
		}
	} else {
		rc = -1;
	}
	
	if (rc == 0 && foundNS) {
		*nsPrefix = tempNS.data;
		*nsPrefixLen = tempNS.dataLength;
	}
	
	return rc;
}
