#include "pgmspace.h"

extern const char* isrgrootx1_cert;
extern const char* cloudflare_cert;
extern const char* deploy_the_fleet_cert;
extern const int CERT_BUNDLE_ID;

constexpr const int CERT_BUNDLE_ID = 1;

const char* isrgrootx1_cert PROGMEM = \
"-----BEGIN CERTIFICATE-----\n" \
"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\n" \
"-----END CERTIFICATE-----\n";

const char* cloudflare_cert PROGMEM = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIEADCCAuigAwIBAgIID+rOSdTGfGcwDQYJKoZIhvcNAQELBQAwgYsxCzAJBgNV\n" \
"BAYTAlVTMRkwFwYDVQQKExBDbG91ZEZsYXJlLCBJbmMuMTQwMgYDVQQLEytDbG91\n" \
"ZEZsYXJlIE9yaWdpbiBTU0wgQ2VydGlmaWNhdGUgQXV0aG9yaXR5MRYwFAYDVQQH\n" \
"Ew1TYW4gRnJhbmNpc2NvMRMwEQYDVQQIEwpDYWxpZm9ybmlhMB4XDTE5MDgyMzIx\n" \
"MDgwMFoXDTI5MDgxNTE3MDAwMFowgYsxCzAJBgNVBAYTAlVTMRkwFwYDVQQKExBD\n" \
"bG91ZEZsYXJlLCBJbmMuMTQwMgYDVQQLEytDbG91ZEZsYXJlIE9yaWdpbiBTU0wg\n" \
"Q2VydGlmaWNhdGUgQXV0aG9yaXR5MRYwFAYDVQQHEw1TYW4gRnJhbmNpc2NvMRMw\n" \
"EQYDVQQIEwpDYWxpZm9ybmlhMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKC\n" \
"AQEAwEiVZ/UoQpHmFsHvk5isBxRehukP8DG9JhFev3WZtG76WoTthvLJFRKFCHXm\n" \
"V6Z5/66Z4S09mgsUuFwvJzMnE6Ej6yIsYNCb9r9QORa8BdhrkNn6kdTly3mdnykb\n" \
"OomnwbUfLlExVgNdlP0XoRoeMwbQ4598foiHblO2B/LKuNfJzAMfS7oZe34b+vLB\n" \
"yrP/1bgCSLdc1AxQc1AC0EsQQhgcyTJNgnG4va1c7ogPlwKyhbDyZ4e59N5lbYPJ\n" \
"SmXI/cAe3jXj1FBLJZkwnoDKe0v13xeF+nF32smSH0qB7aJX2tBMW4TWtFPmzs5I\n" \
"lwrFSySWAdwYdgxw180yKU0dvwIDAQABo2YwZDAOBgNVHQ8BAf8EBAMCAQYwEgYD\n" \
"VR0TAQH/BAgwBgEB/wIBAjAdBgNVHQ4EFgQUJOhTV118NECHqeuU27rhFnj8KaQw\n" \
"HwYDVR0jBBgwFoAUJOhTV118NECHqeuU27rhFnj8KaQwDQYJKoZIhvcNAQELBQAD\n" \
"ggEBAHwOf9Ur1l0Ar5vFE6PNrZWrDfQIMyEfdgSKofCdTckbqXNTiXdgbHs+TWoQ\n" \
"wAB0pfJDAHJDXOTCWRyTeXOseeOi5Btj5CnEuw3P0oXqdqevM1/+uWp0CM35zgZ8\n" \
"VD4aITxity0djzE6Qnx3Syzz+ZkoBgTnNum7d9A66/V636x4vTeqbZFBr9erJzgz\n" \
"hhurjcoacvRNhnjtDRM0dPeiCJ50CP3wEYuvUzDHUaowOsnLCjQIkWbR7Ni6KEIk\n" \
"MOz2U0OBSif3FTkhCgZWQKOOLo1P42jHC3ssUZAtVNXrCk3fw9/E15k8NPkBazZ6\n" \
"0iykLhH1trywrKRMVw67F44IE8Y=\n" \
"-----END CERTIFICATE-----\n";

const char* deploy_the_fleet_cert PROGMEM = \
"-----BEGIN CERTIFICATE-----\n" \
"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\n" \
"Hg==\n" \
"-----END CERTIFICATE-----\n";