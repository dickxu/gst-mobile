/*
 * Copyright 2013 The Android Open Source Project
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

#ifndef NATIVEHELPER_ALOGPRIV_H_
#define NATIVEHELPER_ALOGPRIV_H_

#include <android/log.h>

#ifndef LOG_TAG
#define LOG_TAG "k2player"
#define LOG_NDEBUG 0
#endif

#ifndef LOG_NDEBUG
#ifdef NDEBUG
#define LOG_NDEBUG 1
#else
#define LOG_NDEBUG 0
#endif
#endif


/*
 * Basic log message macros intended to emulate the behavior of log/log.h
 * in system core.  This should be dependent only on ndk exposed logging
 * functionality.
 */

#ifndef ALOG
#define ALOG(priority, tag, fmt...) \
    __android_log_print(ANDROID_##priority, tag, fmt)
#endif

#ifndef ALOGV
#if LOG_NDEBUG
#define ALOGV(...)   ((void)0)
#else
#define ALOGV(...) ((void)ALOG(LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#endif
#endif

#ifndef ALOGD
#define ALOGD(...) ((void)ALOG(LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#endif

#ifndef ALOGI
#define ALOGI(...) ((void)ALOG(LOG_INFO, LOG_TAG, __VA_ARGS__))
#endif

#ifndef ALOGW
#define ALOGW(...) ((void)ALOG(LOG_WARN, LOG_TAG, __VA_ARGS__))
#endif

#ifndef ALOGE
#define ALOGE(...) ((void)ALOG(LOG_ERROR, LOG_TAG, __VA_ARGS__))
#endif

#ifndef log_info
#define log_info(p)  ALOGW("[%s][%s:%d], %s is null/false", __func__, __FILE__, __LINE__, p)
#endif

#ifndef return_assert
#define return_assert(p)    if (!(p)) {log_info(#p); return;}
#endif

#ifndef returnb_assert
#define returnb_assert(p)   if (!(p)) {log_info(#p); return false;}
#endif

#ifndef returnv_assert
#define returnv_assert(p, v) if (!(p)) {log_info(#p); return (v);}
#endif

#endif
