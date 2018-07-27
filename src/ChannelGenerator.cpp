/*******************************************************************************
 * Copyright (C) 2004-2011 Intel Corporation. All rights reserved.
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "ChannelGenerator.h"

unsigned int ChannelGenerator::GenerateChannel()
{
  unsigned int ret_channel = ILLEGAL_CHANNEL;
  
  if(_takenChannels.size() > _maxChannel - 1)
    return  ret_channel;

  while (_takenChannels.find(_nextFreeChannel) != _takenChannels.end())
    _nextFreeChannel++;
 
  
  ret_channel = _nextFreeChannel++;
  
  if (_nextFreeChannel == _maxChannel)
    _nextFreeChannel = 1;

  _takenChannels.insert(ret_channel);

  return ret_channel;
}


bool ChannelGenerator::FreeChannel(unsigned int channel)
{
  if(_takenChannels.find(channel) == _takenChannels.end())
    return false;

  _takenChannels.erase(channel);

  return true;
}

void ChannelGenerator::Reset()
{
  _takenChannels.clear();
  _nextFreeChannel = 1;
}
