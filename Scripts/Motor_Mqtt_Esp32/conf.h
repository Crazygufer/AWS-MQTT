#include <pgmspace.h>

#define SECRET
#define THINGNAME "Motor_NoSerie_12345"

const char WIFI_SSID[] = "Agregar aquí la red wifi";
const char WIFI_PASSWORD[] = "Agregar aquí la contraseña de la red wifi";
const char AWS_IOT_ENDPOINT[] = "este valor aparece en configuración de la cuenta en AWS IOT CORE";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
  "pegar aquí el certificado, hay que sacar las comillas y debe incluir la parte de -begin- y de -end-"
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
"pegar aquí el certificado, hay que sacar las comillas y debe incluir la parte de -begin- y de -end-"
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
"pegar aquí el certificado, hay que sacar las comillas y debe incluir la parte de -begin- y de -end-"
)KEY";