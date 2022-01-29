/** Network Simulator 3.31 LTE Test Program
* @Author: Sumit Jena
* @Date: 13 February 2021
*/
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-helper.h"
#include "ns3/config-store.h"
#include <ns3/buildings-helper.h>
#include "ns3/netanim-module.h"
using namespace ns3;
int main () {
 Time simTime = MilliSeconds (3000);
 ConfigStore inputConfig;
 inputConfig.ConfigureDefaults ();
 Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
 lteHelper->EnableLogComponents ();
 NodeContainer enbNodes;
 NodeContainer ueNodes;
 enbNodes.Create (1);
 ueNodes.Create (3);
 // Install Mobility Model
 MobilityHelper mobility;
 mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
 mobility.Install (enbNodes);
 BuildingsHelper::Install (enbNodes);
 mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
 mobility.Install (ueNodes);
 BuildingsHelper::Install (ueNodes);
 NetDeviceContainer enbDevs;
 NetDeviceContainer ueDevs;
 
 // lteHelper->SetSchedulerType ("ns3:RrFfMacScheduler");
 enbDevs = lteHelper->InstallEnbDevice (enbNodes);
 ueDevs = lteHelper->InstallUeDevice (ueNodes);
 // Attach UE to eNB
 lteHelper->Attach (ueDevs, enbDevs.Get (0));
 // Activate a data radio bearer
 enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
 EpsBearer bearer (q);
 lteHelper->ActivateDataRadioBearer (ueDevs, bearer);
 lteHelper->EnableTraces ();
 
 AnimationInterface anim ("animation2.xml");
 anim.SetConstantPosition(enbNodes.Get (0), 1.0, 2.0);
 anim.SetConstantPosition(ueNodes.Get (0), 3.0, 2.0);
 anim.SetConstantPosition(ueNodes.Get (1), 2.0, 3.0);
 anim.SetConstantPosition(ueNodes.Get (2), 4.0, 4.0);
 Simulator::Stop (simTime);
 Simulator::Run ();
 Simulator::Destroy();
 return 0;
}
