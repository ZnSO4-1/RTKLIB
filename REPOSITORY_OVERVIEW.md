# Repository Overview

## English

This repository contains an algorithm-focused C++ migration of RTKLIB 2.4.2
p13. The codebase is still structurally close to upstream RTKLIB: the core
library remains procedural, while the build system now treats the migrated
sources as C++.

### Core Areas

- `src/rtkcmn.cpp`: common time, coordinate, matrix, satellite-system, path,
  and tracing utilities.
- `src/pntpos.cpp`: single-point positioning.
- `src/rtkpos.cpp`: RTK relative positioning.
- `src/ppp.cpp` and `src/ppp_ar.cpp`: PPP and PPP ambiguity resolution.
- `src/lambda.cpp`: integer ambiguity search and fixing.
- `src/postpos.cpp`: post-processing workflow used by `rnx2rtkp`.
- `src/solution.cpp`: solution formatting, reading, and output.
- `src/rinex.cpp` and `src/convrnx.cpp`: RINEX reading, writing, and
  conversion.
- `src/rtcm*.cpp`: RTCM decoding and encoding.
- `src/stream.cpp`, `src/streamsvr.cpp`, and `src/rtksvr.cpp`: real-time data
  streams and RTK server logic.
- `src/rcv`: raw receiver protocol decoders.

### Applications

- `app/rnx2rtkp`: command-line post-processing.
- `app/rtkrcv`: command-line real-time positioning.
- `app/convbin`: raw receiver data to RINEX conversion.
- `app/str2str`: stream relay and conversion.
- `app/pos2kml`: position result to KML conversion.

### Tests and Tools

- `test/utest`: upstream unit tests registered with CTest.
- `test/regression`: committed numerical regression baselines.
- `util`: auxiliary conversion, simulation, ionosphere, STEC, CRC, and
  ephemeris tools.

### Legacy GUI

Original Windows VCL GUI applications are preserved under `legacy_gui_vcl/app`.
They are not part of the default CMake build and require Embarcadero/Borland
C++Builder if GUI compatibility is needed.

## 中文

本仓库包含基于 RTKLIB 2.4.2 p13 的算法主线 C++ 迁移版本。代码结构仍然接近上游 RTKLIB：核心库保持过程式组织方式，但构建系统已经将迁移后的源码按 C++ 处理。

### 核心模块

- `src/rtkcmn.cpp`：时间、坐标、矩阵、卫星系统、路径和 trace 等公共工具。
- `src/pntpos.cpp`：单点定位。
- `src/rtkpos.cpp`：RTK 相对定位。
- `src/ppp.cpp` 和 `src/ppp_ar.cpp`：PPP 与 PPP 模糊度固定。
- `src/lambda.cpp`：整周模糊度搜索和固定。
- `src/postpos.cpp`：`rnx2rtkp` 使用的后处理流程。
- `src/solution.cpp`：解算结果格式化、读取和输出。
- `src/rinex.cpp` 和 `src/convrnx.cpp`：RINEX 读写与转换。
- `src/rtcm*.cpp`：RTCM 解码与编码。
- `src/stream.cpp`、`src/streamsvr.cpp`、`src/rtksvr.cpp`：实时数据流和 RTK server 逻辑。
- `src/rcv`：接收机原始协议解码模块。

### 应用程序

- `app/rnx2rtkp`：命令行后处理。
- `app/rtkrcv`：命令行实时定位。
- `app/convbin`：接收机原始数据转 RINEX。
- `app/str2str`：数据流转发和转换。
- `app/pos2kml`：定位结果转 KML。

### 测试和工具

- `test/utest`：已注册到 CTest 的上游单元测试。
- `test/regression`：已提交的数值回归基线。
- `util`：转换、仿真、电离层、STEC、CRC 和星历相关辅助工具。

### Legacy GUI

原始 Windows VCL 图形界面应用保留在 `legacy_gui_vcl/app` 下。它们不属于默认 CMake 构建；如需 GUI 兼容，需要使用 Embarcadero/Borland C++Builder。
