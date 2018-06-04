
#!/usr/bin/env bash
echo "进入编译ffmpeg脚本"
NDK=/Users/chengfangming/Library/android/sdk/android-ndk-r14b
PLATFORM=$NDK/plarforms/android-21/arch-arm
TOOLCHAIN=$NDK/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64

#这个目录需要自己建，后会改为shell脚步建
TMPDIR=./jni/temp
function buildFF {
  echo "开始编译ffmpeg"
  ./configure \
  --prefix=$PREFIX \
  --target-os=android \
  --cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi- \
  --arch=arm \
  --cpu=$CPU \
  --sysroot=$PLATFORM \
   --extra-libs=-lgcc \
  --extra-cflags=$CFLAGS \
  --cc=$TOOLCHAIN/bin/arm-linux-androideabi-gcc \
  --nm=$TOOLCHAIN/bin/arm-linux-androideabi-nm \
  --enable-shared \
  --enable-runtime-cpudetect \
  --enable-gpl \
  --enable-small \
  --enable-cross-compile \

  --disable-debug \
  --disable-static \
  --disable-doc \
  --disable-ffmpeg \
  --disable-ffplay \
  --disable-ffprobe \
  --disable-ffserver \
  --disable-postproc \
  --disable-avdevice \
  --disable-symver \
  --disable-stripping\
  $ADD \
  make -j8
  make install
  echo "编译结束"
}

echo "编译支持neon和硬解码"
CPU=armv7-a
PREFIX=./android/$CPU-a-neon-hard
CFLAGS="-I$PLATFORM/usr/include -fPIC -DANDROID -mfpu=neon -mfloat-abi=softfp "
ADD="--enable-asm \
  --enable-neon \
  --enable-jni \
  --enable-mediacodec \
  --enable-decoder=h264_mediacodec \
  --enable-hwaccel=h264_mediacodec"

buildFF
#echo "编译不支持neon和硬解码"
#CPU=armv7-a
#PREFIX=./android/$CPU
#CFLAGS="-I$PLATFORM/usr/include -fPIC -DANDROID -mfloat-abi=softfp "
#ADD=""
#buildFF
