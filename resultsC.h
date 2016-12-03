//
//  resultsC.h
//  Project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#ifndef resultsC_h
#define resultsC_h

class resultsC {
  protected:
   int totalPacketCount;
   int totalEthernet2;
   int total8023;

  public:
   resultsC();
   void incrementPacketCount() { totalPacketCount++; };
   void incrementEthernet2() { totalEthernet2++; };
   void increment8023() { total8023++; };
   void displayResults();
};

#endif
