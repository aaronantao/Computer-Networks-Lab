//program to calculate subnet mask and network id based on given ip address and subnet mask
//do it in c++

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string ip;
    cout << "Enter IP Address: ";
    cin >> ip;

    stringstream ss(ip);
    string part;
    getline(ss, part, '.');
    int firstOctet = stoi(part);

    if (firstOctet >= 0 && firstOctet <= 127) {
        cout << "Class: A" << endl;
        cout << "First Octet: 0 - 127" << endl;
        cout << "Binary Prefix: 0XXXXXXX" << endl;
        cout << "IP Range: 0.0.0.0 - 127.255.255.255" << endl;
        cout << "Subnet Mask: 255.0.0.0" << endl;
        cout << "Hosts/Network: 2^24 - 2 = 16,777,214" << endl;
        cout << "No. of Networks: 2^7 = 128" << endl;
    }
    else if (firstOctet >= 128 && firstOctet <= 191) {
        cout << "Class: B" << endl;
        cout << "First Octet: 128 - 191" << endl;
        cout << "Binary Prefix: 10XXXXXX" << endl;
        cout << "IP Range: 128.0.0.0 - 191.255.255.255" << endl;
        cout << "Subnet Mask: 255.255.0.0" << endl;
        cout << "Hosts/Network: 2^16 - 2 = 65,534" << endl;
        cout << "No. of Networks: 2^14 = 16,384" << endl;
    }
    else if (firstOctet >= 192 && firstOctet <= 223) {
        cout << "Class: C" << endl;
        cout << "First Octet: 192 - 223" << endl;
        cout << "Binary Prefix: 110XXXXX" << endl;
        cout << "IP Range: 192.0.0.0 - 223.255.255.255" << endl;
        cout << "Subnet Mask: 255.255.255.0" << endl;
        cout << "Hosts/Network: 2^8 - 2 = 254" << endl;
        cout << "No. of Networks: 2^21 = 2,097,152" << endl;
    }
    else if (firstOctet >= 224 && firstOctet <= 239) {
        cout << "Class: D" << endl;
        cout << "First Octet: 224 - 239" << endl;
        cout << "Binary Prefix: 1110XXXX" << endl;
        cout << "IP Range: 224.0.0.0 - 239.255.255.255" << endl;
        cout << "Subnet Mask: N/A" << endl;
    }
    else if (firstOctet >= 240 && firstOctet <= 255) {
        cout << "Class: E" << endl;
        cout << "First Octet: 240 - 255" << endl;
        cout << "Binary Prefix: 1111XXXX" << endl;
        cout << "IP Range: 240.0.0.0 - 255.255.255.255" << endl;
        cout << "Subnet Mask: N/A" << endl;
    }
    else {
        cout << "Invalid IP Address!" << endl;
    }
    cout << "\nSubnet mask is used to divide the network id and host id" << endl;
    cout << "Loopback address is an address that a computer or network device uses to send data packets to itself" << endl;
    cout << "The loopback address is typically used for testing and troubleshooting purposes, as it allows a device to verify that its own network stack is functioning correctly" << endl;
    cout << "The reason for -2 is that two addresses are reserved and cannot be assigned to hosts. The first address is the Network Address, which identifies the network itself, and the last address is the Broadcast Address, which is used to send data to all hosts in the network" << endl; 
    return 0;
}
