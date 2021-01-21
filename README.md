# Introduction 
A demo on implementing simplified docker

# Getting Started
Please go through the following steps to prepare for the environment. We are assuming you are using Windows host.

## 1. Work in Windows Subsystem for Linux with Visual Studio Code
Follow [this doc](https://code.visualstudio.com/docs/remote/wsl-tutorial) to install VS Code, WSL extension, Linux distro.
Besides, you should install c/c++ extension as well.

This takes around 10 minutes. 

## 2. Install gcc
In VS code terminal connected to the Ubuntu, 
```
apt-get update
apt install g++
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

## 1. Create a cgroup
```
sh mygroup.sh
```

## 2. Compile and run
```
gcc -o demo demo.c
sudo ./demo
```

## 3. Validation
Try some commands, such as `ls`, `ps`,...