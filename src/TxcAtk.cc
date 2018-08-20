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

#include "TxcAtk.h"

Define_Module(TxcAtk);

void TxcAtk::initialize()
{
    if (getIndex() == 0) {
        // Boot the process scheduling the initial message as a self-message.
        char msgname[20];
        sprintf(msgname, "tic-%d", getIndex());
        cMessage *msg = new cMessage(msgname);
        scheduleAt(0, msg);
    }
}

void TxcAtk::forwardMessage(cMessage *msg)
{
    // In this example, we just pick a random gate to send it on.
    // We draw a random number between 0 and the size of gate `out[]'.

    int n = gateSize("out");
    //int k = intuniform(0, n-1);
    //for(int j = 0; j < 2; j++){



    for(int i= 0; i< n; i++){
        EV << "Forwarding message " << msg << " on port out[" << i << "]\n";
        send(msg->dup(), "out", i);
    }

    //}
}

void TxcAtk::handleMessage(cMessage *msg)
{
    // just send back the message we received
    if (getIndex() == 30) {
        // Message arrived.
        EV << "Message " << msg << " arrived.\n";
        delete msg;
    }
    else {
        // We need to forward the message.
        forwardMessage(msg);
    }
}
