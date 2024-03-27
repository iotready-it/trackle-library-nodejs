CC = gcc
CCX = g++
TRACKLE_LIB=$(TRACKLE_LIB_PATH)
DIST_LIB_PATH=$(TRACKLE_DIST_PATH)

# OS detection for DLL extension
ifeq ($(shell uname -s),Darwin)
    DLL_EXTENSION = dylib
else
    ifeq ($(shell uname -s),Linux)
        DLL_EXTENSION = so
    else
        $(error Unsupported OS)
    endif
endif

# TEST_AUX_FUN_SRCS = test_auxiliary_functions.c

# Trackle library and its components compilation variables
TRACKLE_LIB_SRCS = $(TRACKLE_LIB)/src/*.cpp
TRACKLE_LIB_INCLUDES = -I"$(TRACKLE_LIB)/include"

UECC_SRCS = $(TRACKLE_LIB)/lib/micro-ecc/uECC.c
UECC_INCLUDES = -I"$(TRACKLE_LIB)/lib/micro-ecc"

TINY_SRCS = $(TRACKLE_LIB)/lib/tinydtls/ccm.c \
			$(TRACKLE_LIB)/lib/tinydtls/crypto.c \
			$(TRACKLE_LIB)/lib/tinydtls/dtls.c \
			$(TRACKLE_LIB)/lib/tinydtls/dtls_debug.c \
			$(TRACKLE_LIB)/lib/tinydtls/dtls_time.c \
			$(TRACKLE_LIB)/lib/tinydtls/dtls_prng.c \
			$(TRACKLE_LIB)/lib/tinydtls/hmac.c \
			$(TRACKLE_LIB)/lib/tinydtls/netq.c \
			$(TRACKLE_LIB)/lib/tinydtls/peer.c \
			$(TRACKLE_LIB)/lib/tinydtls/session.c \
			$(TRACKLE_LIB)/lib/tinydtls/aes/*.c \
			$(TRACKLE_LIB)/lib/tinydtls/sha2/sha2.c
TINY_INCLUDES = -I"$(TRACKLE_LIB)/lib/tinydtls" \
			    -I"$(TRACKLE_LIB)/lib/tinydtls/aes" \
			    -I"$(TRACKLE_LIB)/lib/tinydtls/platform-specific" \
			    -I"$(TRACKLE_LIB)/lib/tinydtls/sha2"


# All object files in base directory
OBJS = *.o

# Flags to be passed to compiler before compiling DLL pieces
DLL_FLAGS = -DDISABLE_EXAMPLES_LOGGING

# default: dll_trackle dll_callbacks dll_cloudfunctions
default: dll_trackle


trackle_library_fpic:
	$(CCX) -w -std=c++11 -fpermissive -fms-extensions -c -fPIC $(TRACKLE_LIB_SRCS) $(TRACKLE_LIB_INCLUDES) $(UECC_INCLUDES) $(TINY_INCLUDES) $(DLL_FLAGS)

uecc_fpic:
	$(CC) -w -c -fPIC $(UECC_SRCS) $(UECC_INCLUDES) $(DLL_FLAGS)

tinydtls_fpic:
	$(CC) -w -c -fPIC $(TINY_SRCS) $(TINY_INCLUDES) $(UECC_INCLUDES) $(DLL_FLAGS) -DWITH_SHA256

dll_trackle: trackle_library_fpic uecc_fpic tinydtls_fpic
	$(CC) -w -shared $(OBJS) -o $(DIST_LIB_PATH)/trackle_library.$(DLL_EXTENSION) -lstdc++ -lm
	rm -f *.o