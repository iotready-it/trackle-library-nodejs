{
    "variables": {
        "trackle_src_dir": "lib/trackle-library-cpp-v4"
    },
    "targets": [
        {
            "target_name": "micro-ecc",
            "type": "static_library",
            "xcode_settings": {
                'OTHER_CFLAGS':  [ 
                    "-DDISABLE_EXAMPLES_LOGGING"
                ],
            },
            "sources": [
                "<(trackle_src_dir)/lib/micro-ecc/uECC.c"
            ],
            "include_dirs": [
                "<(trackle_src_dir)/lib/micro-ecc"
            ],
            "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"]
        },
        {
            "target_name": "tinydtls",
            "type": "static_library",
            "xcode_settings": {
                'OTHER_CFLAGS':  [ 
                    "-DWITH_SHA256", "-DDISABLE_EXAMPLES_LOGGING", "-Wno-incompatible-function-pointer-types"
                ],
            },
            "sources": [
                "<(trackle_src_dir)/lib/tinydtls/ccm.c",
                "<(trackle_src_dir)/lib/tinydtls/crypto.c",
                "<(trackle_src_dir)/lib/tinydtls/dtls.c",
                "<(trackle_src_dir)/lib/tinydtls/dtls_debug.c",
                "<(trackle_src_dir)/lib/tinydtls/dtls_prng.c",
                "<(trackle_src_dir)/lib/tinydtls/dtls_time.c",
                "<(trackle_src_dir)/lib/tinydtls/hmac.c",
                "<(trackle_src_dir)/lib/tinydtls/netq.c",
                "<(trackle_src_dir)/lib/tinydtls/peer.c",
                "<(trackle_src_dir)/lib/tinydtls/session.c",
                "<(trackle_src_dir)/lib/tinydtls/aes/rijndael.c",
                "<(trackle_src_dir)/lib/tinydtls/aes/rijndael_wrap.c",
                "<(trackle_src_dir)/lib/tinydtls/sha2/sha2.c"
            ],
            "dependencies": [
                "micro-ecc"
            ],
            "include_dirs": [
                "<(trackle_src_dir)/lib/micro-ecc",
                "<(trackle_src_dir)/lib/tinydtls",
                "<(trackle_src_dir)/lib/tinydtls/aes",
                "<(trackle_src_dir)/lib/tinydtls/sha2"
            ]
        },
        {
            "target_name": "trackle_library",
            "type": "static_library",
            "xcode_settings": {
                'OTHER_CPLUSPLUSFLAGS': [ 
                    "-std=c++11", "-DDISABLE_EXAMPLES_LOGGING"
                ],
            },
            "sources": [
                "<(trackle_src_dir)/src/chunked_transfer.cpp",
                "<(trackle_src_dir)/src/diagnostic.cpp",
                "<(trackle_src_dir)/src/events.cpp",
                "<(trackle_src_dir)/src/protocol.cpp",
                "<(trackle_src_dir)/src/trackle.cpp",
                "<(trackle_src_dir)/src/coap.cpp",
                "<(trackle_src_dir)/src/dtls_message_channel.cpp",
                "<(trackle_src_dir)/src/logging.cpp",
                "<(trackle_src_dir)/src/protocol_defs.cpp",
                "<(trackle_src_dir)/src/trackle_interface.cpp",
                "<(trackle_src_dir)/src/coap_channel.cpp",
                "<(trackle_src_dir)/src/dtls_protocol.cpp",
                "<(trackle_src_dir)/src/messages.cpp",
                "<(trackle_src_dir)/src/publisher.cpp",
                "<(trackle_src_dir)/src/trackle_protocol_functions.cpp"
            ],
            "include_dirs": [
                "<(trackle_src_dir)/include",
                "<(trackle_src_dir)/lib/tinydtls",
                "<(trackle_src_dir)/lib/tinydtls/aes",
                "<(trackle_src_dir)/lib/tinydtls/sha2"
            ],
            "dependencies": [
                "tinydtls"
            ],
            "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"]
        },
        {
            "target_name": "trackle_wrapper",
            "xcode_settings": {
                'OTHER_CPLUSPLUSFLAGS': [ 
                    "-std=c++11", "-DDISABLE_EXAMPLES_LOGGING"
                ],
            },
            "sources": [
                "lib/wrapper/callbacks/default_callbacks.cpp",
                "lib/wrapper/callbacks/http_cb_handler.cpp",
                "lib/wrapper/main.cpp",
                "lib/wrapper/proxy/trackle_proxy.cpp",
                "lib/wrapper/utils/utils.cpp"
            ],
            "dependencies": [
                "trackle_library"
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                "<(trackle_src_dir)/include"
            ],
            "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"]
        }
    ]
}
