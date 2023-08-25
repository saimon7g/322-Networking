#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ssid.h"
#include "ns3/yans-wifi-helper.h"

#include <fstream>
#include <iostream>

// Default Network Topology
//
//   Wifi 10.1.3.0
//                 AP
//  *    *    *    *
//  |    |    |    |    10.1.1.0
// n5   n6   n7   n0 -------------- n1   n2   n3   n4
//                   point-to-point  |    |    |    |
//                                   *    *    *    *
//                                     LAN 10.1.2.0

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("WirelessStatic");

double totalRxBytes = 0;
double totalTxBytes = 0;
Time lastTime;
Time firstTime;
bool firstTimeFlag = false;

static void
RxCallback(Ptr<const Packet> packet, const Address& address)
{
    uint64_t packetSize = packet->GetSize(); // in bytes
    uint64_t bitsReceived = packetSize * 8;  // convert to bits

    totalRxBytes += bitsReceived / 1024;
    lastTime = Simulator::Now();
    if(!firstTimeFlag){
        firstTime = Simulator::Now();
        firstTimeFlag = true;
    }
}

static void
TxCallback(Ptr<const Packet> packet)
{
    uint64_t packetSize = packet->GetSize(); // in bytes
    uint64_t bitsReceived = packetSize * 8;  // convert to bits
    // Here you can log or analyze the bitsReceived data as needed

    totalTxBytes += bitsReceived / 1024;
    lastTime = Simulator::Now();
}

