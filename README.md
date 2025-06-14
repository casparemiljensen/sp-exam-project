# sp-exam-project

## Authors
Caspar Emil Jensen, Lucas Lybek Højlund Pedersen, Pætur Magnussen, Thomas Dam Nykjær & Thomas Ilum Andersen

## Requirements
Install **graphviz** 
- https://graphviz.org/download/  
- Setup path in environment variables to make the "dot" file - command available\

Install **qt6-charts** 
- https://www.qt.io/download/

- CMAKE 3.30 or later \

## Additional Requirements
This library requires: \
gcc-14 compiler \
cpp 23+ standard \
Which is included in bleeding edge package managers and will be added to others later \
CLion does not yet come packaged with gcc-14+/cpp 23+, so for Windows systems:
Install **MSYS2** - ensure CLion configuration uses ucrt64 

### FAQ
Generator errors are related to missing or wrong gcc version. See [Additional Requirements](#additional-requirements)

## Network graph Generation (Graphviz)
To generate the network graph, run the following command in a terminal:
```
cd /graphs
dot -Tpng "name-of-file".dot -o network.png
```


