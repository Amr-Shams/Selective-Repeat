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

#include "Cordinate.h"
#include "msg_m.h"
#include "config.h"
Define_Module(Cordinate);

void Cordinate::initialize()
{
    // TODO - Generated method body
    inputFile = std::string(par("inputFile").stringValue());
    cordinateConfig = new config(inputFile);
    // init a msg 
    Msg_Base* initialMsg = new Msg_Base();
    initialMsg->setFrameType("INITIAL");
    initialMsg->setPayload(std::to_string(cordinateConfig->getStartingTime()).c_str());

    if (cordinateConfig->getNodeID() == 0)
        send(initialMsg, "out0");
    else
        send(initialMsg, "out1");
}

void Cordinate::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}
