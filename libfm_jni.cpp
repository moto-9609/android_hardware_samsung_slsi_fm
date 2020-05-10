/*
 * Copyright (C) 2020 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <jni.h>
#include <log/log.h>
#include <math.h>
#include "FmRadioController_slsi.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "FMLIB_SLSI_JNI"

static FmRadioController_slsi * pFMRadio = NULL;

jboolean openDev(JNIEnv *env, jobject thiz)
{
    pFMRadio = new FmRadioController_slsi();
    
    if (pFMRadio->Initialise() == 0) {
        ALOGI("%s FM Radio Initialized Successfully\n", __func__);
        return JNI_TRUE;
    }

    ALOGE("%s failed to initialise FmRadio\n", __func__);
    return JNI_FALSE;
}

jboolean closeDev(JNIEnv *env, jobject thiz)
{
    delete pFMRadio;
    pFMRadio = NULL;
    ALOGI("%s FM Radio Un-Initialized Successfully\n", __func__);

    return JNI_TRUE;
}

jboolean powerUp(JNIEnv *env, jobject thiz, jfloat freq)
{
    pFMRadio->TuneChannel((int)(freq * 1000.00000000));
    ALOGI("%s [freq=%d] \n", __func__, (int)freq);

    return JNI_TRUE;
}

jboolean powerDown(JNIEnv *env, jobject thiz, jint type)
{
    ALOGI("%s \n", __func__);

    return JNI_TRUE;
}

jboolean tune(JNIEnv *env, jobject thiz, jfloat freq)
{
    pFMRadio->TuneChannel((int)(freq * 1000.00000000));
    ALOGI("%s [freq=%d] \n", __func__, (int)freq);

    return JNI_TRUE;
}

jfloat seek(JNIEnv *env, jobject thiz, jfloat freq, jboolean isUp) //jboolean isUp;
{
    int ret;
    if (isup == JNI_TRUE) {
        ret = pFMRadio->SeekUp();
    } else {
        ret = pFMRadio->SeekDown();
    }

    ALOGI("%s [freq=%d] \n", __func__, ret);

    return roundf((ret/1000.00F) * 100) / 100;
}

jshortArray autoScan(JNIEnv *env, jobject thiz)
{
    ALOGD("%s not supported \n", __func__);

    return JNI_FALSE;
}

jshort readRds(JNIEnv *env, jobject thiz)
{
    ALOGD("%s not supported \n", __func__);

    return JNI_FALSE;
}

jbyteArray getPs(JNIEnv *env, jobject thiz)
{
    ALOGI("%s \n", __func__);
    // TODO
    jbyteArray PSName;
    uint8_t *rt = NULL;
    int rt_len = 0;
    PSName = env->NewByteArray(rt_len);
    env->SetByteArrayRegion(PSName, 0, rt_len, (const jbyte*)rt);
    return PSName;
}

jbyteArray getLrText(JNIEnv *env, jobject thiz)
{
    ALOGI("%s \n", __func__);
    // TODO
    jbyteArray PSName;
    uint8_t *rt = NULL;
    int rt_len = 0;
    PSName = env->NewByteArray(rt_len);
    env->SetByteArrayRegion(PSName, 0, rt_len, (const jbyte*)rt);
    return PSName;
}

jshort activeAf(JNIEnv *env, jobject thiz)
{
    ALOGI("%s \n", __func__);
    
    int ret = pFMRadio->GetChannel();

    return roundf((ret/1000.00F) * 100) / 100;
}

jshortArray getAFList(JNIEnv *env, jobject thiz)
{
    ALOGD("%s not supported \n", __func__);

    return JNI_FALSE;
}

jint setRds(JNIEnv *env, jobject thiz, jboolean rdson)
{
    if (rdson == JNI_TRUE) {
        pFMRadio->EnableRDS();
    } else {
        pFMRadio->DisableRDS();
    }

    ALOGI("%s\n", __func__);

    return JNI_TRUE;
}

jboolean stopScan(JNIEnv *env, jobject thiz)
{
    ALOGD("%s not supported \n", __func__);

    return JNI_TRUE;
}

jint setMute(JNIEnv *env, jobject thiz, jboolean mute)
{
    if (mute == JNI_TRUE) {
        pFMRadio->MuteOn();
    } else {
        pFMRadio->MuteOff();
    }

    ALOGI("%s  [mute=%d] \n", __func__, (int)mute);

    return JNI_TRUE;
}

jint isRdsSupport(JNIEnv *env, jobject thiz)
{
    ALOGD("%s not supported \n", __func__);

    return JNI_FALSE;
}

jint switchAntenna(JNIEnv *env, jobject thiz, jint antenna)
{
    ALOGD("%s not supported \n", __func__);

    return JNI_FALSE;
}

static const char *classPathNameRx = "com/android/fmradio/FmNative";

static JNINativeMethod methodsRx[] = {
    { "openDev", "()Z", (void*)openDev },
    { "closeDev", "()Z", (void*)closeDev },
    { "powerUp", "(F)Z", (void*)powerUp },
    { "powerDown", "(I)Z", (void*)powerDown },
    { "tune", "(F)Z", (void*)tune },
    { "seek", "(FZ)F", (void*)seek },
    { "autoScan", "()[S", (void*)autoScan },
    { "stopScan", "()Z", (void*)stopScan },
    { "setRds", "(Z)I", (void*)setRds },
    { "readRds", "()S", (void*)readRds },
    { "getPs", "()[B", (void*)getPs },
    { "getLrText", "()[B", (void*)getLrText },
    { "activeAf", "()S", (void*)activeAf },
    { "setMute", "(Z)I", (void*)setMute },
    { "isRdsSupport", "()I", (void*)isRdsSupport },
    { "switchAntenna", "(I)I", (void*)switchAntenna },
};

/*
 * Register several native methods for one class.
 */
static jint registerNativeMethods(JNIEnv* env, const char* className,
    JNINativeMethod* gMethods, int numMethods)
{
    jclass clazz;

    clazz = env->FindClass(className);
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
    if (clazz == NULL) {
        ALOGE("Native registration unable to find class '%s'", className);
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        ALOGE("RegisterNatives failed for '%s'", className);
        return JNI_FALSE;
    }

    ALOGD("%s, success\n", __func__);
    return JNI_TRUE;
}

/*
 * Register native methods for all classes we know about.
 *
 * returns JNI_TRUE on success.
 */
static jint registerNatives(JNIEnv* env)
{
    jint ret = JNI_FALSE;

    if (registerNativeMethods(env, classPathNameRx,methodsRx,
        sizeof(methodsRx) / sizeof(methodsRx[0]))) {
        ret = JNI_TRUE;
    }

    ALOGD("%s, done\n", __func__);
    return ret;
}

// ----------------------------------------------------------------------------

/*
 * This is called by the VM when the shared library is first loaded.
 */

typedef union {
    JNIEnv* env;
    void* venv;
} UnionJNIEnvToVoid;

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    UnionJNIEnvToVoid uenv;
    uenv.venv = NULL;
    jint result = -1;
    JNIEnv* env = NULL;

    ALOGI("JNI_OnLoad");

    if (vm->GetEnv(&uenv.venv, JNI_VERSION_1_4) != JNI_OK) {
        ALOGE("ERROR: GetEnv failed");
        goto fail;
    }
    env = uenv.env;

    if (registerNatives(env) != JNI_TRUE) {
        ALOGE("ERROR: registerNatives failed");
        goto fail;
    }

    result = JNI_VERSION_1_4;

fail:
    return result;
}
