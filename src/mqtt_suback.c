#include <mqtt.h>


ssize_t mqtt_unpack_suback_response (struct mqtt_response *mqtt_response, const uint8_t *buf) {
    const uint8_t const *start = buf;
    uint32_t remaining_length = mqtt_response->fixed_header.remaining_length;
    
    /* assert remaining length is at least 3 (for packet id and at least 1 topic) */
    if (remaining_length < 3) {
        return MQTT_ERROR_MALFORMED_RESPONSE;
    }

    /* unpack packet_id */
    mqtt_response->decoded.suback.packet_id = (uint16_t) ntohs(*(uint16_t*) buf);
    buf += 2;
    remaining_length -= 2;

    /* unpack return codes */
    mqtt_response->decoded.suback.num_return_codes = (size_t) remaining_length;
    mqtt_response->decoded.suback.return_codes = buf;
    buf += remaining_length;

    return buf - start;
}