int
main(int argc, char* argv[])
{
    bool verbose = true;
    uint32_t numNode = 6;
    uint32_t numFlow = 3;
    uint32_t numPacketperSecond = 10;
    uint32_t coverageArea = 100;

    uint32_t leftSideNode = 2;
    uint32_t rightSideNode = 3;
    uint32_t packetSize = 1024;

    uint32_t variable_param = 1;    
    bool tracing = false;

    CommandLine cmd(__FILE__);
    cmd.AddValue("numNode", "Number of Nodes", numNode);
    cmd.AddValue("numFlow", "Number of Flows", numFlow);
    cmd.AddValue("numPacketperSecond", "Number of Packets per Second", numPacketperSecond);
    cmd.AddValue("coverageArea", "Coverage Area", coverageArea);
    cmd.AddValue("verbose", "Tell echo applications to log if true", verbose);
    cmd.AddValue("tracing", "Enable pcap tracing", tracing);
    cmd.AddValue("variable_param", "Variable Parameter", variable_param);

    cmd.Parse(argc, argv);

    if (verbose)
    {
        LogComponentEnable("OnOffApplication", LOG_LEVEL_INFO);
        LogComponentEnable("PacketSink", LOG_LEVEL_INFO);
    }

    rightSideNode=numNode/2;
    leftSideNode=numNode-rightSideNode;

    // p2p node

    NodeContainer p2pNodes;
    p2pNodes.Create(2);

    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

    NetDeviceContainer p2pDevices;
    p2pDevices = pointToPoint.Install(p2pNodes);

    // left side node

    NodeContainer wifiStaNodesLeft;
    wifiStaNodesLeft.Create(leftSideNode);
    NodeContainer wifiApLeft = p2pNodes.Get(0);

    // wifi setup

    YansWifiChannelHelper channelLeft = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phyLeft;
    phyLeft.SetChannel(channelLeft.Create());

    WifiMacHelper macLeft;
    Ssid ssidLeft = Ssid("ns-3-ssid-Left");
    WifiHelper wifiLeft;

    NetDeviceContainer staDevicesLeft;
    macLeft.SetType("ns3::StaWifiMac",
                    "Ssid",
                    SsidValue(ssidLeft),
                    "ActiveProbing",
                    BooleanValue(false));
    staDevicesLeft = wifiLeft.Install(phyLeft, macLeft, wifiStaNodesLeft);

    NetDeviceContainer apDevicesLeft;
    macLeft.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssidLeft));
    apDevicesLeft = wifiLeft.Install(phyLeft, macLeft, wifiApLeft);

    // right side nodes
    NodeContainer wifiStaNodesRight;
    wifiStaNodesRight.Create(rightSideNode);
    NodeContainer wifiApNodeRight = p2pNodes.Get(1);

    YansWifiChannelHelper channelRight = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phyRight;
    phyRight.SetChannel(channelRight.Create());

    WifiMacHelper macRight;
    Ssid ssidRight = Ssid("ns-3-ssid-Right");
    WifiHelper wifiRight;

    NetDeviceContainer staDevicesRight;
    macRight.SetType("ns3::StaWifiMac",
                     "Ssid",
                     SsidValue(ssidRight),
                     "ActiveProbing",
                     BooleanValue(false));
    staDevicesRight = wifiRight.Install(phyRight, macRight, wifiStaNodesRight);

    NetDeviceContainer apDevicesRight;
    macRight.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssidRight));
    apDevicesRight = wifiRight.Install(phyRight, macRight, wifiApNodeRight);

    // adding Mobility

    MobilityHelper mobility;

    mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                  "MinX",
                                  DoubleValue(0.0),
                                  "MinY",
                                  DoubleValue(0.0),
                                  "DeltaX",
                                  DoubleValue(coverageArea / 5),
                                  "DeltaY",
                                  DoubleValue(coverageArea / 5),
                                  "GridWidth",
                                  UintegerValue(sqrt(numNode)),
                                  "LayoutType",
                                  StringValue("RowFirst"));

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(wifiStaNodesRight);
    mobility.Install(wifiStaNodesLeft);
    mobility.Install(wifiApLeft);
    mobility.Install(wifiApNodeRight);

    // Internet stack

    InternetStackHelper stack;
    stack.Install(p2pNodes);
    stack.Install(wifiStaNodesLeft);
    stack.Install(wifiStaNodesRight);

    // IP address assignment

    Ipv4AddressHelper address;

    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer p2pInterfaces;
    p2pInterfaces = address.Assign(p2pDevices);

    address.SetBase("10.1.2.0", "255.255.255.0");
    address.Assign(staDevicesLeft);
    address.Assign(apDevicesLeft);

    address.SetBase("10.1.3.0", "255.255.255.0");
    address.Assign(staDevicesRight);
    address.Assign(apDevicesRight);

    // Server side

    ApplicationContainer apps;

    for (uint32_t i = 0; i < rightSideNode; i++)
    {
        PacketSinkHelper sink("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), 9));
        apps = sink.Install(wifiStaNodesRight.Get(i));
    }

    apps.Start(Seconds(1.0));
    apps.Stop(Seconds(10.0));

    // Client side

    ApplicationContainer clientApps;
    OnOffHelper onoff("ns3::UdpSocketFactory", Address());
    onoff.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    onoff.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
    onoff.SetAttribute("PacketSize", UintegerValue(packetSize));
    onoff.SetAttribute("DataRate", DataRateValue(packetSize * 8 * numPacketperSecond));

    uint32_t cur_flow_count = 0;
    for (uint32_t i = 0; i < leftSideNode; ++i)
    {
        bool flag = false;

        for (uint32_t j = 0; j < rightSideNode; j++)
        {
            AddressValue remoteAddress(InetSocketAddress(
                wifiStaNodesRight.Get(j)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
                9));
            onoff.SetAttribute("Remote", remoteAddress);
            clientApps.Add(onoff.Install(wifiStaNodesLeft.Get(i)));
            cur_flow_count++;

            if (cur_flow_count == numFlow)
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            break;
        }
    }

    clientApps.Start(Seconds(1.0));
    clientApps.Stop(Seconds(10.0));

    // Routing

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    Simulator::Stop(Seconds(11.0));

    if (tracing == true)
    {
        AsciiTraceHelper ascii;
        phyLeft.EnableAsciiAll(ascii.CreateFileStream("scratch/tracing/wifi-left.tr"));
        phyRight.EnableAsciiAll(ascii.CreateFileStream("scratch/tracing/wifi-right.tr"));
        pointToPoint.EnableAsciiAll(ascii.CreateFileStream("scratch/tracing/p2p.tr"));
        pointToPoint.EnablePcapAll("scratch/tracing/p2p");
        phyLeft.EnablePcapAll("scratch/tracing/wifi-left");
        phyRight.EnablePcapAll("scratch/tracing/wifi-right");
    }

    // Callbacks
    for (uint32_t i = 0; i < apps.GetN(); i++)
    {
        Ptr<Application> app = apps.Get(i);
        Ptr<PacketSink> pktSink = DynamicCast<PacketSink>(app);
        if (pktSink)
        {
            pktSink->TraceConnectWithoutContext("Rx", MakeCallback(&RxCallback));
        }
    }

    for (uint32_t i = 0; i < clientApps.GetN(); i++)
    {
        Ptr<Application> app = clientApps.Get(i);
        Ptr<OnOffApplication> onoffApp = DynamicCast<OnOffApplication>(app);
        if (onoffApp)
        {
            onoffApp->TraceConnectWithoutContext("Tx", MakeCallback(&TxCallback));
        }
    }

    Simulator::Run();

    Time totalTime = lastTime - firstTime;

    double throughput = totalRxBytes/totalTime.GetSeconds();
    // std::cout << "Throughput: " << throughput << " bps" << std::endl;
    double deliveryrate = totalRxBytes / totalTxBytes;
    deliveryrate = deliveryrate * 100;
    // std::cout << "Delivery Rate: " << deliveryrate << std::endl;

    std::string filename1 = "scratch/throughput.dat";
    std::string filename2 = "scratch/delivery_ratio.dat";




    std::ofstream outFile1(filename1, std::ios::app);
    std::ofstream outFile2(filename2, std::ios::app);

    if (!outFile1 || !outFile2)
    {
        std::cerr << "Error opening file for appending." << std::endl;
        return 1;
    }
    if(variable_param==1){
        outFile1 << numNode << " " << throughput << std::endl;
        outFile2 << numNode << " " << deliveryrate << std::endl;
    }
    else if(variable_param==2){
        outFile1 << numFlow << " " << throughput << std::endl;
        outFile2 << numFlow << " " << deliveryrate << std::endl;
    }
    else if(variable_param==3){
        outFile1 << numPacketperSecond << " " << throughput << std::endl;
        outFile2 << numPacketperSecond << " " << deliveryrate << std::endl;
    }
    else{
        outFile1 << coverageArea << " " << throughput << std::endl;
        outFile2 << coverageArea << " " << deliveryrate << std::endl;
    }

    // Close the file
    outFile1.close();
    outFile2.close();

    Simulator::Destroy();

    return 0;
}