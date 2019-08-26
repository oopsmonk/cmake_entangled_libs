/*
 * Copyright (c) 2019 IOTA Stiftung
 *
 * Refer to the LICENSE file for licensing information
 */

#include <stdio.h>
#include <inttypes.h>

#include "utils/time.h"
#include "common/errors.h"
#include "cclient/api/core/core_api.h"
#include "cclient/api/extended/extended_api.h"
#include "utils/logger_helper.h"
#include "utils/time.h"

static char const *amazon_ca1_pem =
    "-----BEGIN CERTIFICATE-----\r\n"
    "MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\r\n"
    "ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\r\n"
    "b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\r\n"
    "MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\r\n"
    "b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\r\n"
    "ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\r\n"
    "9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\r\n"
    "IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\r\n"
    "VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\r\n"
    "93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\r\n"
    "jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\r\n"
    "AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\r\n"
    "A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\r\n"
    "U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\r\n"
    "N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\r\n"
    "o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\r\n"
    "5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\r\n"
    "rqXRfboQnoZsG4q5WTP468SQvvG5\r\n"
    "-----END CERTIFICATE-----\r\n";

void example_node_info(iota_client_service_t *s) {
  printf("\n[%s]\n", __FUNCTION__);
  retcode_t ret = RC_ERROR;
  get_node_info_res_t *node_res = get_node_info_res_new();
  if (node_res == NULL) {
    printf("Error: OOM\n");
    return;
  }

  if ((ret = iota_client_get_node_info(s, node_res)) == RC_OK) {
    printf("appName %s \n", get_node_info_res_app_name(node_res));
    printf("appVersion %s \n", get_node_info_res_app_version(node_res));

    printf("latestMilestone: ");
    flex_trit_print(node_res->latest_milestone, NUM_TRITS_HASH);
    printf("\n");

    printf("latestMilestoneIndex %u \n", node_res->latest_milestone_index);

    printf("latestSolidSubtangleMilestone: ");
    flex_trit_print(node_res->latest_solid_subtangle_milestone, NUM_TRITS_HASH);
    printf("\n");

    printf("latestSolidSubtangleMilestoneIndex %u \n", node_res->latest_solid_subtangle_milestone_index);
    printf("neighbors %d \n", node_res->neighbors);
    printf("packetsQueueSize %d \n", node_res->packets_queue_size);
    printf("time %" PRIu64 " \n", node_res->time);
    printf("tips %d \n", node_res->tips);
    printf("transactionsToRequest %d \n", node_res->transactions_to_request);
  } else {
    printf("Error: %s", error_2_string(ret));
  }

  get_node_info_res_free(&node_res);
}

int main() {
  iota_client_service_t serv;
  serv.http.path = "/";
  serv.http.content_type = "application/json";
  serv.http.accept = "application/json";
  serv.http.host = "nodes.devnet.iota.org";
  serv.http.port = 443;
  serv.http.api_version = 1;
  serv.serializer_type = SR_JSON;
  serv.http.ca_pem = amazon_ca1_pem;
  logger_helper_init(LOGGER_DEBUG);

  iota_client_core_init(&serv);
  iota_client_extended_init();

  printf("Connecting to node: https://%s:%u\n", serv.http.host, serv.http.port);

  /* Core APIs */
  example_node_info(&serv);
  return 0;
}
