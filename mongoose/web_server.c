// Copyright (c) 2021 Cesanta Software Limited
// All rights reserved

#include "mongoose.h"

static struct mg_mgr mgr;
// Note: actual IP address should be set in web_server.h
// Default is 192.168.0.1
static const char *s_listening_address = "http://0.0.0.0:80";

static void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_HTTP_MSG) {
    mg_http_reply(c, 200, "", "hello, %s!\n", "world");
  }
  (void) fn_data;
  (void) ev_data;
}

void mg_run_server() {
  mg_mgr_init(&mgr);
  LOG(LL_INFO, ("Starting Mongoose v%s", MG_VERSION)); // Tell the world
  void *c = mg_http_listen(&mgr, s_listening_address, cb, &mgr); // Web listener
  while (c) {
	  mg_mgr_poll(&mgr, 100); // Infinite event loop
  }
  mg_mgr_free(&mgr); // Unreachable
}
