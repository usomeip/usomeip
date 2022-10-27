# uSOMEIP -- micro SOMEIP

Those codes is mirrored from https://github.com/autoas/ssas-public, and this library is source open for SOMEIP study&research, but not free for any other commercial usage.

This is a light weight SOMEIP/SD software stack implemented according to AUTOSAR 4.4 specification. And this can be deployed on either resource constrained MCU or on rich os such as windows/linux/android/QNX, etc.

## An example to play with:

* NetApp: An app with SOMEIP/SD.
* NetAppT: An anti-test purpose app with SOMEIP/SD

```sh
# The NetApp is built with FreeRTOS+LWIP sockets
set USE_LWIP=YES
# the index of the Virtual Box Network Adaptor "Oracle"
# on my PC, it's zero, but on your PC, it's maybe not
# and please staticly configured its ipv4 address to 172.18.0.1
set PACKET_LIB_ADAPTER_NR=0
scons --app=NetApp --os=FreeRTOS --net=LWIP

# The NetAppT is built with host windows sockets
set USE_LWIP=
scons --app=NetAppT

# in 2 different pannel, launch below commands to start the apps
build\nt\GCC\NetApp\NetApp.exe
build\nt\GCC\NetAppT\NetAppT.exe
```

When you launch the NetApp, generally you will see below messages, please note that for the NetApp + FreeRTOS + LWIP, it's using the [windows PCAP](https://www.winpcap.org/) to simulate a virtual network adapter for the easy study/development process. And I find that the [VirtualBox](https://www.virtualbox.org/) network adapter is the most stable one that works perfect.  So you need to install the VirtualBox and then manually configure its ipv4 address to "172.18.0.1", as below picture shows:

![vbox-ip-config](https://autoas.github.io/ssas-public/images/someip-vbox-net-adapter-ip-config.png)

```sh
INFO    :application build @ May  3 2022 21:06:24
... ...
TCPIPI  :Starting lwIP, IP 172.18.0.200
 0: NPF_{7C69ADB8-A49E-46AA-AA62-5E367B965EE9}
     Desc: "Oracle"
 1: NPF_{D8E510AC-9490-42A0-AA88-3BE0BD41E52D}
     Desc: "TAP-Windows Adapter V9"
 2: NPF_{8FAE2F35-41DC-4D5D-A2FC-8426852265FF}
     Desc: "Microsoft"
 3: NPF_{8F9E1CE9-4EA7-4354-844F-848EA56AF7EE}
     Desc: "Microsoft"
 4: NPF_{434E0818-480A-450B-A7F1-99F473224151}
     Desc: "Microsoft"
Using adapter_num: 0
Using adapter: "Oracle"
DEMI    :Set Event 5 status 2
DEMI    :Set Event 5 status 2
DEMI    :Operation Cycle 1 Start
```

After all the applications launched, press key "s" to put SOMEIP related server/client/event group online, running for several seconds, press key "s" again to put them  offline, you can see logs as below:

![someip net log](https://autoas.github.io/ssas-public/images/someip-netapp-netappt-runing-log.png)

And under the root directory of ssas-public, you could see net.log and wireshark.pcap.

* net.log: A text file with logs about SOMEIP/SD
* wireshark.pcap: a network pcap file has all the ethernet packets received or transmitted by lwip

![someip pcap](https://autoas.github.io/ssas-public/images/someip-netapp-netappt-pcap.png)

