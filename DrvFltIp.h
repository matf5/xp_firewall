/*

  DrvFltIp.H

  

*/


//
// Define the various device type values.  Note that values used by Microsoft
// Corporation are in the range 0-32767, and 32768-65535 are reserved for use
// by customers.
//

//Include This file for the definitions of the CTL_CODE and extra
#include <winioctl.h>

#define FILE_DEVICE_DRVFLTIP  0x00654322



//
// Macro definition for defining IOCTL and FSCTL function control codes.  Note
// that function codes 0-2047 are reserved for Microsoft Corporation, and
// 2048-4095 are reserved for customers.
//

#define DRVFLTIP_IOCTL_INDEX  0x830



//重要，这是应用向驱动发送的指令代码
#define START_IP_HOOK CTL_CODE(FILE_DEVICE_DRVFLTIP, DRVFLTIP_IOCTL_INDEX,METHOD_BUFFERED, FILE_ANY_ACCESS)

#define STOP_IP_HOOK CTL_CODE(FILE_DEVICE_DRVFLTIP, DRVFLTIP_IOCTL_INDEX+1, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define ADD_FILTER CTL_CODE(FILE_DEVICE_DRVFLTIP, DRVFLTIP_IOCTL_INDEX+2, METHOD_BUFFERED, FILE_WRITE_ACCESS)

#define CLEAR_FILTER CTL_CODE(FILE_DEVICE_DRVFLTIP, DRVFLTIP_IOCTL_INDEX+3, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define READ_FILTER  CTL_CODE(FILE_DEVICE_DRVFLTIP, DRVFLTIP_IOCTL_INDEX+4, METHOD_BUFFERED, FILE_READ_ACCESS)



//重要，该结构体是filter的构成
typedef struct filter
{
	USHORT protocol;		//protocol used

	ULONG sourceIp;			//source ip address
	ULONG destinationIp;	//destination ip address

	ULONG sourceMask;		//source mask
	ULONG destinationMask;	//destination mask

	USHORT sourcePort;		//source port
	USHORT destinationPort; //destination port
	
	BOOLEAN drop;			//if true, the packet will be drop, otherwise the packet pass
}IPFilter;



//struct to build a linked list 
struct filterList
{
	IPFilter ipf;

	struct filterList *next;
};


//Ip Header，不会用到
typedef struct IPHeader 
{
    UCHAR     iphVerLen;      // Version and length 
    UCHAR     ipTOS;          // Type of service 
    USHORT    ipLength;       // Total datagram length 
    USHORT    ipID;		      // Identification 
    USHORT    ipFlags;	      // Flags
    UCHAR     ipTTL;	      // Time to live 
    UCHAR     ipProtocol;	  // Protocol 
    USHORT    ipChecksum;     // Header checksum 
    ULONG     ipSource;       // Source address 
    ULONG     ipDestination;  // Destination address 
} IPPacket; 


//TCP Header，不会用到
typedef struct _TCPHeader
{
	USHORT			sourcePort;			// Source Port
	USHORT			destinationPort;	// Destination Port
	ULONG			sequenceNumber;		// Number of Sequence
	ULONG			acknowledgeNumber;	// Number of aknowledge
	UCHAR			dataoffset;			// Pointer to data
	UCHAR			flags;				// Flags
	USHORT			windows;			// Size of window
	USHORT			checksum;			// Total checksum
	USHORT			urgentPointer;		// Urgent pointer
} TCPHeader;


//UDP Header，不会用到
typedef struct _UDPHeader
{
	USHORT			sourcePort;			// Source Port
	USHORT			destinationPort;	// Destination Port
	USHORT			len;				// Total length
	USHORT			checksum;			// Total checksum
} UDPHeader;
