APP_ABI      := arm64-v8a armeabi-v7a
APP_PLATFORM := android-21
APP_STL      := c++_static
APP_OPTIM    := release
APP_PIE      := true

ifeq ($(APP_OPTIM),release)
  APP_CFLAGS     := -O2 -DNDEBUG #-Wall #-Wextra
  APP_STRIP_MODE := --strip-all
else
  APP_CFLAGS     := -O0 -g
  APP_STRIP_MODE := none
endif

APP_BUILD_SCRIPT := Android.mk


# I'm @RrQ_Owner owner's of @RrQ_MoDs 