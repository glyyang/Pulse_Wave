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

#include "Server.h"

Define_Module(Server);

//Server::Server(){
//    queue->setName("Server Queue");
//}
//
//Server::~Server(){
//
//}

void Server::initialize()
{
    if (getIndex() == 0) {
        // Boot the process scheduling the initial message as a self-message.
        char msgname[20];
        sprintf(msgname, "tic-%d", getIndex());
        cPacket *msg = new cPacket(msgname, 0, 64*8);
        //msg->setByteLength(64);
//        throughput += 0;
//        throughput += 64*8;
//        tpRecord.record(throughput);






        //scheduleAt(0.0, msg);
    }
}

void Server::forwardMessage(cMessage *msg)
{
    // In this example, we just pick a random gate to send it on.
    // We draw a random number between 0 and the size of gate `out[]'.

}

void Server::handleMessage(cMessage *msg)
{
    //cMessage *msg2 = receive();
    // just send back the message we received

    //usleep(200);

    EV << "Message " << msg << " arrived.\n";
    //arrival(msg);
    simtime_t time = simTime();
    msg->setTimestamp(time);
    queue.insert(msg);


    int ql; //= queue.getLength();
    //tpRecord.recordWithTimestamp(time, ql*64*8.0);
    // We need to forward the message.

//    send(msg, "out", k);

    //throughput -= 64*8;
    //tpRecord.record(throughput);
    //delete msg;



    cPacket* p1 = (cPacket*)queue.get(0);
    while((p1->getTimestamp()+0.0001) <= simTime() && !queue.isEmpty()){

        msg = (cPacket *)queue.pop();
        int n = gateSize("out");
        int k = n-1;
        EV << "Forwarding message " << msg << " on port out[" << k << "]\n";
        //if(gate)
        //send(msg, "out", k);
        //scheduleAt(simTime(), msg)

        time = simTime();
        ql = queue.getLength();
        EV << "Queue size " << ql << "]\n";
        bool isRec = tpRecord.recordWithTimestamp(time, ql*64*8.0);
        EV << "Recording is " << isRec << "\n";
//        if(simTime() > msg->getTimestamp() + 0.1)
//            delete msg;
        //delete msg2;

        p1 = (cPacket*)queue.get(0);

    }
}
