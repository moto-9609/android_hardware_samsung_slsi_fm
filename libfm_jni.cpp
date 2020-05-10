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

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "FMLIB_JNI"

jboolean openDev(JNIEnv *env, jobject thiz)
{
}

jboolean closeDev(JNIEnv *env, jobject thiz)
{
}

jboolean powerUp(JNIEnv *env, jobject thiz, jfloat freq)
{
}

jboolean powerDown(JNIEnv *env, jobject thiz, jint type)
{
}

jboolean tune(JNIEnv *env, jobject thiz, jfloat freq)
{
}

jfloat seek(JNIEnv *env, jobject thiz, jfloat freq, jboolean isUp) //jboolean isUp;
{
}

jshortArray autoScan(JNIEnv *env, jobject thiz)
{
}

jshort readRds(JNIEnv *env, jobject thiz)
{
}

jbyteArray getPs(JNIEnv *env, jobject thiz)
{
}

jbyteArray getLrText(JNIEnv *env, jobject thiz)
{
}

jshort activeAf(JNIEnv *env, jobject thiz)
{
}

jshortArray getAFList(JNIEnv *env, jobject thiz)
{
}

jint setRds(JNIEnv *env, jobject thiz, jboolean rdson)
{
}

jboolean stopScan(JNIEnv *env, jobject thiz)
{
}

jint setMute(JNIEnv *env, jobject thiz, jboolean mute)
{
}

jint isRdsSupport(JNIEnv *env, jobject thiz)
{
}

jint switchAntenna(JNIEnv *env, jobject thiz, jint antenna)
{
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
