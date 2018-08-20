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

#include "Reflector.h"

Define_Module(Reflector);

void Reflector::initialize()
{
    if (getIndex() == 0) {
        // Boot the process scheduling the initial message as a self-message.
        char msgname[20];
        sprintf(msgname, "tic-%d", getIndex());
        cPacket *msg = new cPacket(msgname, 0, 64*8);
        msg->setByteLength(64);
        //scheduleAt(0.0, msg);

    }
}

void Reflector::forwardMessage(cMessage *msg)
{
    // In this example, we just pick a random gate to send it on.
    // We draw a random number between 0 and the size of gate `out[]'.

    int n = gateSize("out");
    //int k = intuniform(0, n-1);
    for(int i= 0; i< 100; i++){
        EV << "Forwarding message " << msg << " on port out[" << i%n << "]\n";
        send(msg->dup(), "out", i%n);
    }

    delete msg;
}

void Reflector::handleMessage(cMessage *msg)
{
    // just send back the message we received
    //cMessage *msg2 = receive();
    EV << "Message " << msg << " arrived.\n";
    //delete msg2;

    forwardMessage(msg);

}
