//
//  resultsC.h
//  Project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//


#ifndef resultsC_h
#define resultsC_h
#include <set>

using namespace std;

class resultsC {
  protected:
    int totalPacketCount;
    int totalEthernet2;
    int total8023;
   
    //Layer 3
    int totalARP;
    int totalipv4;
    int totalipv6;
    int totalOtherNetworkLayer;
   
    int maxARP;
    int maxipv4;
    int maxipv6;

    int minARP;
    int minipv4;
    int minipv6;

    int sumARP;
    int sumipv4;
    int sumipv6;
    
    //Layer 4
    int totalICMP;
    int totalTCP;
    int totalUDP;
    int totalOtherTransportLayer;
   
    int maxICMP;
    int maxTCP;
    int maxUDP;

    int minICMP;
    int minTCP;
    int minUDP;

    int sumICMP;
    int sumTCP;
    int sumUDP;
    
    // Protocol Details
    set<long long> sMac;
    set<long long> dMac;
    set<long long> sIP;
    set<long long> dIP;
    set<long long> sUDPPort;
    set<long long> dUDPPort;
    set<long long> sTCPPort;
    set<long long> dTCPPort;
    
    int syn;
    int fin;
    int frag;

  public:
   resultsC();
   void incrementPacketCount() { totalPacketCount++; };
   void incrementEthernet2() { totalEthernet2++; };
   void increment8023() { total8023++; };
   void incrementipv4() { totalipv4++; };
   void incrementipv6() { totalipv6++; };
   void incrementARP() { totalARP++; };
   void incrementOtherNetworkLayer() { totalOtherNetworkLayer++; };
   void incrementOtherTransportLayer() { totalOtherTransportLayer++; };
   void displayResults();
   void arpStats(int input);
   void ipv4Stats(int input);
   void ipv6Stats(int input);
   void icmpStats(int input);
   void tcpStats(int input);
   void udpStats(int input);
   
   // Protocol Details
   void insertSMac(long long input){sMac.insert(input);};
   void insertDMac(long long input){dMac.insert(input);};
   void insertSIP(long long input){sIP.insert(input);};
   void insertDIP(long long input){dIP.insert(input);};
   void insertSUDPPort(long long input){sUDPPort.insert(input);};
   void insertDUDPPort(long long input){dUDPPort.insert(input);};
   void insertSTCPPort(long long input){sTCPPort.insert(input);};
   void insertDTCPPort(long long input){dTCPPort.insert(input);};
   
   
   void incrementsyn() { syn++; };
   void incrementfin() { fin++; };
   void incrementfrag() { frag++; };
};

#endif
