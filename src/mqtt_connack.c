#include <mqtt.h>
#include <mqtt_details.h>


ssize_t mqtt_unpack_connack_response(struct mqtt_response *mqtt_response, const uint8_t *buf) {
    const uint8_t const *start = buf;
    struct mqtt_response_connack *response;
    
    response = &(mqtt_response->decoded.connack);
    /* unpack */
    if (*buf & 0xFE) {
        /* only bit 1 can be set */
        return MQTT_ERROR_CONNACK_FORBIDDEN_FLAGS;
    } else {
        response->session_present_flag = *buf++;
    }

    if (*buf > 5u) {
        /* only bit 1 can be set */
        return MQTT_ERROR_CONNACK_FORBIDDEN_CODE;
    } else {
        response->return_code = (enum ConnackReturnCode) *buf++;
    }
    return buf - start;
}