# Introduction 
A demo on implementing simplified docker

# Getting Started
Please go through the following steps to prepare for the environment. We are assuming you are using Windows host.

## 1. Work in Windows Subsystem for Linux with Visual Studio Code
Follow [this doc](https://code.visualstudio.com/docs/remote/wsl-tutorial) to install VS Code, WSL extension, Linux distro.
Besides, you should install c/c++ extension as well.

This takes around 10 minutes. 

## 2. Install gcc, make, alpine
In VS code terminal connected to the Ubuntu, 
```
apt-get update
apt install g++
apt install make
```
```
mkdir alpine
cd alpine
curl -o alpine.tar.gz http://dl-cdn.alpinelinux.org/alpine/v3.10/releases/x86_64/alpine-minirootfs-3.10.0-x86_64.tar.gz
tar xvf alpine.tar.gz
rm alpine.tar.gz
cd ..
```

## 3. Validation
On host machine, open a powershell,
```
wsl -l -v
```
The Ubuntu should be running as displayed:
```
  NAME                   STATE           VERSION
  Ubuntu-20.04           Running         2
```
If the version is 1, you need to switch to WSL 2,
```
wsl --set-version Ubuntu-20.04 2
```

# Run the container

## 1. Compile and run
```
make demo
sudo ./demo
```

## 2. Validation
Try some commands, such as `ls`, `ps`,...