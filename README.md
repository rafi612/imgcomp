# imgcomp
[Build]: https://img.shields.io/github/actions/workflow/status/rafi612/imgcomp/build.yml?branch=main
[License]: https://img.shields.io/github/license/rafi612/imgcomp
[Release]: https://img.shields.io/github/v/release/rafi612/imgcomp
[Repo size]: https://img.shields.io/github/repo-size/rafi612/imgcomp
[Total lines]: https://img.shields.io/tokei/lines/github/rafi612/imgcomp

[![Build]](https://github.com/rafi612/imgcomp/actions/workflows/build.yml)
[![License]](https://github.com/rafi612/imgcomp/blob/main/LICENSE)
[![Release]](https://github.com/rafi612/imgcomp/releases/)
[![Repo size]](https://github.com/rafi612/imgcomp)
[![Total lines]](https://github.com/rafi612/imgcomp)

**Imgcomp** is cross platform image compressing tool which allows to lossy-compress amount of images in directories and subdirectories.

# How to use:
`imgcomp -<flags> <folder or image path> <divider> <format>`

**Flags:** 
- `-k` - keep original files
- `-n` - keep original names on compressed files
- `-help` - shows how to use imgcomp

Flags use: `-xyz`

**Divider:** Resolution was divided by divider

**Format:** png/jpg/bmp etc.. (jpg recomended)

If you dont use flags use: `imgcomp <folder or image path> <divider> <format>`

# Dependencies

Imgcomp using following libraries:
- [stb](https://github.com/nothings/stb) - image reading, writing and compressing

# Building

First clone repository: `git clone https://github.com/rafi612/imgcomp`

### Requirements
- CMake

Update submodules:

```
git submodule init
git submodule update
```
## Linux/MacOS X

Create build directory using: `mkdir build && cd build`

Run CMake using: `cmake ..`

Build using: `make -j4` (in `-j4` enter amount of cores/threads that your CPU have)

## Windows

Create build directory named `build` and enter them.

Run CMake using: `cmake ..`

Open generated Visual Studio Project and build executable.

Alternatively you can run command: `cmake --build ..`

# Packaging

You can generate packages for linux distributions:

**Debian/Ubuntu based (deb):**
run command: `cpack -G DEB`

**RedHat based (rpm):**
*not implemented yet.*

**Arch based (PKGBUILD):**
*PKGBUILD* file can be founded in *package/aur* directory.


In other operating system you can use normal executables only. To use it from terminal add it to directory which is in **PATH** environment variable.
