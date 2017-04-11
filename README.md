# C_Mockup
Little quick and dirty C program for testing the AppDynamics C SDK. In this case we have two versions, one with and one without instrumentation.

This does not do much but simulate Transactions happening that issue calls to backends like HTTP or database calls.
Just compile and execute, there are no other requirements than a C compiler.

When doing a simple compile without makefile etc., be sure to add the sdk.so library, otherwise you will get errors about undefined references:

  path-to-c_app$ gcc c_app.c appdynamics-sdk-native/sdk_lib/lib/libappdynamics_native_sdk.so
  
In this example the sdk was extracted to the same directory as the actual c application, otherwise please adjust the location accordingly.

IMPORTANT: Also adjust the Controller location and access key (and maybe the SDK location for the include), otherwise the agent will not be able to send it's data.

TODO - 
There is a lot of stuff that has not yet happened here. The things that come from the top of my mind are:
- Additional BTs and backends - this is very limited at the moment
- Consistent BT behavior calls - right now everything (backend calls, execution time, etc. ) is completely random
- Add data to exit calls like SQL statements or URLs, etc.
- Add User Data - Not being used at the moment.
- Add snapshot information when a snapshot is happening.
- Up- and Downstream correlation, so that this becomes part of a bigger application.

If you have anything that you think makes sense, please let me know: thomas.klughardt@appdynamics.com
