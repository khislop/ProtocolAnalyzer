//
//  resultsC.cc
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "project4.h"

// ***************************************************************************
// * resultsC::resultsC
// *  Constructor for the results container class.  
// ***************************************************************************
resultsC::resultsC() {
  totalPacketCount = 0;
  totalEthernet2 = 0;
  total8023 = 0;
  
  //Layer 3
  totalARP = 0;
  totalipv4 = 0;
  totalipv6 = 0;
  totalOtherNetworkLayer = 0;
  
  maxARP = 0;
  maxipv4 = 0;
  maxipv6 = 0;
  
  minARP = 9999999;
  minipv4 = 9999999;
  minipv6 = 9999999;
  
  sumARP = 0;
  sumipv4 = 0;
  sumipv6 = 0;
  
  //Layer 4
  totalICMP = 0;
  totalTCP = 0;
  totalUDP = 0;
  totalOtherTransportLayer = 0;
   
  maxICMP = 0;
  maxTCP = 0;
  maxUDP = 0;

  minICMP = 9999999;
  minTCP = 9999999;
  minUDP = 9999999;

  sumICMP = 0;
  sumTCP = 0;
  sumUDP = 0;
}

void resultsC::arpStats(int input){
    if(input > maxARP){
        maxARP = input;
    }
    if(input < minARP){
        minARP = input;
    }
    sumARP += input;
} 

void resultsC::ipv4Stats(int input){
    if(input > maxipv4){
        maxipv4 = input;
    }
    if(input < minipv4){
        minipv4 = input;
    }
    sumipv4 += input;
} 

void resultsC::ipv6Stats(int input){
    if(input > maxipv6){
        maxipv6 = input;
    }
    if(input < minipv6){
        minipv6 = input;
    }
    sumipv6 += input;
} 


void resultsC::icmpStats(int input){
    if(input > maxICMP){
        maxICMP = input;
    }
    if(input < minICMP){
        minICMP = input;
    }
    sumICMP += input;
    totalICMP ++;
} 

void resultsC::tcpStats(int input){
    if(input > maxTCP){
        maxTCP = input;
    }
    if(input < minTCP){
        minTCP = input;
    }
    sumTCP += input;
    totalTCP ++;
} 

void resultsC::udpStats(int input){
    if(input > maxUDP){
        maxUDP = input;
    }
    if(input < minUDP){
        minUDP = input;
    }
    sumUDP += input;
    totalUDP ++;
} 



// ***************************************************************************
// * displayResults:
// *  This method will be called once, after all the packets have been
// *  processed.  You should use this to print all the statistics you
// *  collected to stdout.
// ***************************************************************************
void resultsC::displayResults() {
  //Calculate Averages
  double aveARP = totalARP != 0 ? (double)sumARP / totalARP : 0;
  double aveipv4 = totalipv4 != 0 ? (double)sumipv4 / totalipv4 : 0;
  double aveipv6 = totalipv6 != 0 ? (double)sumipv6 / totalipv6 : 0;
  double aveICMP = totalICMP != 0 ? (double)sumICMP / totalICMP : 0;
  double aveUDP = totalUDP != 0 ? (double)sumUDP / totalUDP : 0;
  double aveTCP = totalTCP != 0 ? (double)sumTCP / totalTCP : 0;


  std::cout << "A total of " << totalPacketCount << " packets processed." << std::endl;
  //Link Layer
  std::cout << "Link Layer:" << std::endl;
  std::cout << "A total of " << totalEthernet2 << " Ethernet 2 packets processed." << std::endl;
  std::cout << "A total of " << total8023 << " 802.3 packets processed." << std::endl;
  //Network Layer
  std::cout << endl << "Network Layer:" << std::endl;
  std::cout << "Type\tTotal\tmin\tmax\taverage" << std::endl;
  std::cout << "ipv4" << "\t" << totalipv4 << "\t" << minipv4 << "\t" << maxipv4 << "\t" << aveipv4 << std::endl;
  std::cout << "ipv6" << "\t" << totalipv6 << "\t" << minipv6 << "\t" << maxipv6 << "\t" << aveipv6 << std::endl;
  std::cout << "ARP" << "\t" << totalARP << "\t" << minARP << "\t" << maxARP << "\t" << aveARP << std::endl;
  std::cout << "Other" << "\t" << totalOtherNetworkLayer << std::endl;
  //Transport Layer
  std::cout << endl << "Transport Layer:" << std::endl;
  std::cout << "Type\tTotal\tmin\tmax\taverage" << std::endl;
  std::cout << "UDP" << "\t" << totalUDP << "\t" << minUDP << "\t" << maxUDP << "\t" << aveUDP << std::endl;
  std::cout << "TCP" << "\t" << totalTCP << "\t" << minTCP << "\t" << maxTCP << "\t" << aveTCP << std::endl;
  std::cout << "ICMP" << "\t" << totalICMP << "\t" << minICMP << "\t" << maxICMP << "\t" << aveICMP << std::endl;
  std::cout << "Other" << "\t" << totalOtherTransportLayer << std::endl;
  
  
  
  
  //std::cout << "A total of " << totalipv4 << " ipv4 packets processed." << std::endl;
  //std::cout << "A total of " << totalipv6 << " ipv6 packets processed." << std::endl;
  //std::cout << "A total of " << totalARP << " ARP packets processed." << std::endl;
  //std::cout << "A total of " << totalOtherNetworkLayer << " Other network layer packets processed." << std::endl;

  
}
