#include "wifi_drv.h"
#include "WiFiRM04.h"

extern "C" {
  #include "utility/wl_definitions.h"
  #include "utility/wl_types.h"
  #include "debug.h"
}

// XXX: don't make assumptions about the value of MAX_SOCK_NUM.
#if MAX_SOCK_NUM == 1
int16_t 	WiFiRM04Class::_state[MAX_SOCK_NUM] = { NA_STATE };
uint16_t 	WiFiRM04Class::_server_port[MAX_SOCK_NUM] = { 0 };
#else
int16_t 	WiFiRM04Class::_state[MAX_SOCK_NUM] = { NA_STATE, NA_STATE };
uint16_t 	WiFiRM04Class::_server_port[MAX_SOCK_NUM] = { 0, 0 };
#endif

WiFiRM04Class::WiFiRM04Class()
{
	// Driver initialization
	init();
}

void WiFiRM04Class::init()
{
    WiFiDrv::wifiDriverInit();
}

#ifndef _SMALL_DRIVER
uint8_t WiFiRM04Class::getSocket()
{
    for (uint8_t i = 0; i < MAX_SOCK_NUM; ++i)
    {
        if (WiFiRM04Class::_server_port[i] == 0)
        {
             return i;
        }
    }
    return NO_SOCKET_AVAIL;
}
#endif

char* WiFiRM04Class::firmwareVersion()
{
	return WiFiDrv::getFwVersion();
}

#ifndef _SMALL_DRIVER
bool WiFiRM04Class::beginAsAp(char* ssid)
{
    return WiFiDrv::wifiSetApMode(ssid, strlen(ssid));
}
#endif

int WiFiRM04Class::begin(char* ssid)
{
	uint8_t status = WL_IDLE_STATUS;
	uint8_t attempts = WL_MAX_ATTEMPT_CONNECTION;

   if (WiFiDrv::wifiSetNetwork(ssid, strlen(ssid)) != WL_FAILURE)
   {
	   do
	   {
		   delay(WL_DELAY_START_CONNECTION);
		   status = WiFiDrv::getConnectionStatus();
	   }
	   while ((( status == WL_IDLE_STATUS)||(status == WL_SCAN_COMPLETED))&&(--attempts>0));
   }else
   {
	   status = WL_CONNECT_FAILED;
   }
   return status;
}

#ifndef _SMALL_DRIVER
int WiFiRM04Class::begin(char* ssid, uint8_t key_idx, const char *key)
{
	uint8_t status = WL_IDLE_STATUS;
	uint8_t attempts = WL_MAX_ATTEMPT_CONNECTION;

	// set encryption key
   if (WiFiDrv::wifiSetKey(ssid, strlen(ssid), key_idx, key, strlen(key)) != WL_FAILURE)
   {
	   do
	   {
		   delay(WL_DELAY_START_CONNECTION);
		   status = WiFiDrv::getConnectionStatus();
	   }while ((( status == WL_IDLE_STATUS)||(status == WL_SCAN_COMPLETED))&&(--attempts>0));
   }else{
	   status = WL_CONNECT_FAILED;
   }
   return status;
}
#endif

int WiFiRM04Class::begin(char* ssid, const char *passphrase)
{
	uint8_t status = WL_IDLE_STATUS;
	uint8_t attempts = WL_MAX_ATTEMPT_CONNECTION;

	// set passphrase
    if (WiFiDrv::wifiSetPassphrase(ssid, strlen(ssid), passphrase, strlen(passphrase))!= WL_FAILURE)
    {
 	   do
 	   {
 		   delay(WL_DELAY_START_CONNECTION);
 		   status = WiFiDrv::getConnectionStatus();
 	   }
	   while ((( status == WL_IDLE_STATUS)||(status == WL_SCAN_COMPLETED))&&(--attempts>0));
    }else{
    	status = WL_CONNECT_FAILED;
    }
    return status;
}

#ifndef _SMALL_DRIVER
void WiFiRM04Class::config(IPAddress local_ip)
{
	WiFiDrv::config(1, (uint32_t)local_ip, 0, 0);
}

void WiFiRM04Class::config(IPAddress local_ip, IPAddress dns_server)
{
	WiFiDrv::config(1, (uint32_t)local_ip, 0, 0);
	WiFiDrv::setDNS(1, (uint32_t)dns_server, 0);
}

