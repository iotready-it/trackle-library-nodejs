{
    "variables": {
        "trackle_dist_dir" : "<!@(pwd)/dist/app/lib/",
        "trackle_src_dir" : "<!@(pwd)/lib/src/trackle-library-cpp-4"
    },
    "targets": [
        {
            "target_name": "trackle_wrapper",
            "cflags!": [ "-fno-exceptions" ],
            "cflags_cc!": [ "-fno-exceptions" ],
            "cflags": [ "-std=c++11" ],
            "sources": [       
                "./lib/src/wrapper/callbacks/default_callbacks.cpp",
                "./lib/src/wrapper/callbacks/http_cb_handler.cpp",
                "./lib/src/wrapper/main.cpp",
                "./lib/src/wrapper/proxy/trackle_proxy.cpp",
                "./lib/src/wrapper/utils/utils.cpp"],
            "libraries": [
                "<(trackle_dist_dir)/trackle_library.so"
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                "<(trackle_src_dir)/include"
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS']
        }
    ]
}