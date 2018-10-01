# mollex: mollusc extractor

mollex extracts molluscoid shapes from images.
Mollusca is a phylum containing cephalopods (octopods etc.)
and gastropods (such as snails and slugs).
More precisely, the
_Museum für Naturkunde Berlin_ kindly provided us with a large
collection of molluscs as part of the [Coding da Vinci](https://codingdavinci.de)
hackathon.

mollex works by removing the background, performing some adaptive
prefiltering and finally finding contours that match typical
molluscoid shapes.

We tested mollex only on snail-like shapes.

## Daten

  - [Coding da Vinci](https://codingdavinci.de/daten/#museum-f%C3%BCr-naturkunde-berlin)
  - [Metadata](http://gbif.naturkundemuseum-berlin.de/CDV2018/Mollusken/Metadaten/)
  - [Image Files](http://gbif.naturkundemuseum-berlin.de/CDV2018/Mollusken/)
  - [Gallery View](http://gbif.naturkundemuseum-berlin.de/CDV2018/mollusken-gallery.html)
  
  
![](https://img1.picload.org/image/dogggpcw/image18.png)  

## Install instruction

### Linux

```sh
mkdir build
meson --buildtype=debug build
ninja -C build
./build/mollex

Usage: ./build/mollex [options] source destination
Extract snails from images.

Options:
  -h, --help     Displays this help.
  -v, --version  Displays version information.
  --verbose      Show debug information.
  --json         Write metadata as JSON to stdout.

Arguments:
  source         Source image to process.
  destination    Destination directory.
```

### Windows

- Download and install [meson](https://github.com/mesonbuild/meson/releases) for Windows.
- Download and install [Qt5](https://www.qt.io/download) for Windows.
- Download and install [OpenCV 3.4.2](https://opencv.org/releases.html) for Windows.
- Download ans install [Visual Studio](https://visualstudio.microsoft.com/de/downloads/).

Run inside a terminal:

```sh
meson build --backend vs \
  -Dopencv_includes=C:\opt\opencv-3.4.3\build\include\
  -Dopencv_lib=C:\opt\opencv-3.4.3\build\x64\vc15\lib\opencv_world343d.lib
```

This will generate project files for Visual Studio inside `build`. Open `mollex.sln` in Visual Studio and build the project.

Alternatively, in a terminal try something like this:
```sh
"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsx86_amd64.bat"
cd build
MSBuild mollex
```

## Usage

``` 
Usage: mollex [options] source destination
Extract snails from images.

Options:
  -h, --help     Displays this help.
  -v, --version  Displays version information.
  --verbose      Show debug information.
  --json         Write metadata as JSON to stdout.

Arguments:
  source         Source image to process.
  destination    Destination directory.
```

```
λ .\mollex.exe --json --verbose C:\Users\Jens\Desktop\ZMB_Mol_4085_1.jpg out
threshold: 0.21625739303 b:980943 1.32685                                                        
convex: 776734 q:1.05063                                                                         
676745 b:1.23891e+06 1.83069                                                                     
Found 1 potential molluscs                                                                       
{                                                                                                
    "basename": "ZMB_Mol_4085_1",                                                                
    "imagePath": "C:\\Users\\Jens\\Desktop\\ZMB_Mol_4085_1.jpg",                                 
    "molluscoids": [                                                                             
        {                                                                                        
            "angle": -1.5298357108069875,                                                        
            "bbox": {                                                                            
                "height": 1319,                                                                  
                "width": 816,                                                                    
                "x": 1373,                                                                       
                "y": 515                                                                         
            },                                                                                   
            "color": "#cda56f",                                                                  
            "imageName": "ZMB_Mol_4085_1_0.png",                                                 
            "ratio": 0.592178225517273                                                           
        }                                                                                        
    ]                                                                                            
}
```