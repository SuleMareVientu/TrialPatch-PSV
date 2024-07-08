#include <taihen.h>
#include <vitasdk.h>

#define SCE_APPUTIL_APPPARAM_ID_SKU_FLAG 0

#define SCE_APPUTIL_APPPARAM_SKU_FLAG_NONE 0
#define SCE_APPUTIL_APPPARAM_SKU_FLAG_TRIAL 1
#define SCE_APPUTIL_APPPARAM_SKU_FLAG_FULL 3

static SceUID hook;
static tai_hook_ref_t ref_hook;
int sceAppUtilAppParamGetInt_patch(int param, int *value) {
	int res = TAI_CONTINUE(int, ref_hook, param, value);
	if (res >= 0) {
		if (param == SCE_APPUTIL_APPPARAM_ID_SKU_FLAG)
			*value = SCE_APPUTIL_APPPARAM_SKU_FLAG_FULL;
	}
	return res;
}

void _start() __attribute__ ((weak, alias ("module_start")));

int module_start(SceSize argc, const void *args) {
	hook = taiHookFunctionImport(&ref_hook,
		TAI_MAIN_MODULE,
		TAI_ANY_LIBRARY,
		0xCD7FD67A, // sceAppUtilAppParamGetInt
		sceAppUtilAppParamGetInt_patch);

	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) {
	taiHookRelease(hook, ref_hook);
	return SCE_KERNEL_STOP_SUCCESS;
}