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

#ifndef PACKET_H_
#define PACKET_H_
#include "msg_m.h"
#include "PacketMetaData.h"
class Packet {
public:
    Packet(PacketMetaData *packetMetaData, int sequenceNumber);
    Msg_Base *myMessage { nullptr };
    PacketMetaData *metaData { nullptr };
    Msg_Base *timeOut { nullptr };
    int sequenceNumber { -1 };
    int modifyRandomBit(std::string &payload);
};

#endif /* PACKET_H_ */
