## Wireshark
1. Put interface intp *Promiscuous Mode*
2. Use filters

## Most Important network requirements
1. IP Address
2. Network mask
3. Default Gateway

## Config Router

enable
conf t
interface <interface_name>
ip address 10.0.0.1/255.255.255.0
no shut down
exit
conf t
interface <interface_name>
ip address 
no shut down
exit
write # store all configurations

show interfaces
show ip route