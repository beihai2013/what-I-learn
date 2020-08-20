# geth

## 环境

ubuntu 20.01

## 配置命令

```
sudo apt-get install software-properties-common
sudo add-apt-repository -y ppa:ethereum/ethereum
sudo apt-get update
sudo apt-get install ethereum
```

### 雷点

ubuntu推荐用类似的命令安装

```
apt-get snap install geth
```

这个安装方法无法初始化创世区块，会爆出类似错误

```
Fatal: Failed to read genesis block
```

## 初始化区块

创建创世区块json配置文件

```
// genesis.json

{
  "config": {
    "chainId": 666,
    "homesteadBlock": 0,
    "eip150Block": 0,
    "eip150Hash": "0x0000000000000000000000000000000000000000000000000000000000000000",
    "eip155Block": 0,
    "eip158Block": 0,
    "byzantiumBlock": 0,
    "constantinopleBlock": 0,
    "petersburgBlock": 0,
    "istanbulBlock": 0,
    "ethash": {}
  },
  "nonce": "0x0",
  "timestamp": "0x5ddf8f3e",
  "extraData": "0x0000000000000000000000000000000000000000000000000000000000000000",
  "gasLimit": "0x47b760",
  "difficulty": "0x00002",
  "mixHash": "0x0000000000000000000000000000000000000000000000000000000000000000",
  "coinbase": "0x0000000000000000000000000000000000000000",
  "alloc": { },
  "number": "0x0",
  "gasUsed": "0x0",
  "parentHash": "0x0000000000000000000000000000000000000000000000000000000000000000"
}
```

创建文件夹 /data

将两者的权限修改为可写可读可执行

``` 
chmod 777 genesis.json
chmod 777 data
```

执行命令

```
sudo geth --datadir data init genesis.json
```

