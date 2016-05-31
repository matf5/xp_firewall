#include "stdafx.h"
#include "sockutil.h"
#include <stdlib.h>
#include <string.h>

/*++

Routine Description:

    Convert the ip to the format we have to compare

Arguments:

    ip - string that represent a ip address


Return Value:

	ip

--*/
//重要，IP地址类型，添加filter的时候需要强制转换为该类型
unsigned long inet_addr(const char *sIp)
{
	int octets[4];
	int i;
	const char * auxCad = sIp;
	unsigned long lIp = 0;
	
	//we extract each octet of the ip address
	//atoi will get characters until it found a non numeric character(in our case '.')
	for(i = 0; i < 4; i++)
	{
		octets[i] = atoi(auxCad);

		if(octets[i] < 0 || octets[i] > 255)
			return 0;
		lIp |= (octets[i] << (i*8));

		//update auxCad to point to the next octet
		auxCad = strchr(auxCad, '.');

		if(auxCad == NULL && i!=3)
			return -1;
		auxCad++;
	}
	return lIp;
}



/*++

Routine Description:

    Convert the port to the format we have to compare

Arguments:

    port - port to convert


Return Value:

	port converted

--*/
//重要，端口号类型，添加filter的时候需要强制转换为该类型
unsigned short htons(unsigned short port)
{
	unsigned short portRet;
	portRet = ((port << 8) | (port >> 8));
	return portRet;
}