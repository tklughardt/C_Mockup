#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int get_call_time() {
	// Helper routine, returns a duration for a backend call
 	int duration = rand() % 5;
	fprintf(stderr, "duration for call is : %i seconds... ", duration);
	return duration;
}

void call_to_database_backend_1() {

	fprintf(stderr, "Calling Database Backend 1 ... ");
	// Exit Call starts here

	sleep((int)get_call_time());

	// and ends here
	printf("done\n");

}

void call_to_http_backend1() {

	fprintf(stderr, "Calling HTTP Backend 1 ... ");
	// Exit Call starts here

	sleep((int)get_call_time());

	// and ends here
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

	// BT Call starts here
	int status = core_logic();
	// and has ended here

	printf ("BT 1 is done \n");

	return 0;
}

int call_to_bt2() {
	// Let's assume that a BT starts in this routine, that does some exit calls to varying backends.
	printf ("BT2 is starting... \n");

	// BT Call starts here
	int status = core_logic();
	// and has ended here

	printf ("BT 2 is done \n");

	return 0;
}

int main() {

    printf("***********************************************\n");
	printf("* Simple C Mockup App for testing C/C++ Agent *\n");
	printf("* @Author Thomas.Klughardt@appdynamics.com     *\n");
    printf("***********************************************\n");

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

	return 0;
}

