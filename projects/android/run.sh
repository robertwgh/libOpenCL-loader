adb shell "rm -rf /data/local/tmp/cl-test"
adb shell "mkdir -p /data/local/tmp/cl-test && chmod 777 /data/local/tmp/cl-test"
adb push ./libs/armeabi-v7a/clinfo /data/local/tmp/cl-test/
adb shell "cd /data/local/tmp/cl-test && chmod 777 ./clinfo && ./clinfo -v"
