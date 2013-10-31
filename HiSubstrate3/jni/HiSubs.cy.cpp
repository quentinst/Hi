
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

MSConfig(MSFilterLibrary, "libril.so")
//MSConfig(MSFilterLibrary, "libsec-ril.so")
//MSConfig(MSFilterExecutable, "/system/bin/rild")
//MSConfig(MSFilterLibrary, "liblog.so")

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
 * libril.so RIL_onUnsolicitedResponse
 *
 ***********************************************************************************************/
void (* old_RIL_onUnsolicitedResponse)(int unsolResponse, void *data, size_t datalen);
void new_RIL_onUnsolicitedResponse(int unsolResponse, void *data, size_t datalen)
{

	FILE *f2 = fopen("/sdcard/a.log", "a+");
	fputs("-------------------------------------", f2);
	fclose(f2);

	old_RIL_onUnsolicitedResponse(unsolResponse, data, datalen);
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
//	void (* p_requestSendSMS)(void *, size_t, RIL_Token);
//	p_requestSendSMS = (void (*)(void *, size_t, RIL_Token)) MSFindSymbol (NULL, "requestSendSMS");
//	if (p_requestSendSMS != NULL)
//	{
//		MSHookFunction(p_requestSendSMS, &new_requestSendSMS, &old_requestSendSMS);
//	}

	char c[1024];
	FILE *f;

	f = fopen("/sdcard/a.log", "a+");
	fputs("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n", f);
	fclose(f);


	void (* p_RIL_onUnsolicitedResponse)(int, void *, size_t);
	f = fopen("/sdcard/a.log", "a+");
	fputs("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n", f);
	fclose(f);

	p_RIL_onUnsolicitedResponse = (void (*)(int, void *, size_t)) MSFindSymbol (NULL, "RIL_onUnsolicitedResponse");

	f = fopen("/sdcard/a.log", "a+");
	fputs("cccccccccccccccccccccccccccccc\n", f);
	fclose(f);

	f = fopen("/sdcard/a.log", "a+");
	memset(c, 0, sizeof(c));
	sprintf(c, "p_RIL_onUnsolicitedResponse = %x", (int)p_RIL_onUnsolicitedResponse);
	fputs(c, f);
	fclose(f);

	if (p_RIL_onUnsolicitedResponse != NULL)
	{
		f = fopen("/sdcard/a.log", "a+");
		memset(c, 0, sizeof(c));
		sprintf(c, "p_RIL_onUnsolicitedResponse = %x", (int)p_RIL_onUnsolicitedResponse);
		fputs(c, f);
		fclose(f);

		MSHookFunction(p_RIL_onUnsolicitedResponse, &new_RIL_onUnsolicitedResponse, &old_RIL_onUnsolicitedResponse);

		f = fopen("/sdcard/a.log", "a+");
		fputs("ddddddddddddddddddddddddddddddddd\n", f);
		fclose(f);
	}

	f = fopen("/sdcard/a.log", "a+");
	fputs("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n", f);
	fclose(f);

}
