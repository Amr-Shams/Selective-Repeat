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

#include "Node.h"
#include <bitset>
Define_Module(Node);

void Node::initialize()
{
    // TODO - Generated method body
    this->windowSize = par("windowSize").intValue();
    this->timerDuration = par("timerDuration").doubleValue();
    this->messageDelayTime = par("messageDelayTime").doubleValue();
    this->messageProcessingTime = par("messageProcessingTime").doubleValue();
    this->inputFile = std::string(par("inputFile").stringValue());
    this->outputFile = std::string(par("outputFile").stringValue());
    this->id = par("id").intValue();
    this->lossRate = par("lossRate").doubleValue();
    this->logFile = std::ofstream(outputFile, std::ofstream::out | std::ofstream::trunc);
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    Msg_Base *arrivedMsg = check_and_cast<Msg_Base*>(msg);
    // check the msg for receiver or sender
    if(isMsgForReceiver(arrivedMsg))
        handleMsgAsReceiver(arrivedMsg);
    else
        handleMsgAsSender(arrivedMsg);

}

void Node::finish()
{
    // TODO - Generated method body
    this->logFile.close();
}
bool Node::isMsgForReceiver(Msg_Base *msg)
{
    return !strcmp(msg->getFrameType(), "DATA");
}

void Node::handleMsgAsReceiver(Msg_Base *msg)
{
    // TODO - Handle the arrived msg as receiver
   // construct a response (msg)
   Msg_Base *response = new Msg_Base();
   // increase the simulation time by the processing time
   Node::increaseSimulationTimeBy(this->messageProcessingTime);
   // check if it is expected
   if(isExpectedMsg(msg)){
    // check if it is corrupted
    if(isMsgCorrupted(msg)){
        // send NACK
        response->setFrameType("NAK");
        response->setSequenceNumber(msg->getSequenceNumber());
   
   }
   else{
    // store it in the buffer if the window is not full
    if (Node::isWindowFull()){
        // write to the log file all the Msg_Base in the window
        for (int i = 0; i < this->RecWindow.size(); i++)
            logFile << "At time[" << simTime() << "], Node[" << id << "] Sending [" << this->RecWindow[i].getFrameType() << "] with number[" << this->RecWindow[i].getSequenceNumber() << "], loss[" << "NO" << "]"
                    << std::endl;
        // clear the window
        this->RecWindow.clear();
    }
    // add it to the window
    this->RecWindow.push_back(*msg);
    // send ACK
    response->setFrameType("ACK");
    response->setSequenceNumber(msg->getSequenceNumber());
  
    }
   }
   else{
    // send NACK
    response->setFrameType("NAK");
    response->setSequenceNumber(msg->getSequenceNumber());
   
    // store it in the buffer if it is not corrupted
    if(!isMsgCorrupted(msg)&&!Node::isWindowFull())
       {
        
        // add it to the window
        this->RecWindow.push_back(*msg);
       }
    else{
        // drop it
        delete msg;
    }
   }
   // get the random number
    double random = par("random").doubleValue();
    // check if the msg is lost
    if(random >= this->lossRate){
        // send the response
        send(response, "out");
    }
    else{
        // drop the response
        // write to the log file
        logFile << "At time[" << simTime() << "], Node[" << id << "] Sending [" << response->getFrameType() << "] with number[" << response->getSequenceNumber() << "], loss[" << "YES" << "]"
                << std::endl;
        delete response;
    }
}

bool Node::isExpectedMsg(Msg_Base *msg)
{
    // TODO - Generated method body
    return msg->getSequenceNumber() == this->RecWindow.front().getSequenceNumber();
}
bool Node::isMsgCorrupted(Msg_Base *msg)
{
    // TODO - Generated method body
    // calc the parity of the msg
    // compare it with the parity of the msg
    // return true if they are not equal
    std::bitset<8> parity(0);
    // get the payload
    std::string payload = msg->getPayload();
    // loop over the payload
    for (int i = 0; i < payload.length(); i++)
        parity ^= std::bitset<8>(payload[i]);
    // get the trailer
    std::bitset<8> trailer(msg->getTrailer());
    return parity != trailer;
}

void Node::increaseSimulationTimeBy(double duration)
{
    // TODO - Generated method body
    this->getSimulation()->setSimTime(simTime() + duration);
}

void Node::handleMsgAsSender(Msg_Base *msg)
{

    // check if it is the intial msg
    if(strcmp(msg->getFrameType(),"INITIAL")==0){
        // this is the initial msg
        double startingTime = std::stod(msg->getPayload());
        // increase the simulation time by the starting time
        Node::increaseSimulationTimeBy(startingTime);
        // create the input file parser
        this->packetParser = new PacketParser(this->inputFile);
        // check if there are more packets in the input file
        while (packetParser->checkForPackets() && !Node::isWindowFull())
            SaveThePackt();
    }
    else if(strcmp(msg->getFrameType(),"TIMEOUT")==0){
        // this is the timeout msg
        // get the sequence number
    logFile << "Time out event at time [" << simTime() << "], at Node[" << id << "] for frame with seq_num=[" << msg->getSequenceNumber() << "]" << std::endl;
       // get the packet from the window the sequence number
        Packet packet = this->SenderWindow[msg->getSequenceNumber()];
        // resend this packet
        sendPacket(packet);
    }
    else if(strcmp(msg->getFrameType(),"ACK")==0){
        // this is the ack msg
        if(isExpectedMsg(msg)){
           unsetTimerOnPacket(this->SenderWindow.front());
              SenderWindow.pop_front();
                if (this->packetParser->checkForPackets() && !Node::isWindowFull())
                    SaveThePackt();
        }
    }
    else{
        // this is the nack msg
        // get the sequence number
        int sequenceNumber = msg->getSequenceNumber();
        // get the packet from the window
        Packet packet = this->SenderWindow[sequenceNumber];
        // send the packet
        sendPacket(packet);
    }
}

