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

#include "PacketParser.h"
#include <fstream>


PacketParser::PacketParser(const std::string &fileName) {
    // TODO Auto-generated constructor stub
    std::vector<std::string> lines;
    std::string line;
    std::ifstream file(fileName);
    while (getline(file, line))
        lines.push_back(line);
    file.close();
    
    for (const std::string &line : lines)
        inputMessages.push_back(new PacketMetaData(line));

}
PacketMetaData* PacketParser::getNextPacketMetaData()
{
    if (checkForPackets())
        return nextPacketMetaData();
    else
        return nullptr;
}
bool PacketParser::checkForPackets() const
{
    return currentMessageIndex < inputMessages.size();
}
PacketMetaData* PacketParser::nextPacketMetaData()
{
    return inputMessages[currentMessageIndex++];
}
PacketParser::~PacketParser() {
    // TODO Auto-generated destructor stub
}

