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

#include "PacketMetaData.h"

PacketMetaData::PacketMetaData(const std::string &line) {
    // TODO Auto-generated constructor stub
    errorCode = line.substr(0, LENGTH_OF_ERROR_CODE);
    payload = line.substr(BEGIN_OF_PAYLOAD); //To the end of the line.
}

PacketMetaData::~PacketMetaData() {
    // TODO Auto-generated destructor stub
    // deonstructor
}

