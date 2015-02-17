#ifndef Server_Drv_h
#define Server_Drv_h

#define _SMALL_DRIVER

#include <inttypes.h>
#include "wifi_spi.h"

typedef enum eProtMode {TCP_MODE, UDP_MODE}tProtMode;

class ServerDrv
{
public:

#ifndef _SMALL_DRIVER
    // Start server TCP on port specified
    static void startServer(uint16_t port, uint8_t sock, uint8_t protMode=TCP_MODE);
#endif

    static void startClient(uint32_t ipAddress, uint16_t port, uint8_t sock, uint8_t protMode=TCP_MODE);

    static void startClient(const char *host, uint16_t port, uint8_t sock, uint8_t protMode=TCP_MODE);

    static void stopClient(uint8_t sock);
                                                            
#ifndef _SMALL_DRIVER															
    static uint8_t getServerState(uint8_t sock);
#endif

    static uint8_t getClientState(uint8_t sock);

    static bool getData(uint8_t sock, uint8_t *data, uint8_t peek = 0);

    static bool getDataBuf(uint8_t sock, uint8_t *data, uint16_t *len);

    static bool insertDataBuf(uint8_t sock, const uint8_t *_data, uint16_t _dataLen);

    static bool sendData(uint8_t sock, const uint8_t *data, uint16_t len);

    static bool sendUdpData(uint8_t sock);

    static uint16_t availData(uint8_t sock);

    static uint8_t checkDataSent(uint8_t sock);
};

extern ServerDrv serverDrv;

#endif