Packet Node::constructNextPacket()
{
    // TODO - Generated method body
    // get the next packet from the input file
    PacketMetaData *packetMetaData = this->packetParser->getNextPacketMetaData();
    // create the packet
    logFile << "At time [" << simTime() << "], Node[" << id << "], Introducing channel error with code = [" << packetMetaData->getErrorCode() << "] ." << std::endl;
    return Packet(packetMetaData, getNextSequenceNumber());

}

// construct and send the next packet 
void Node::SaveThePackt(){
    this->SenderWindow.push_back(constructNextPacket());
    increaseSimulationTimeBy(messageProcessingTime);
    sendPacket(this->SenderWindow.back());
    setTimerOnPacket(this->SenderWindow.back());
}
void Node::setTimerOnPacket(Packet &packet)
{
    // TODO - Generated method body
    // create the timeout msg
    Msg_Base *timeout = new Msg_Base();
    // set the frame type
    timeout->setFrameType("TIMEOUT");
    // set the sequence number
    timeout->setSequenceNumber(packet.sequenceNumber);
    // set the payload
    timeout->setPayload(packet.myMessage->getPayload());
    // set the trailer
    timeout->setTrailer(packet.myMessage->getTrailer());
    // set the timer
    scheduleAt(simTime() + this->timerDuration, timeout);
}
void Node::resendSelectedPacket(const int&seqNum)
{
   
    Packet packet = this->SenderWindow[seqNum];
    // resend the packet 
    sendPacket(packet);
}

void Node::sendPacket(const Packet &packet)
{
    // TODO - Generated method body
    // get the delay
    double delay = packet.metaData->hasDelayError() ? messageDelayTime : 0.0;
    // check if the packet is lost
  if(!packet.metaData->hasLossError()){
    sendDelayed(packet.myMessage, delay, "out");
    if(packet.metaData->hasDuplicationError()){
        Msg_Base* duplicate = new Msg_Base();
        duplicate->setFrameType(packet.myMessage->getFrameType());
        duplicate->setSequenceNumber(packet.myMessage->getSequenceNumber());
        duplicate->setPayload(packet.myMessage->getPayload());
        duplicate->setTrailer(packet.myMessage->getTrailer());

        sendDelayed(duplicate, delay+0.1, "out");
        logFile << "At time [" << simTime() << "], Node[" << id << "] [" << "sent" << "] frame with seq_num = [" << packet.sequenceNumber << "] and payload = [" << packet.myMessage->getPayload()
                    << "] and trailer = [" << packet.myMessage->getTrailer() << "], Modified[" << packet.metaData->modifiedBitPosition << "],Lost[" << "NO" << "], Duplicate[" << 1 << "], Delay[" << delay
                    << "]." << std::endl;
        logFile << "At time [" << simTime() + 0.1 << "], Node[" << id << "] [" << "sent" << "] frame with seq_num = [" << packet.sequenceNumber << "] and payload = [" << packet.myMessage->getPayload()
                    << "] and trailer = [" << packet.myMessage->getTrailer() << "], Modified[" << packet.metaData->modifiedBitPosition << "],Lost[" << "NO" << "], Duplicate[" << 2 << "], Delay[" << delay
                    << "]." << std::endl;

    }
    else{
        logFile << "At time [" << simTime() << "], Node[" << id << "] [" << "sent" << "] frame with seq_num = [" << packet.sequenceNumber << "] and payload = [" << packet.myMessage->getPayload()
                    << "] and trailer = [" << packet.myMessage->getTrailer() << "], Modified[" << packet.metaData->modifiedBitPosition << "],Lost[" << "NO" << "], Duplicate[" << 0 << "], Delay[" << delay
                    << "]." << std::endl;
    }
  }
    else{
        logFile << "At time [" << simTime() << "], Node[" << id << "] [" << "sent" << "] frame with seq_num = [" << packet.sequenceNumber << "] and payload = [" << packet.myMessage->getPayload()
                    << "] and trailer = [" << packet.myMessage->getTrailer() << "], Modified[" << packet.metaData->modifiedBitPosition << "],Lost[" << "YES" << "], Duplicate[" << 0 << "], Delay[" << delay
                    << "]." << std::endl;
    }
}

void Node::unsetTimerOnPacket(Packet &packet)
{
    // TODO - Generated method body
    cancelAndDelete(packet.timeOut);
}