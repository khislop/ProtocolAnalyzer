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
}


// ***************************************************************************
// * displayResults:
// *  This method will be called once, after all the packets have been
// *  processed.  You should use this to print all the statistics you
// *  collected to stdout.
// ***************************************************************************
void resultsC::displayResults() {

  std::cout << "A total of " << totalPacketCount << " packets processed." << std::endl;
  std::cout << "A total of " << totalEthernet2 << " Ethernet 2 packets processed." << std::endl;
  std::cout << "A total of " << total8023 << " 802.3 packets processed." << std::endl;
}
