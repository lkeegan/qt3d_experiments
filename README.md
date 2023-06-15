# Qt3d + sme experiments

## Prerequisites (ubuntu 22.04):

Spatial Model Editor core (with Qt6 compiled with qt3d module - for now re-compiling qt6 locally but will upstream to sme_deps at some point...):

```
git clone --recursive https://github.com/spatial-model-editor/spatial-model-editor.git
cd spatial-model-editor
# install static libs to /opt/smelibs
sudo ./ext/getdeps.sh
# build & install sme::core to same location
mkdir build
cd build
cmake -GNinja -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DCMAKE_CXX_FLAGS="-fpic -fvisibility=hidden" -DCMAKE_PREFIX_PATH="/opt/smelibs;/opt/smelibs/lib/cmake" -DSME_EXTRA_EXE_LIBS="-ltirpc" -DCMAKE_INSTALL_PREFIX=/opt/smelibs
ninja core
ninja install
```

## Build

```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="/opt/smelibs;/opt/smelibs/lib/cmake" -DBUILD_SHARED_LIBS=OFF -GNinja
ninja
```

## Run

```
./qt3d
```