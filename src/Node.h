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

#ifndef __SR_AQN_NODE_H_
#define __SR_AQN_NODE_H_

#include <omnetpp.h>
#include <deque>
#include <fstream>

#include "Packet.h"
#include "PacketParser.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
  private:
    PacketParser *packetParser { nullptr };
    void handleTimeOut(Msg_Base *msg);  //From Sender.
    void handleAck(Msg_Base *msg);  //From Receiver.
    void handleNAck(Msg_Base *msg);  //From Receiver.
    void hanldeInitialPacket(Msg_Base *msg);  //From coordinator.
    void handleDataArival(Msg_Base *msg);  //From Sender.

    // check if it is initial packet
    bool isInitialPacket(Msg_Base *msg);
    // check if it is timeout packet
    bool isTimeOutPacket(Msg_Base *msg);
    // check if it is ack packet
    bool isAckPacket(Msg_Base *msg);
    // check if it is nack packet
    bool isNAckPacket(Msg_Base *msg);
    // check if it is expected msg
    bool isExpectedMsg(Msg_Base *msg);
    // construct next packet
    Packet constructNextPacket();
    // send packet
    void sendPacket(const Packet &packet);
    // construct and send next packet
    void constructAndSendNextPacket();
    // resend selected packets in the window
    void resendSelectedPacket(const int &seqNum);
    // check if the Msg is corrupted
    bool isMsgCorrupted(Msg_Base *msg);
    // handle Msg as sender
    void handleMsgAsSender(Msg_Base *msg);
    // handle Msg as receiver
    void handleMsgAsReceiver(Msg_Base *msg);
    // check if the Msg is for receiver
    bool isMsgForReceiver(Msg_Base *msg);
    // increase simulation time by duration
    void increaseSimulationTimeBy(double duration);
    // set timer on packet
    void setTimerOnPacket(Packet &packet);
    // unset timer on packet
    void unsetTimerOnPacket(Packet &packet);
    // save the packet into the window
    void SaveThePackt();
    // check if the window is full
    bool isWindowFull() const {return SenderWindow.size() == windowSize;}
    // get next sequence number
    int getNextSequenceNumber() {return sequenceNumber++ % windowSize;}
    // variables
    std::deque<Msg_Base> RecWindow;
    std::deque<Packet> SenderWindow;
    int windowSize;
    int sequenceNumber { 0 }, id;
    double lossRate;
    double timerDuration;
    double messageDelayTime;
    double messageProcessingTime;
    std::string inputFile, outputFile;
    std::ofstream logFile;
};

#endif
