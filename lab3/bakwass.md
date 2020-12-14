# Q 5.1

# interface F0/0 in router
enable
conf t
int f0/0 # to configure interface f0/0
ip address 10.0.1.1 255.0.0.0 # ip address <ip> <mask>
no shutdown
exit
exit
write

# interface F0/0 in router
enable
conf t
int f0/1 # to configure interface f0/1
ip address 10.0.2.138 255.255.255.0 # ip address <ip> <mask>
no shutdown
exit
exit
write

# check interfaces
show interfaces

# give ip, mask and default gateway to a pc
# for pc1
ip 10.0.1.10/24 10.0.1.1

# for pc2
ip 10.0.2.10/24 10.0.2.138 
# for pc3
ip 10.0.2.137/29 10.0.2.138 
# for pc4
ip 10.0.2.139/24 10.0.2.138

# show arp table
show arp

# show routing table
show ip route

# show routing cache
show ip cache

# Q5.2
# There are 256 addresses in this block. the first address is 14.24.74.0/24; The last address is 14.24.74.255/24.

# The number of addresses in the largest subblock ,which requires 120 addresses, is not power of 2, we allocate 128 addresses .The subnet mask for this subnet = 25. The first address in this block is 14.24.74.0/25 and the last address is 14.24.74.127/25.

# The number of addresses in the second largest subblock, which requires 60 addresses , is not a power of 2 either, so we allocate 64 addresses .The subnet mask for this subnet = 26. The first address in this block is 14.24.74.128/26 and the last address is 14.24.74.191/26

# The number of addresses in the smallest subblock ,which requires 10 addresses, is not a power of 2 so we allocate 16 addresses.The subnet mask for this subnet = 28. The first address in this block is 14.24.74.192/28 and the last address is 14.24.74.207/28



# Q7.1

enable
R1(config)# int f0/0
R1(config-if)# ip address 10.0.1.1 255.255.255.0
R1(config-if)# no shutdown
R1(config-if)# exit

R1(config)# ip dhcp pool lan1
R1(dhcp-config)# network 10.0.1.0 255.255.255.0
R1(dhcp-config)# Default-router 10.0.1.1
R1(dhcp-config)# exit
R1(config)# exit

dhcp
show ip






