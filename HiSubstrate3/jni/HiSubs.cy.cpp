
#include <jni.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <dlfcn.h>

#include <substrate.h>


/***********************************************************************************************
 *
 * config
 *
 ***********************************************************************************************/

//MSConfig(MSFilterLibrary, "libsec-ril.so")
//MSConfig(MSFilterExecutable, "/system/bin/rild")
MSConfig(MSFilterLibrary, "liblog.so")

/***********************************************************************************************
 *
 * common
 *
 ***********************************************************************************************/



/***********************************************************************************************
 *
 * libsec-ril.so requestSendSMS
 *
 ***********************************************************************************************/

typedef void * RIL_Token;

void (* old_requestSendSMS)(void *, size_t, RIL_Token);

static void new_requestSendSMS(void *data, size_t datalen, RIL_Token t)
{
	old_requestSendSMS(data, datalen, t);
}

/***********************************************************************************************
 *
 * initialize.... do HOOK
 *
 ************************************************************************************************/
//#ifndef RTLD_NEXT
//#define RTLD_NEXT ((int)-1l)
//#endif

MSInitialize
{
	void (* requestSendSMS)(void *, size_t, RIL_Token);
	requestSendSMS = (void (*)(void *, size_t, RIL_Token)) MSFindSymbol (NULL, "requestSendSMS");
	if (requestSendSMS != NULL)
	{
		MSHookFunction(requestSendSMS, &new_requestSendSMS, &old_requestSendSMS);
	}

}
