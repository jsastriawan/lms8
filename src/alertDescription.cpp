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
#include "alertDescription.h"
#include "miniXmlParser.h"
#include <sstream>
#include <fstream>
#include "defaultAlerts.h"
#include "types.h"

bool AlertDescription::classInited = false;
std::string AlertDescription::alertXmlFile = "/usr/local/share/xml/AMTAlerts.xml";
std::string AlertDescription::alertXmlFile1 = "/usr/share/xml/AMTAlerts.xml";
std::map<std::string,std::string> AlertDescription::alertDescriptionMap;

void AlertDescription::initAlertDescription() {

	char               *value       = NULL;
	unsigned int       valueLength  = 0;
	bool               fromFile     = false;
	std::string        alertIdArg;
	std::stringstream  ss;
	std::string        xmlData;
	CDataLen           id;
	CDataLen           arg; 
	CDataLen           description;
	MiniXmlParser      xmlParser;
	std::list<CDataLen>defaultAlertsList;
	std::list<CDataLen>::iterator it;

	do {
		if (classInited) {
			break;
		}

		std::ifstream is(alertXmlFile, std::ifstream::in);
		if (is.good()) {
			ss << is.rdbuf();
			xmlData = ss.str();
			fromFile = true;
		} else {
			std::ifstream _is(alertXmlFile1, std::ifstream::in);
			if (_is.good()) { 
				ss << _is.rdbuf();
				xmlData = ss.str();
				fromFile = true;
			} 
			_is.close();
		}
		is.close();

		/* Parse alert descriptions from xml file, if file is absent use the default ones  */
		if (fromFile) {
			/* From xml file */
			if (xmlParser.parse((char*)xmlData.c_str(), xmlData.size()) == 0) {
				/* Process alert xml of form
				 * <Alerts><Alert><Id>iAMT0052</Id><Arg>1</Arg></Alert> <Alert>...</Alert> ...<Alerts> 
				 */
				if (xmlParser.getXmlTagValue(xmlParser.getRootNode(), "Alerts", 6, NULL, 0, &value, &valueLength) == 0 ) {
					while (xmlParser.getXmlTagValue(NULL, "Alert", 5, NULL, 0, &value, &valueLength) == 0) { 
						xmlParser.getXmlTagValue(NULL, "Id", 2, NULL, 0, &value, &valueLength);
						id.data = value;
						id.dataLength = valueLength;
	
						xmlParser.getXmlTagValue(NULL, "Arg", 3, NULL, 0, &value, &valueLength);
						arg.data = value;
						arg.dataLength = valueLength;
	
						alertIdArg = std::string(id.data, id.dataLength) + "-" + std::string(arg.data, arg.dataLength);

						xmlParser.getXmlTagValue(NULL, "Message", 7, NULL, 0, &value, &valueLength);
						alertDescriptionMap.insert(std::pair<std::string, std::string>(alertIdArg, std::string(value, valueLength)));
					}
					classInited = true;
				}
			} else {
				PRINT("Failed to parse XML\n");
			}
		} else {
			/* Using default XML alerts descriptions */
			defaultAlertsList = Utils::split(DEFAULT_ALERTS , DEFAULT_ALERTS_LENGTH , ";", 1);
			for (CDataLen alert: defaultAlertsList) {
				std::list<CDataLen> alertIdDescription = Utils::split(alert.data, alert.dataLength, ":", 1);
				if (alertIdDescription.size() >= 2) {
					it = alertIdDescription.begin();
					id.data = it->data;
					id.dataLength = it->dataLength;
					it++;
					description.data = it->data;
					description.dataLength = it->dataLength;
					/* Add to std::map for faster retreival */ 
					alertDescriptionMap.insert(std::pair<std::string, std::string>(std::string(id.data, id.dataLength), 
											std::string(description.data, description.dataLength)));
				}
			}
			classInited = true;
		}
	} while(0);
}
	

std::string AlertDescription::getAlertDescription(std::string alert) { 
	CDataLen alertDescription;
	std::map<std::string, std::string>::iterator it;
	
	if (classInited == false) {
		initAlertDescription();
	}
	
	if (classInited && alertDescriptionMap.empty() == false) {
 		it = alertDescriptionMap.find(alert);
		if (it != alertDescriptionMap.end()) {
			return it->second;
		}
	}

	return "";
};
