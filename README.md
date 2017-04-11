# C_Mockup
Little quick and dirty C program for testing the AppDynamics C SDK

This does not do much but simulate Transactions happening that issue calls to backends like HTTP or database calls.
Just compile and execute, there are no other requirements than a C compiler.

When doing a simple compile without makefile etc., be sure to add the sdk.so library, otherwise you will get errors about undefined references:

path-to-agent$ gcc c_app.c appdynamics-sdk-native/sdk_lib/lib/libappdynamics_native_sdk.so

In this example the sdk was extracted to the same directory as the actual c application.

