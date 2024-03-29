{
    "variables": {
        "trackle_dist_dir" : "<!@(pwd)/dist/lib/",
        "trackle_src_dir" : "<!@(pwd)/lib/trackle-library-cpp-v4"
    },
    "targets": [
        {
            "target_name": "trackle_wrapper",
            "cflags!": [ "-fno-exceptions", "-Wno-non-pod-varargs" ],
            "cflags_cc!": [ "-fno-exceptions", "-Wno-non-pod-varargs" ],
            "cflags": [ "-std=c++11" , "-Wno-non-pod-varargs" ],
            "sources": [       
                "./lib/wrapper/callbacks/default_callbacks.cpp",
                "./lib/wrapper/callbacks/http_cb_handler.cpp",
                "./lib/wrapper/main.cpp",
                "./lib/wrapper/proxy/trackle_proxy.cpp",
                "./lib/wrapper/utils/utils.cpp"],
            "conditions": [
                ['OS=="mac"', {
                    "libraries": [
                        "<(trackle_dist_dir)/trackle_library.dylib"
                    ],
                }],
                ['OS=="linux"', {
                    "libraries": [
                        "<(trackle_dist_dir)/trackle_library.so"
                    ],
                }]
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                "<(trackle_src_dir)/include"
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS']
        }
    ]
}