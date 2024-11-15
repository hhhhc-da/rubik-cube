# rubik_cube

#### 介绍
算法设计：二阶魔方程序

#### Cmake + MinGW-Make使用说明

Cmake 编译命令示例

```
cd build
cmake -G "MinGW Makefiles" ..
make
./bin/main.exe
```

Git 编译命令示例

```
git init
git add remote nanoka https://gitee.com/nanokadesu/rubik_cube.git
git pull --rebase nanoka master
# 这边修改好文件之后
git add *
git commit -am"xxx" # xxx 是你要添加的注释
git branch -M yyy   # yyy 是你要新添加的分支
git push -u nanoka yyy
```
