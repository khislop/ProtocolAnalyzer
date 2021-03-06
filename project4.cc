

#include "project4.h"

int COUNT = 0;
// ****************************************************************************
// * pk_processor()
// *  Most of the work done by the program will be done here (or at least it
// *  it will originate here). The function will be called once for every 
// *  packet in the savefile.
// ****************************************************************************
void pk_processor(u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
  COUNT++;

  resultsC* results = (resultsC*)user;
  results->incrementPacketCount();
  
  //Check byte 12 and 13 to tell if packet is 803.2 or Ethernet 2
  //If Ethernet 2
  if((int)packet[12]*256 + (int)packet[13] >= 1536){
  	//cout << "ETHERNET 2" << endl;
    results->incrementEthernet2();
    //Check network layer protocol
    int layer3 = 0;
    int t = (int)packet[12]*256 + (int)packet[13];
    //ipv4
    if(t == 2048){
        layer3 = 1;
    }
    //arp
    else if(t == 2054){
        layer3 = 2;
    }
    //ipv6
    else if(t == 34525){
        layer3 = 3;
    }
    //others
    else{
        layer3 = 0;
    }
    processNetworkLayer(packet, layer3, results, 14);
  }
  //If 802.3
  else if((int)packet[12]*256 + (int)packet[13] <= 1500){
  	//cout << "802.3" << endl;
    results->increment8023();
    //Check network layer protocol
    int layer3 = 0;

    processNetworkLayer(packet, layer3, results, 22);
  }
  
  //Count unique mac
  results->insertDMac((int)packet[0]*pow(255, 5) + packet[1]*pow(255, 4) + packet[2]*pow(255, 3) + packet[3]*pow(255, 2) + packet[4]*pow(255, 1) + packet[5]);
  results->insertSMac((int)packet[6]*pow(255, 5) + packet[7]*pow(255, 4) + packet[8]*pow(255, 3) + packet[9]*pow(255, 2) + packet[10]*pow(255, 1) + packet[11]);
  
  //std::cout << (int)packet[12]*256 + (int)packet[13] << std::endl;

  return;
}

void processNetworkLayer(const u_char *packet, int layer3, resultsC* results, int start){
    //ipv4
    int len;
    if(layer3 == 1){
        len = (int)packet[start+2]*256 + (int)packet[start+3];
        results->incrementipv4();
        results->ipv4Stats(len);
        //Check transport layer protocol
        int layer4 = 0;
        int t = (int)packet[start+9];
        //ICMP
        if(t == 1){
            layer4 = 1;
        }
        //TCP
        else if(t == 6){
            layer4 = 2;
        }
        //UDP
        else if(t == 17){
            layer4 = 3;
        }//udpipv6 = 0x3a
        //others
        else{
            layer4 = 0;
        }
        //Count unique ip
        processTransportLayer(packet, layer4, results, start + (((int)packet[start])%16), len);
        results->insertSIP((int)packet[start + 12]*pow(255, 3) + packet[start + 13]*pow(255, 2) + packet[start + 14]*pow(255, 1) + packet[start + 15]);
        results->insertDIP((int)packet[start + 16]*pow(255, 3) + packet[start + 17]*pow(255, 2) + packet[start + 18]*pow(255, 1) + packet[start + 19]);
        //Count fragmented packages
        if((packet[start + 6] & 32) == 32){
            results->incrementFrag();
        }
    }
    //arp
    else if(layer3 == 2){
        len = 60;
        results->incrementARP();
        results->arpStats(len);
    }
    //ipv6
    else if(layer3 == 3){
        len = (int)packet[start+4]*256 + (int)packet[start+5];
        results->incrementipv6();
        results->ipv6Stats(len);
        //Check transport layer protocol
        int layer4 = 0;
        int t = (int)packet[start+6];
        //ICMP
        if(t == 1){
            layer4 = 1;
        }
        //TCP
        else if(t == 6){
            layer4 = 2;
        }
        //UDP
        else if(t == 17){
            layer4 = 3;
        }//udpipv6 = 0x3a
        //others
        else{
            layer4 = 0;
        }
        processTransportLayer(packet, layer4, results, start+40, len);
        int sIP = 0;
        int dIP = 0;
        for(int q = 0; q < 16; q++){
            sIP += packet[start + 8 + q];
            dIP += packet[start + 24 + q];
        }
        results->insertSIP(sIP);
        results->insertDIP(dIP);
    }
    //other
    else if(layer3 == 0){
        results->incrementOtherNetworkLayer();
    }
    //Soemthing went wrong
    else{
        cout << "error" << endl;
        return;
    }
    
    
    
    
    return;
}

void processTransportLayer(const u_char *packet, int layer4, resultsC* results, int start, int len){
    //ICMP
    if(layer4 == 1){
        results->icmpStats(len - 8);
    }
    //TCP
    else if(layer4 == 2){
        int t = (int)(packet[start+12] - (packet[(start+12)]%16)) / 4;
        results->tcpStats(len - t);
        //Count unique TCP ports
        results->insertSTCPPort(packet[start + 0] * 256 + packet[start + 1]);
        results->insertDTCPPort(packet[start + 2] * 256 + packet[start + 3]);
        //Count syn and fin bits
        if((packet[start + 13] & 2) == 2){
            results->incrementSyn();
        }
        if((packet[start + 13] & 1) == 1){
            results->incrementFin();
        }
    }
    //UDP
    else if(layer4 == 3){
        results->udpStats(len - 8);
        //Count unique UDP ports
        results->insertSUDPPort(packet[start + 0] * 256 + packet[start + 1]);
        results->insertDUDPPort(packet[start + 2] * 256 + packet[start + 3]);
    }
    //other
    else if(layer4 == 0){
        results->incrementOtherTransportLayer();
    }
    //Soemthing went wrong
    else{
        cout << "error" << endl;
        return;
    }
}


// ****************************************************************************
// * main()
// *  You should not have to worry about anything if you don't want to. 
// *  My code will open the file, initalize the results container class,
// *  call pk_processor() once for each packet and the finally call
// *  the displayResutls() method.
// ****************************************************************************
int main (int argc, const char * argv[])
{

  
  // **********************************************************************
  // * The program is called with a single argument, the name of the
  // * pcap save file to read.
  // **********************************************************************
  if (argc != 2) {
     std::cerr << "useage: project4 <filename>" << std::endl;
     exit(EXIT_FAILURE);
  }


  // **********************************************************************
  // * Instantiate the results class.  
  // **********************************************************************
  resultsC* results = new resultsC();



  // **********************************************************************
  // * Attempt to open the file.
  // **********************************************************************
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *PT;

  bzero(errbuf,PCAP_ERRBUF_SIZE);
  if ((PT = pcap_open_offline(argv[1],errbuf)) == NULL ) {
    std::cerr << "Unable to open pcap file: " << argv[1] << "\n"
         << pcap_geterr(PT) << std::endl;
    exit(EXIT_FAILURE);
  }

  if (strlen(errbuf) > 0)
    std::cerr << "Warning: pcap_open_offiline: " << pcap_geterr(PT) << std::endl;



  // **********************************************************************
  // * The dispatcher will call the packet processor once for packet
  // * in the capture file.
  // **********************************************************************
  int pk_count;
  if ((pk_count = pcap_dispatch(PT, -1, pk_processor, (u_char *)results)) < 0) {
    std::cerr << "Error calling dispatcher: " << pcap_geterr(PT) << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "Dispatcher finished with " << pk_count << " packets left in the queue." << std::endl;


  // **********************************************************************
  // * File your report here.
  // **********************************************************************
  results->displayResults();
  exit(EXIT_SUCCESS);
}


