Docker

# 概念

镜像：类

容器：实例

# 安装环境

## centos

找个博客抄命令就行，这个不啰嗦

# 启动

```
systemctl start docker
```

# 常用命令

#### 获取镜像

``` 
docker pull mysql
```

#### 启动容器

```
1. docker run -itd -p 3306:3306 --name mysql_test mysql /bin/bash
/bin/bash 后接的命令
-i 交互式操作
-t 开启一个终端
-d 设置为守护式启动，即页面不显示。此时若没有操作，容器会自动销毁
-p 后接宿主机端口:容器内端口
-P 随机分配宿主机端口
--name 设置别名，后接一个字符串

2. docker start 容器ID
用于启动一个已经停止的容器

3. docker restart 容器ID
重启动一个容器


```

#### 查看当前运行容器

```
docker ps
-a 查看全部容器，包括销毁的
-l 查看上一个容器
```

#### 进入容器

```
1. docker attach 容器ID
进入容器。若退出，容器会停止
2. docker exec -it 容器ID
进入容器。若退出，容器不会停止
```

#### 删除容器

```
docker rm -f 容器ID
-f 表示强制删除
```

#### 列出当前镜像

```
docker images
```

#### 查找云端可获取镜像

```
docker search mysql
```

#### 删除镜像

```
docker rmi -f mysql
```

#### 创建镜像

```
1. 更新镜像后提交
docker commit -m="更新信息" -a="作者信息" e218edb10161容器ID runoob/ubuntu:v2镜像名字：版本号
2. Dockerfile编译提交
docker build -t mysql_test .
-t 指定创建的目标镜像名
. Dockerfile文件所在目录。可以指定绝对路径
```

# Dockerfile

FROM 镜像源

RUN 在build是运行的命令