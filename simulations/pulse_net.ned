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

package pulse_ddos.simulations;

import ned.DelayChannel;
import pulse_ddos.*;

network Pulse_net
{
    parameters:
        int numAgent = 210;
        int numMaster = 3;
        int numVictim = 1;
        int numReflector = 90;
        int numClient = 6000;
    
    types:
    	channel ch1 extends ned.DatarateChannel
    	{
            datarate = 100Mbps;
            delay = (0.1+exponential(50000) / 300000000) * 1s;
            ber = 1e-10;
        }
        
        channel ch2 extends ned.DatarateChannel
    	{
            datarate = 100Mbps;
            delay = (0.1+exponential(30000) / 300000000) * 1s;
            ber = 1e-10;
        }
        
        channel ch7 extends ned.DatarateChannel
    	{
            datarate = 100Mbps;
            delay = (0.1+exponential(30000) / 300000000) * 1s;
            ber = 1e-10;
        }
        
        channel ch8 extends ned.DatarateChannel
    	{
            datarate = 100Mbps;
            delay = (0.1+exponential(30000) / 300000000) * 1s;
            ber = 1e-10;
        }
        
        channel ch3 extends ned.DatarateChannel
    	{
            datarate = 100Mbps;
            delay = (0.1+exponential(100000) / 300000000) * 1s;
            ber = 1.5e-10;
        }
        
        channel ch9 extends ned.DatarateChannel
    	{
            datarate = 100Mbps;
            delay = (0.1+exponential(100000) / 300000000) * 1s;
            ber = 1.5e-10;
        }
        
        channel ch4 extends ned.DatarateChannel
    	{
            datarate = 100Mbps;
            delay = (0.1+exponential(100000) / 300000000) * 1s;
            ber = 1.5e-10;
        }
        
        channel ch5 extends ned.DatarateChannel
    	{
            datarate = 100Mbps;
            delay = (0.1+exponential(100000) / 300000000) * 1s;
            ber = 1.5e-10;
        }
        
        channel ch6 extends ned.DatarateChannel
    	{
            datarate = 100Mbps;
            delay = (0.1+exponential(100000) / 300000000) * 1s;
            ber = 2e-10;
        }
    
    submodules:
        agent[numAgent]: Txc {
            parameters:
                @display("r=,,#707070");
        }
        master[numMaster]: Master {
            parameters:
                @display("r=,,#707070");
        }
        attacker: TxcAtk {
            @display("p=253,421");
        }
        victim[numVictim]: Server {
            parameters:
                @display("p=855,900");
        }
        reflector[numReflector]: Reflector {
            parameters:
                @display("r=,,#707070");
        }
        client[numClient]: TxcClt {
            parameters:
                @display("r=,,#707070");
        }
        cloud: Cloud {
            @display("p=1000,1121");
        };
        
    connections:
                attacker.out++ --> ch1 --> master[0].in++;
                attacker.in++ <-- { delay = 300s; } <-- master[0].out++;
        
                attacker.out++ --> ch1 --> master[1].in++;
                //attacker.in++ <-- { delay = 300s; } <-- master[1].out++;
        
                attacker.out++ --> ch1 --> master[2].in++;
                //attacker.in++ <-- { delay = 300s; } <-- master[2].out++;
        
        
                for i=0..69 {
                    master[0].out++ --> ch2 --> agent[i].in++;
                    //master[0].in++ <-- {  delay = 100ms; } <-- agent[i].out;
                }
        
                for i=70..139 {
                    master[1].out++ --> ch7 --> agent[i].in++;
                    //master[1].in++ <-- {  delay = 90ms; } <-- agent[i].out;
                }
        
                for i=140..200 {
                    master[2].out++ --> ch8 --> agent[i].in++;
                    //master[2].in++ <-- {  delay = 80ms; } <-- agent[i].out;
                }
        
                for i=0..209 {
                    agent[i].out++ --> ch3 --> reflector[i % 90].in++;
                    //agent[i].in <-- {  delay = 85ms; } <-- reflector[i % 90].out++;
        
                }
        
                for i=0..5999 {
                    client[i].out++ --> ch9 --> victim[0].in++;
                	//client[i].in++ <-- ch9 <-- victim[0].out++;
        
                }
        
                for i=0..89 {
                    reflector[i].out++ --> ch4 --> victim[0].in++;
                    //reflector[i].in++ <-- ch4 <-- victim[0].out++;
        
                }
        
                //for i=0..2 {
                    victim[0].out++ --> ch5 --> cloud.in++;
                    //victim[0].in++ <-- ch5 <-- cloud.out++;
                //}
}
