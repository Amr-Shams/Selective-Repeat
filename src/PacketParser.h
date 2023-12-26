//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef PACKETPARSER_H_
#define PACKETPARSER_H_
#include <vector>
#include <string>

#include "PacketMetaData.h"

class PacketParser {
public:
   explicit PacketParser(const std::string &fileName); // why explicit? explicit keyword is used to avoid unintentional implicit conversions
   PacketMetaData* getNextPacketMetaData();
   bool checkForPackets() const;
    virtual ~PacketParser();
private:
    PacketMetaData* nextPacketMetaData();
    std::vector<PacketMetaData*> inputMessages;
    size_t currentMessageIndex = 0;
};

#endif /* PACKETPARSER_H_ */
