#include <cstdint>
#include <WebSocketsServer.h>

void startWebSocket();
void webSocketLoop();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght);