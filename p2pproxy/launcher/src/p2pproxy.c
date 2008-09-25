#include <stdio.h>
#include <jni.h>
#include "p2pproxy.h"

#ifndef P2PPROXY_JMX_PORT
	#define P2PPROXY_JMX_PORT "5678"
#endif
#ifndef P2PPROXY_INSTALLDIR
	#define P2PPROXY_INSTALLDIR "/usr/local/share/java"
#endif 
#ifndef P2PPROXY_BUILDDIR
	#define P2PPROXY_BUILDDIR "./antbuild/dist/p2pproxy_0.1"
#endif
JNIEnv* p2pproxy_application_jnienv = 0;
JavaVM* p2pproxy_application_jvm = 0;

int p2pproxy_application_start(int argc, char **argv) {
	
	JavaVMInitArgs args;
	JavaVMOption options[0];
	jint res=-1;
	
	if (p2pproxy_application_jnienv != 0) {
		fprintf(stderr,"p2pproxy already started");
		return P2PPROXY_ERROR_APPLICATION_ALREADY_STARTED;
	}
	args.version = JNI_VERSION_1_4;
	args.nOptions = sizeof (options);
	/*options[0].optionString = "-verbose:jni";*/
	/*options[1].optionString = "-Djava.class.path="P2PPROXY_BUILDDIR"/p2pproxy.jar:"\
													P2PPROXY_INSTALLDIR"/p2pproxy.jar:"\
													P2PPROXY_BUILDDIR"/log4j.jar:"\
													P2PPROXY_INSTALLDIR"/log4j.jar";
	

/*
	options[1].optionString = "-Dcom.sun.management.jmxremote";
	options[2].optionString = "-Dcom.sun.management.jmxremote.port="P2PPROXY_JMX_PORT;
	options[3].optionString = "-Dcom.sun.management.jmxremote.authenticate=false";
	options[4].optionString = "-Dcom.sun.management.jmxremote.ssl=false";
	*/							
 		
	args.options = options;
	args.ignoreUnrecognized = JNI_FALSE;

	res = JNI_CreateJavaVM(&p2pproxy_application_jvm, (void **)&p2pproxy_application_jnienv, &args);
	if (res < 0) {
		fprintf(stderr,"cannot start p2pproxy vm [%i]",res);
		return P2PPROXY_ERROR;
	}
	return P2PPROXY_NO_ERROR;
}


const char* p2pproxy_status_string(int status_code) {
	return 0;
}


int p2pproxy_accountmgt_createAccount(const char* user_name) {
	return P2PPROXY_ERROR;
}

int p2pproxy_accountmgt_isValidAccount(const char* user_name) {
	return P2PPROXY_ERROR;
}

int p2pproxy_accountmgt_deleteAccount(const char* user_name) {
	return P2PPROXY_ERROR;
}



JNIEnv* create_vm() {

}

void invoke_class(JNIEnv* env) {
	jclass helloWorldClass;
	jmethodID mainMethod;
	jobjectArray applicationArgs;
	jstring applicationArg0;

	helloWorldClass = (*env)->FindClass(env, "example/jni/InvocationHelloWorld");

	mainMethod = (*env)->GetStaticMethodID(env, helloWorldClass, "main", "([Ljava/lang/String;)V");

	applicationArgs = (*env)->NewObjectArray(env, 1, (*env)->FindClass(env, "java/lang/String"), NULL);
	applicationArg0 = (*env)->NewStringUTF(env, "From-C-program");
	(*env)->SetObjectArrayElement(env, applicationArgs, 0, applicationArg0);

	(*env)->CallStaticVoidMethod(env, helloWorldClass, mainMethod, applicationArgs);
}


