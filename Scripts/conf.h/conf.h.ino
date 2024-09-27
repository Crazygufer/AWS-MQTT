#include <pgmspace.h>

#define SECRET
#define THINGNAME "Motor_NoSerie_12345"

const char WIFI_SSID[] = "Wifi_Gufer";
const char WIFI_PASSWORD[] = "84226869";
const char AWS_IOT_ENDPOINT[] = "a17ljl77dug8n1-ats.iot.ap-southeast-2.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE----- : AmazonRootCA1.pem
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAMOcEgah8XaZexSgZnp7lxIeIJzrMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDA5MTUxMTQ1
MDdaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDIYa2nzVyuzGTuWopR
yrv0v2MKVzIZj6gj6yBPlCvovRkjGvYJoGolocEbX1/MKwdipIh98HwcWGDpBB/i
iqEWAnxTx6S74y7yrsJWQAWgGH8aJr9JctWtflp9W3o+69zr9F04JTjLCzLq1qeM
Z+Lt0khkauWBbxhqAYGbv9UkVeMduSwaqpye5uZWyL9/HrpqpoZjhgCHsI6uSkV6
zbztpIKpiSRpXT02iEz45BUOdOzXT0PBI9M/86ZBs1hNEhI9nThgUKdBlIw+Z5l0
UVnQoP+bPOC0L8jTFBgl5CJ8QcBgyaqQKzJsst3TNM5opUMJNgW6uA9+Zy+5o6E0
0CdLAgMBAAGjYDBeMB8GA1UdIwQYMBaAFEEILXoJZl9PJXf1LhE22f3OGwg/MB0G
A1UdDgQWBBRei1D7/FMESzFvtU1rtrkALu0ZozAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEATFijU0U0RSQen/ebs0+v8Nlf
/rlHBpO1i3PGruAPdsfdX6/PlUySQlVwambet9sDYvgzfSkTUp5k5AdnImo1JpZu
w3f/QgZZeN6GPg28ZoJOfE66arHUcCZbSee9wyAJFn7VjLGX9ci4VYnRuEeslDge
thPY1BbK26NwyTF2G9kugAkiL5kSKoRE7amb5fpIfkUZuSNaJue+F5sSeMNVyr/0
/WWxHqk5GQqg/U+8tq5XBZcVMHrO3pXFUwiLtvTs6OGIyqQJ1RjSJEXDDkcIkiii
A9mgqv7GQSOOzxfUwiLinqSlLun2CxIx6eYZPCiPzvuEiW5jp9KOQQZIP2fC5g==
-----END CERTIFICATE-----
: certificate.pem.crt
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAyGGtp81crsxk7lqKUcq79L9jClcyGY+oI+sgT5Qr6L0ZIxr2
CaBqJaHBG19fzCsHYqSIffB8HFhg6QQf4oqhFgJ8U8eku+Mu8q7CVkAFoBh/Gia/
SXLVrX5afVt6Puvc6/RdOCU4ywsy6tanjGfi7dJIZGrlgW8YagGBm7/VJFXjHbks
GqqcnubmVsi/fx66aqaGY4YAh7COrkpFes287aSCqYkkaV09NohM+OQVDnTs109D
wSPTP/OmQbNYTRISPZ04YFCnQZSMPmeZdFFZ0KD/mzzgtC/I0xQYJeQifEHAYMmq
kCsybLLd0zTOaKVDCTYFurgPfmcvuaOhNNAnSwIDAQABAoIBAQCMI5QZiQxKy3PD
JtsZvNman8caUkUdj1SeWjBst0nGKYnM/WwY63GRBAFTrW4IEgfGOx+iRG/oOv77
uAC8pQtnozFkPnm9VXNeEk6jl37XqooptfON4JwEDBwpE7L5EmedNXeEbrO7fQeN
KbZgAb+5Z5ltcT01OocujAMi9BSSpaktsnfOOXmWPqefw4enqylEErVlAs2BNlqk
S5S9OC//8QJLB8QVgjRULaRI6WnayYso8jaDrI2QehJ9zLsHO6UdCNc2mjOeX4IU
BPdHR6p8ECzZm+QrVtI0Lsr01PmMjAvUOnXM8v0DvOqKKtYpdRwH5Wiphd2DYV6o
jDLQa3WhAoGBAPAAtTpMs2dw8OMCqBD+3zUZNzbxJvwIMy+Kw6G6Q1f4j7YdCbum
yYPqSAFDHKuiKHhNqy2OEvaSTSDUc63lJsIb9OaTtyGAGd6lVPz5GJQxDVRejUqF
QfkTulwdXqipUK/MYsbgKYc6fRWs1hT9YAPIthuuLcMpPGHRivkHOF+JAoGBANW8
5KK+zL+v64v3hAa+QJw7zBYb3/38Qa/pKzCtgvs5uyQsA//wFcZJjEmpqQ599oTa
+opGfF+gklGvP/OTFEYyZxeXcP5oZbr+irv1iUItvkTemgoeHIe2f2sR3ycKTl81
hBbuWJapBcS247LzE8wK3GHwfM8uCtVbpEievWczAoGATCVdWm7laMdblhrMqf/D
X7xtWUAvxzzuyIG1SgWnwix5pCUYZnInc3QMfmIFoarkPi8eRWjTOWn3kJf3T8/p
eSKXk+R/8OAM1SgNi+mYU8QwX3lUSLV41gbdVMZ4tvhpQi2NlV2fr2juMMdScPxm
zyyKIsQjfs0BfGOYPSR+TUkCgYEAlf0WXPaT7DhhjTlGlwzPflOgJiuthiiNWArC
WkiI0A91Oi8BJ4utXBaksdSzZA4U/qpEguBvyxN9WoEm2aDu60vXeIC3tHBCY3TY
mon1plE/YkjrxAnZb4sr41EJTfY3hSyi4wyjciZue9rz8tINpHRCrx/6FdFznMHQ
iX2L4G0CgYEAyBP/NpAGnnXnw+6JmrazmXsno8LzJTq45q/izZ9/QJf43dGPkKsB
0+3LlQRyCWwFLhnomxjnGb4IouhbKsSpelBLltvLGLssIy7BL7QygIqwPnFVvDlw
rTV3TwZQANizboHH18on1BJkdxkPjULcUyo5cy5LnDkDoKchj/hDRFc=
-----END RSA PRIVATE KEY-----
: private.pem.key
)KEY";