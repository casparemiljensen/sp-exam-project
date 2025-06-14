# sp-exam-project

## Authors
Caspar Emil Jensen, Lucas Lybek Højlund Pedersen, Pætur Magnussen, Thomas Dam Nykjær & Thomas Ilum Andersen

## Requirements
Install **graphviz** 
- https://graphviz.org/download/  
- Setup path in environment variables to make the "dot" file - command available\

Install **qt6-charts** (Can be installed through msys2 as shown below) 
- https://www.qt.io/download/

- CMAKE 3.30 or later \

## Additional Requirements
This library requires: \
gcc-14 compiler \
cpp 23+ standard \
Which is included in bleeding edge package managers and will be added to others later \
CLion does not yet come packaged with gcc-14+/cpp 23+, so for Windows systems:
Install **MSYS2** - ensure CLion configuration uses ucrt64.\

**Example installation:**\
Install MSYS2 by going to their website. When downloaded, run the following commands in the MSYS2 UCRT64 terminal to install the requirements: \
``pacman -S mingw-w64-ucrt-x86_64-gcc``

**Install qtCharts:** \
Update packages:\
``pacman -Syu`` 

Open MSYS2 UCRT64 terminal again and run the following command:
```
pacman -S mingw-w64-ucrt-x86_64-qt6-base \
    mingw-w64-ucrt-x86:64-qt6-charts
```

Install cmake in UCRT64: \
``pacman -S mingw-w64-ucrt-x86_64-cmake``

Set your toolchain to the following in CLion (Assuming your msys is installed directly on the C drive: \
Toolset: ``C:\msys64\ucrt64`` \
CMake: ``C:\msys64\ucrt64\bin\cmake.exe``

The rest of the options should be auto-detected

In your Cmake debug and release profiles:\
CMake options:\
``-DCMAKE_PREFIX_PATH=C:/msys64/ucrt64 -DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic``

Environment:\
``MSYSTEM=UCRT64;CHERE_INVOKING=1``


### FAQ
Generator errors are related to missing or wrong gcc version. See [Additional Requirements](#additional-requirements)

## Network graph Generation (Graphviz)
To generate the network graph, run the following command in a terminal:
```
cd /graphs
dot -Tpng "name-of-file".dot -o network.png
```


