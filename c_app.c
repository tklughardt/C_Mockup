#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "/opt/C_Test/appdynamics-sdk-native/sdk_lib/appdynamics.h"

appd_bt_handle btHandle;
char db_backend_1[] = "DB_BACKEND_1";
char http_backend_1[] = "HTTP_BACKEND_1";


// ---- Initialization of AppDynamics ------
static int init_appdynamics(void) {
	struct appd_config cfg;
	int initRC;

	appd_config_init(&cfg);

	cfg.app_name              = "Mockup";
	cfg.tier_name             = "CoreTier";
	cfg.node_name             = "CoreNode";
	cfg.controller.host       = "seenablementbootca";
	cfg.controller.port       = 8090;
	cfg.controller.account    = "customer1";
	cfg.controller.access_key = "81ce07b1-79df-42c0-811b-a763f6cfb294";
	cfg.controller.use_ssl    = 0;
	cfg.init_timeout_ms       = -1;

	fprintf(stderr, "Initializing AppDynamics SDK... ");
	initRC = appd_sdk_init(&cfg);

	if (initRC != 0) {
	fprintf(stderr, "appd_sdk_init failed: %d\n", initRC);
	return 1;
  }

  	fprintf(stderr, "Initialization successful.\n");
  	return 0;
  }

// ---- De-initialization of AppDynamics ----
static void deinit_appdynamics(void) {
	fprintf(stderr, "Terminating AppDynamics SDK... ");
	appd_sdk_term();
	fprintf(stderr, "AppDynamics SDK successfully terminated.\n");
}

// ---- Declarations for AppDynamics ------

static void declareBackends() {

	int status;

	fprintf(stderr, "Declaring Backends.\n");

	appd_backend_declare(APPD_BACKEND_HTTP, http_backend_1);
	status = appd_backend_set_identifying_property(http_backend_1, "HOST", "Mockup_HTTP_Backend");
	if (status != 0) {
		fprintf(stderr, "Error setting identifying property for HTTP Backend: %i.\n", status);
	}

	status = appd_backend_prevent_agent_resolution(http_backend_1);
	if (status != 0) {
		fprintf(stderr, "Error Turning off backend to tier resolution for HTTP Backend: %i.\n", status);
	}

	status = appd_backend_add(http_backend_1);
	if (status) {
   		fprintf(stderr, "Error: appd_backend_add for http_backend_1: %i.\n", status);
	}

	appd_backend_declare(APPD_BACKEND_DB, db_backend_1);
	status = appd_backend_set_identifying_property(db_backend_1, "HOST", "Mockup_DB_Backend");
	if (status != 0) {
		fprintf(stderr, "Error setting identifying property for DB Backend: %i.\n", status);
	}
	status = appd_backend_prevent_agent_resolution(db_backend_1);
	if (status != 0) {
		fprintf(stderr, "Error Turning off backend to tier resolution for DB Backend: %i.\n", status);
	}

	status = appd_backend_add(db_backend_1);
	if (status) {
   		fprintf(stderr, "Error: appd_backend_add for db_backend_1: %i.\n", status);
	}
}

// ---- Actual Application begins here ------

int get_call_time() {
	// Helper routine, returns a duration for a backend call
 	int duration = rand() % 5;
	fprintf(stderr, "duration for call is : %i seconds... ", duration);
	return duration;
}

void call_to_database_backend_1() {

	fprintf(stderr, "Calling Database Backend 1 ... ");
	// Exit Call starts here

	appd_exitcall_handle ecHandle = appd_exitcall_begin(btHandle, db_backend_1);

	int rc = appd_exitcall_set_details(ecHandle, "DB_BACKEND_1");
	if (rc) {
   		fprintf(stderr, "Error: exitcall details1");
	}

	sleep((int)get_call_time());

	// and ends here
	appd_exitcall_end(ecHandle);

	printf("done\n");

}

void call_to_http_backend1() {

	fprintf(stderr, "Calling HTTP Backend 1 ... ");
	// Exit Call starts here

	appd_exitcall_handle ecHandle = appd_exitcall_begin(btHandle, http_backend_1);

	int rc = appd_exitcall_set_details(ecHandle, "HTTP_BACKEND_1");
	if (rc) {
   		fprintf(stderr, "Error: exitcall details1");
	}

	sleep((int)get_call_time());

	// and ends here
	appd_exitcall_end(ecHandle);

	printf("done\n");

}

int core_logic() {
	// This is the core logic routine. It does up to 10 mock up backend calls.
	// Of course you could also write the logic directly into the BT calls as well.
	// It is not necessary to instrument anything here.

	// Call up to 10 backends
	int s =  rand() % 10;
	printf ("Calling %i of backends in this Transaction\n", s);

	int i;
	for (i = 0; i < s; i = i + 1) {
		int backend = rand() % 2;

		if (backend == 0) {
			call_to_database_backend_1();
		}
		else if (backend == 1) {
			call_to_http_backend1();
		}
		else {
			// something is wrong
			break;
		}
	}

	return 0;
}

int call_to_bt1() {
	// Let's assume that a BT starts in this routine, that does some exit calls to varying backends.
	printf ("BT1 is starting... \n");

	btHandle = appd_bt_begin("BT1", NULL);
	// BT Call starts here
	int status = core_logic();
	// and has ended here
	appd_bt_end(btHandle);


	printf ("BT 1 is done \n");

	return 0;
}

int call_to_bt2() {
	// Let's assume that a BT starts in this routine, that does some exit calls to varying backends.
	printf ("BT2 is starting... \n");

	btHandle = appd_bt_begin("BT2", NULL);
	// BT Call starts here
	int status = core_logic();
	// and has ended here
	appd_bt_end(btHandle);

	printf ("BT 2 is done \n");

	return 0;
}

int main() {

	printf("***********************************************\n");
	printf("* Simple C Mockup App for testing C/C++ Agent *\n");
	printf("* @Author Thomas.Klughardt@appdynamics.com    *\n");
	printf("***********************************************\n");

	// Initialize AppDynamics agent
	if(init_appdynamics() != 0)
    	exit(0);

	declareBackends();

	for(;;) {

		int r = rand() % 2;

		// TODO - add additional BTs to call, two is a bit boring
		if (r == 0) {
			int status = call_to_bt1();
		}
		else if (r == 1) {
			int status = call_to_bt2();
		}
		else {
			// something is wrong
			break;
		}

		sleep(2);
	}

	// De-initialize AppDynamics agent
	  deinit_appdynamics();

	return 0;
}

