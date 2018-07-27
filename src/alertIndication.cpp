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
#include "alertIndication.h"
#include <string.h>

const char* AlertIndication::CLASS_URI = "http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/CIM_AlertIndication";
void AlertIndication::initAlertIndication(char *ns, unsigned int nsLen) {
	
	char *value          = NULL;
	unsigned int valueLen= 0;

	if (xmlParser.getXmlTagValue(xmlParser.getRootNode(), "MessageID", strlen("MessageID"), ns, nsLen, &value, &valueLen) == 0) {
		messageID.data = value;
		messageID.dataLength = valueLen;
	}

	if (xmlParser.getXmlTagValue(xmlParser.getRootNode(), "MessageArguments", strlen("MessageArguments"), ns, nsLen, &value, &valueLen) == 0) {
		messageArguments.data = value;
		messageArguments.dataLength = valueLen;
	}

	if (xmlParser.getXmlTagValue(xmlParser.getRootNode(), "IndicationTime", strlen("IndicationTime"), ns, nsLen, &value, &valueLen) == 0) {
		if (xmlParser.getXmlTagValue(NULL, "Datetime", strlen("Datetime"), NULL, 0, &value, &valueLen) == 0) {
			indicationTime.data = value;
			indicationTime.dataLength = valueLen;
		}
	}
}

int AlertIndication::initFromXml(char *buffer, unsigned int bufferLen) {

	char *nsPrefix    = NULL;
	int   rc          = 0;
	unsigned int nsPrefixLen = 0;

	do {
		if (buffer == NULL || bufferLen == 0) {
			rc = -1;
			break;
		}

		if (xmlParser.parse(buffer, bufferLen)) {
			rc = -1;
			break;
		}

		if (xmlParser.getNSPrefix(xmlParser.getRootNode(), (char*)CLASS_URI, CLASS_URI_LEN, &nsPrefix, &nsPrefixLen)) {
			rc = -1;
			break;
		}
	
		initAlertIndication(nsPrefix, nsPrefixLen);
		
	} while(0);

	return rc;
}

CDataLen AlertIndication::getMessageArguments() { return messageArguments; };
CDataLen AlertIndication::getIndicationTime() { return indicationTime; };
CDataLen AlertIndication::getMessageID() { return messageID; };

