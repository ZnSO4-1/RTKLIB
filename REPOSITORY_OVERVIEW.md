# RTKLIB 仓库内容介绍

下面是当前工作区 `c:\0` 里的 RTKLIB 仓库内容梳理。该仓库基于 `RTKLIB 2.4.2 p13`，基础提交为 `71db0ff rtklib 2.4.2 p13`。

## 整体定位

RTKLIB 是一个开源 GNSS 标准/精密定位程序包，由核心库和多个应用程序组成。它支持 GPS、GLONASS、Galileo、QZSS、BeiDou、SBAS；定位模式包括 Single、DGPS/DGNSS、Kinematic、Static、Moving-Baseline、Fixed、PPP-Kinematic、PPP-Static、PPP-Fixed 等。

本工作区已经开始将原来的 C 代码迁移为 C++ 源码。代码整体仍保留上游 RTKLIB 的过程式结构；后续应先保持兼容构建稳定，再逐步引入新的 C++ 封装和优化。

## 关键目录

- `src`：RTKLIB 核心库源码，算法、文件格式、流处理、RTK/PPP 解算基本都在这里。
- `src/rtklib.h`：核心公共头文件，定义版本号、主要结构体和库 API，例如 `prcopt_t`、`solopt_t`、`obs_t`、`nav_t`、`rtk_t`，以及 `postpos()`、`rtkpos()`、`pntpos()`、`pppos()` 等接口。
- `src/rcv`：接收机原始数据解码模块，例如 u-blox、NovAtel、JAVAD、SkyTraq、BINEX、Septentrio 等。
- `app`：各应用程序源码和构建工程。
- `doc`：文档目录，包含上游手册和发布说明。
- `data`：示例数据。
- `test`：测试程序和测试数据，包含 `test/utest` 与 `test/data`。
- `util`：辅助工具，例如 CRC 生成、IONO 生成、RINEX 转 RTCM、模拟观测值、星历测试等。
- `lib`：库生成/外部支持相关目录，目前主要有 `iers`、`omf`。
- `bin`：该源码仓库里的 `bin` 主要是说明文件，提示可执行二进制已移到 `RTKLIB_bin/bin`。

## 核心源码分工

`src/rtkcmn.cpp` 是基础公共函数集合，包含时间、坐标、矩阵、卫星系统、路径、调试等通用工具，是很多模块的底座。

`src/pntpos.cpp` 做单点定位；`src/rtkpos.cpp` 做 RTK 相对定位主逻辑；`src/ppp.cpp` 和 `src/ppp_ar.cpp` 处理 PPP 与 PPP 模糊度固定；`src/lambda.cpp` 是整周模糊度搜索/固定相关算法。

`src/postpos.cpp` 是后处理入口逻辑，命令行 `rnx2rtkp` 和 GUI `rtkpost` 都会围绕它工作。若要改“RINEX 输入后输出解算结果”的流程，通常会看这里和应用入口。

`src/rinex.cpp`、`src/convrnx.cpp` 负责 RINEX 读写和转换；`src/rtcm.cpp`、`src/rtcm2.cpp`、`src/rtcm3.cpp`、`src/rtcm3e.cpp` 负责 RTCM 解码/编码。

`src/stream.cpp`、`src/streamsvr.cpp`、`src/rtksvr.cpp` 是实时数据流和实时 RTK server 相关逻辑，和串口、TCP/IP、NTRIP、文件回放等输入输出更相关。

`src/solution.cpp` 负责解算结果格式化、读取、输出，包括常见 `.pos`、NMEA 等结果相关内容。如果要改输出列、输出格式、状态信息，常从这里入手。

## 应用程序

`app/rnx2rtkp`：命令行后处理程序 RNX2RTKP。入口文件是 `app/rnx2rtkp/rnx2rtkp.cpp`。

`app/rtkrcv`：命令行实时定位程序 RTKRCV。入口文件是 `app/rtkrcv/rtkrcv.cpp`，并带有多个示例配置，如 `single.conf`、`rtk.conf`、`ppp.conf`。

`app/convbin`：命令行原始数据转 RINEX 工具 CONVBIN。

`app/str2str`：命令行数据流转发/转换工具 STR2STR，常用于串口、TCP、NTRIP、文件流之间转发。

`app/pos2kml`：把定位结果转换为 KML 的命令行工具。

GUI 应用已移到 `legacy_gui_vcl/app`，包括 `rtknavi`、`rtkpost`、`rtkplot`、`rtkconv`、`strsvr`、`rtkget`、`rtklaunch` 等。它们属于 Windows/VCL legacy 组件，不纳入默认算法主线构建。

## 后续修改入口建议

如果想改后处理结果：优先看 `app/rnx2rtkp/rnx2rtkp.cpp`、`src/postpos.cpp`、`src/solution.cpp`。

如果想改实时定位：优先看 `app/rtkrcv/rtkrcv.cpp`、`src/rtksvr.cpp`、`src/rtkpos.cpp`、`src/stream.cpp`。

如果想改接收机原始数据支持：看 `src/rcv` 以及 `src/rcvraw.cpp`。

如果想改 RINEX/RTCM 格式处理：看 `src/rinex.cpp`、`src/convrnx.cpp`、`src/rtcm3.cpp` 等。
