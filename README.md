# Qt3d experiments

## To build on ubuntu 22.04:

Install Qt6 3d dev dependencies:

```
sudo apt-get install qt6-base-dev qt6-3d-dev
```

Build with cmake

```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -GNinja
ninja
```

Run

```
./qt3d
```