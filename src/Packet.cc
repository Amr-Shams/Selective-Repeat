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

#include "Packet.h"
#include "PayLoadStuffer.h"
#include <string>
#include <bitset>
Packet::Packet(PacketMetaData *packetMetaData, int sequenceNumber){
    // TODO Auto-generated constructor stub
    this->metaData = packetMetaData;
    this->sequenceNumber = sequenceNumber;
    this->myMessage = new Msg_Base();
    this->myMessage->setSequenceNumber(sequenceNumber);
    this->myMessage->setFrameType("DATA");
    std::string inputPayload = packetMetaData->getPayload();
    // stuff the payload with 0x7d for 0x7e and 0x7d
    std::string stuffedPayload = PayLoadStuffer::stuff(inputPayload);
    // calculate the parity bit
    std::bitset<8> parity(0);
    for (const auto &character : stuffedPayload)
        parity ^= std::bitset<8>(character);

    
    // check if the packet has a modification error
    if (packetMetaData->hasModificationError())
        packetMetaData->modifiedBitPosition = Packet::modifyRandomBit(stuffedPayload);
    // set the paylaod and the trailer
    this->myMessage->setTrailer(parity.to_string().c_str());
    this->myMessage->setPayload(stuffedPayload.c_str());

}

int Packet::modifyRandomBit(std::string &payload){
    // TODO Auto-generated destructor stub
    // convert the payload to a bitset
    std::vector<std::bitset<8>> bitRepresentation;
    for (auto &c : payload)
        bitRepresentation.emplace_back(c);
    // generate a random byte index and bit index
    srand(time(NULL));
    size_t randomByteIndex = rand() % bitRepresentation.size();
    size_t randomBitIndex = rand() % 8;
    // flip the bit
    bitRepresentation[randomByteIndex].flip(randomBitIndex);
    // convert the bitset back to a string
    payload = "";
    for (int i = 0; i < bitRepresentation.size(); i++)
        payload += (char) (bitRepresentation[i].to_ulong());
    // return the position of the modified bit
    return 8 * randomByteIndex + randomBitIndex;
}