void WiFiRM04Class::config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway)
{
	WiFiDrv::config(2, (uint32_t)local_ip, (uint32_t)gateway, 0);
	WiFiDrv::setDNS(1, (uint32_t)dns_server, 0);
}

void WiFiRM04Class::config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet)
{
	WiFiDrv::config(3, (uint32_t)local_ip, (uint32_t)gateway, (uint32_t)subnet);
	WiFiDrv::setDNS(1, (uint32_t)dns_server, 0);
}

void WiFiRM04Class::setDNS(IPAddress dns_server1)
{
	WiFiDrv::setDNS(1, (uint32_t)dns_server1, 0);
}

void WiFiRM04Class::setDNS(IPAddress dns_server1, IPAddress dns_server2)
{
	WiFiDrv::setDNS(2, (uint32_t)dns_server1, (uint32_t)dns_server2);
}
#endif

int WiFiRM04Class::disconnect()
{
#ifndef _SMALL_DRIVER
    return WiFiDrv::disconnect();
#else
	return 0;
#endif
}

uint8_t* WiFiRM04Class::macAddress(uint8_t* mac)
{
	uint8_t* _mac = WiFiDrv::getMacAddress();
	memcpy(mac, _mac, WL_MAC_ADDR_LENGTH);
  return mac;
}
  
#ifndef _SMALL_DRIVER
IPAddress WiFiRM04Class::localIP()
{
	IPAddress ret;
	WiFiDrv::getIpAddress(ret);
	return ret;
}

IPAddress WiFiRM04Class::subnetMask()
{
	IPAddress ret;
	WiFiDrv::getSubnetMask(ret);
	return ret;
}

IPAddress WiFiRM04Class::gatewayIP()
{
	IPAddress ret;
	WiFiDrv::getGatewayIP(ret);
	return ret;
}

char* WiFiRM04Class::SSID()
{
    return WiFiDrv::getCurrentSSID();
}

uint8_t* WiFiRM04Class::BSSID(uint8_t* bssid)
{
	uint8_t* _bssid = WiFiDrv::getCurrentBSSID();
	memcpy(bssid, _bssid, WL_MAC_ADDR_LENGTH);
    return bssid;
}
#endif

int32_t WiFiRM04Class::RSSI()
{
#ifndef _SMALL_DRIVER
    return WiFiDrv::getCurrentRSSI();
#else
	return -60;
#endif
}

#ifndef _SMALL_DRIVER
uint8_t WiFiRM04Class::encryptionType()
{
    return WiFiDrv::getCurrentEncryptionType();
}
#endif


int8_t WiFiRM04Class::scanNetworks()
{
#ifndef _SMALL_DRIVER
	uint8_t attempts = 10;
	uint8_t numOfNetworks = 0;

	if (WiFiDrv::startScanNetworks() == WL_FAILURE)
		return WL_FAILURE;
 	do
 	{
 		delay(2000);
 		numOfNetworks = WiFiDrv::getScanNetworks();
 	}
	while (( numOfNetworks == 0)&&(--attempts>0));
	return numOfNetworks;
#else
	return 0;
#endif
}

char* WiFiRM04Class::SSID(uint8_t networkItem)
{
#ifndef _SMALL_DRIVER
	return WiFiDrv::getSSIDNetoworks(networkItem);
#else
	return "";
#endif
}

int32_t WiFiRM04Class::RSSI(uint8_t networkItem)
{
#ifndef _SMALL_DRIVER
	return WiFiDrv::getRSSINetoworks(networkItem);
#else
	return -60;
#endif
}

uint8_t WiFiRM04Class::encryptionType(uint8_t networkItem)
{
#ifndef _SMALL_DRIVER
    return WiFiDrv::getEncTypeNetowrks(networkItem);
#else
	return 0;
#endif
}

uint8_t WiFiRM04Class::status()
{
    return WiFiDrv::getConnectionStatus();
}

#ifndef _SMALL_DRIVER
int WiFiRM04Class::hostByName(const char* aHostname, IPAddress& aResult)
{
	return WiFiDrv::getHostByName(aHostname, aResult);
}
#endif

WiFiRM04Class WiFi;
