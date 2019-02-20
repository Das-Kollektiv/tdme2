![LOGO](https://raw.githubusercontent.com/andreasdr/tdme2/master/resources/logo/tdme_logo_full.png)

# 1. How to build TDME2?

## 1.1. FreeBSD(tested on FreeBSD 12.0)
### 1.1.1 Install packages

```bash
su -
pkg install git
pkg install gmake
pkg install glew
pkg install openal-soft
pkg install freeglut
exit
```

### 1.1.2. Clone repository
```bash
git clone https://github.com/andreasdr/tdme2
cd tdme2
```

### 1.1.3. Build
```bash
gmake clean && gmake -j HARDWARE_THREADS mains
```

## 1.2. Ubuntu(tested on XUBUNTU 18.04)
### 1.2.1 Install packages

```bash
sudo apt install git
sudo apt install make
sudo apt install g++
sudo apt-get install libglew-dev
sudo apt-get install libopenal-dev
sudo apt-get install freeglut3-dev
```

### 1.2.2. Clone repository
```bash
git clone https://github.com/andreasdr/tdme2
cd tdme2
```

### 1.2.3. Build
```bash
make clean && make -j HARDWARE_THREADS mains
```

## 1.3. Mac OS X
### 1.3.1 Install packages
You have to install XCode or XCode command line tools.


### 1.3.2. Clone repository
```bash
git clone https://github.com/andreasdr/tdme2
cd tdme2
```

### 1.3.3. Build
```bash
make clean && make -j HARDWARE_THREADS mains
```

# 2. Running a TDME2 binary

You find binaries in
- ./bin/tdme/tests/
- ./bin/tdme/tools/

You have to execute the binaries from tdme2 root folder like:

```bash
$ pwd
/usr/home/andreas/Development/drewke.net/tdme2
$ ./bin/tdme/tests/AngleTest
```

# Other information
- Links
	- TDME2 Engine, see [README.md](./README.md)
    - TDME2 Model Editor, see [README-ModelEditor.md](./README-ModelEditor.md)
    - TDME2 Particle System Editor, see [README-ParticleSystemEditor.md](./README-ParticleSystemEditor.md)
    - TDME2 Level Editor, see [README-LevelEditor.md](./README-LevelEditor.md)
    - TDME2 How to build, see [README-BuildingHowTo.md](./README-BuildingHowTo.md)

- Build instructions will follow for FreeBSD, NetBSD, Windows-MINGW, Windows-MSC, ...  