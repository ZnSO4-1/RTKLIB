# RTKLIB C++ Algorithm Fork

[![Windows MSVC](https://github.com/ZnSO4-1/RTKLIB/actions/workflows/windows-msvc.yml/badge.svg)](https://github.com/ZnSO4-1/RTKLIB/actions/workflows/windows-msvc.yml)

## English

This repository is an algorithm-focused downstream fork of RTKLIB 2.4.2 p13.
It keeps the upstream GNSS positioning algorithms as the foundation while
modernizing the source layout and build workflow for further C++ development.

The default tree focuses on:

- RTKLIB core positioning algorithms in `src`;
- command-line applications in `app`;
- auxiliary tools in `util`;
- unit and numerical regression tests in `test`;
- CMake, VSCode, and Windows/MSVC GitHub Actions coverage.

The original Windows VCL GUI applications are preserved under
`legacy_gui_vcl/app`. They are not part of the default build because this fork
is intended primarily for algorithm development and command-line workflows.

### Current Status

- Tracked C source files have been migrated from `.c` to `.cpp`.
- The default CMake build uses C++17.
- Main command-line programs are covered: `rnx2rtkp`, `rtkrcv`, `convbin`,
  `str2str`, and `pos2kml`.
- Major utility targets and upstream unit tests are registered with CTest.
- Numerical regression baselines are included for `rnx2rtkp` single-point,
  relative-kinematic, PPP-static, and PPP-kinematic runs using bundled sample
  data.
- Windows/MSVC Debug and Release builds are checked by GitHub Actions.

### Build

On Windows with Visual Studio 2022 Build Tools:

```powershell
cmake --preset msvc-debug
cmake --build --preset msvc-debug
ctest --test-dir build/cmake/msvc-debug -C Debug --output-on-failure --interactive-debug-mode 0
```

Release build:

```powershell
cmake --preset msvc-release
cmake --build --preset msvc-release
ctest --test-dir build/cmake/msvc-release -C Release --output-on-failure --interactive-debug-mode 0
```

VSCode users can run the default build task with `Ctrl+Shift+B`.

### Repository Layout

- `src`: core RTKLIB library and positioning algorithms.
- `src/rcv`: receiver raw-data decoders.
- `app`: command-line applications.
- `util`: auxiliary conversion, simulation, ionosphere, and test tools.
- `test`: unit tests, sample test data, and regression baselines.
- `data`: receiver command examples and sample data.
- `doc`: upstream manual and release notes.
- `legacy_gui_vcl`: preserved Windows VCL GUI applications.

### Licensing

This fork is derived from RTKLIB by T. Takasu and contributors. The upstream
license terms are retained in `LICENSE`, `NOTICE`, and the original
`readme.txt`. Redistribution should preserve upstream copyright notices,
license terms, and applicable third-party notices.

## 中文

本仓库是基于 RTKLIB 2.4.2 p13 的算法主线分支。它以 RTKLIB 上游 GNSS 定位算法为基础，同时整理源码结构和构建流程，为后续 C++ 化开发、算法优化和自动化回归测试提供更稳定的基线。

默认主线聚焦于：

- `src` 中的 RTKLIB 核心定位算法；
- `app` 中的命令行程序；
- `util` 中的辅助工具；
- `test` 中的单元测试和数值回归测试；
- CMake、VSCode 和 Windows/MSVC GitHub Actions 构建验证。

原始 Windows VCL 图形界面应用已保留在 `legacy_gui_vcl/app` 下。它们不属于默认构建目标，因为本分支主要面向算法开发和命令行工作流。

### 当前状态

- 已将受 Git 跟踪的 C 源文件从 `.c` 迁移为 `.cpp`。
- 默认 CMake 构建使用 C++17。
- 已覆盖主要命令行程序：`rnx2rtkp`、`rtkrcv`、`convbin`、`str2str`、`pos2kml`。
- 已将主要辅助工具和上游单元测试注册到 CTest。
- 已加入 `rnx2rtkp` 单点定位和相对动态定位数值回归基线，使用仓库内置 RINEX 示例数据。
- GitHub Actions 会在 Windows/MSVC 下验证 Debug 和 Release 构建。

### 构建

在安装 Visual Studio 2022 Build Tools 的 Windows 环境中：

```powershell
cmake --preset msvc-debug
cmake --build --preset msvc-debug
ctest --test-dir build/cmake/msvc-debug -C Debug --output-on-failure --interactive-debug-mode 0
```

Release 构建：

```powershell
cmake --preset msvc-release
cmake --build --preset msvc-release
ctest --test-dir build/cmake/msvc-release -C Release --output-on-failure --interactive-debug-mode 0
```

VSCode 用户可以通过 `Ctrl+Shift+B` 运行默认构建任务。

### 仓库结构

- `src`：RTKLIB 核心库和定位算法。
- `src/rcv`：接收机原始数据解码模块。
- `app`：命令行应用程序。
- `util`：转换、仿真、电离层和测试等辅助工具。
- `test`：单元测试、测试数据和回归基线。
- `data`：接收机命令示例和示例数据。
- `doc`：上游手册和发布说明。
- `legacy_gui_vcl`：保留的 Windows VCL 图形界面应用。

### 许可

本分支派生自 T. Takasu 及贡献者维护的 RTKLIB。上游许可条款保留在 `LICENSE`、`NOTICE` 和原始 `readme.txt` 中。再发布时应保留上游版权声明、许可条款以及适用的第三方声明。
