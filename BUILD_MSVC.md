# MSVC Build and Regression

## English

This document records the supported Windows/MSVC build path for this fork.

### Toolchain

- Compiler: Microsoft Visual Studio 2022 Build Tools / MSVC
- Build system: CMake
- Language mode: C++17
- Test runner: CTest

The provided presets are:

- `msvc-debug`
- `msvc-release`

### Build and Test

Debug:

```powershell
cmake --preset msvc-debug
cmake --build --preset msvc-debug
ctest --test-dir build/cmake/msvc-debug -C Debug --output-on-failure --interactive-debug-mode 0
```

Release:

```powershell
cmake --preset msvc-release
cmake --build --preset msvc-release
ctest --test-dir build/cmake/msvc-release -C Release --output-on-failure --interactive-debug-mode 0
```

`--interactive-debug-mode 0` is used to avoid modal MSVC debug assertion
dialogs during automated test runs.

### Verified Target Groups

- Main command-line applications: `rnx2rtkp`, `convbin`, `pos2kml`,
  `str2str`, `rtkrcv`.
- Auxiliary tools: `rnx2rtcm`, `simobs`, `gencrc`, `genxor`, `genmsk`,
  `geniono`, `genstec`, `gengrid`, `rcvdcb`, `estiono`, `diffeph`,
  `dumpssr`, `convlex`, `dumplex`, `outlexion`, `margelog`.
- Unit tests: `t_matrix`, `t_time`, `t_coord`, `t_rinex`, `t_lambda`,
  `t_atmos`, `t_misc`, `t_preceph`, `t_gloeph`, `t_geoid`, `t_ppp`,
  `t_ionex`, `t_stec`, `t_tle`.
- Numerical regression tests: `regression_rnx2rtkp_single`,
  `regression_rnx2rtkp_kinematic`.

### Notes

- Geoid tests skip external grid-file checks when optional `data/geoiddata`
  files are not present.
- Several smoke tests intentionally run tools without input and pass only when
  the expected error path is reached.
- `regression_rnx2rtkp_single` runs `rnx2rtkp -p 0` against bundled RINEX
  sample data and compares the generated `.pos` output with the committed
  baseline.
- `regression_rnx2rtkp_kinematic` runs `rnx2rtkp -p 2` with bundled rover/base
  RINEX observations to cover the relative positioning and ambiguity-resolution
  path.
- `estiono` is kept as an explicit unsupported historical-draft command because
  the upstream source was incomplete. Maintained ionosphere/STEC paths should
  use `geniono` or `genstec`.
- Legacy VCL GUI projects require Embarcadero/Borland C++Builder and are not
  part of the default MSVC CMake build.

## 中文

本文档记录本分支支持的 Windows/MSVC 构建和回归测试路径。

### 工具链

- 编译器：Microsoft Visual Studio 2022 Build Tools / MSVC
- 构建系统：CMake
- 语言模式：C++17
- 测试运行器：CTest

提供的 preset：

- `msvc-debug`
- `msvc-release`

### 构建和测试

Debug：

```powershell
cmake --preset msvc-debug
cmake --build --preset msvc-debug
ctest --test-dir build/cmake/msvc-debug -C Debug --output-on-failure --interactive-debug-mode 0
```

Release：

```powershell
cmake --preset msvc-release
cmake --build --preset msvc-release
ctest --test-dir build/cmake/msvc-release -C Release --output-on-failure --interactive-debug-mode 0
```

`--interactive-debug-mode 0` 用于避免自动化测试过程中弹出 MSVC Debug 断言对话框。

### 已覆盖目标

- 主要命令行应用：`rnx2rtkp`、`convbin`、`pos2kml`、`str2str`、`rtkrcv`。
- 辅助工具：`rnx2rtcm`、`simobs`、`gencrc`、`genxor`、`genmsk`、`geniono`、`genstec`、`gengrid`、`rcvdcb`、`estiono`、`diffeph`、`dumpssr`、`convlex`、`dumplex`、`outlexion`、`margelog`。
- 单元测试：`t_matrix`、`t_time`、`t_coord`、`t_rinex`、`t_lambda`、`t_atmos`、`t_misc`、`t_preceph`、`t_gloeph`、`t_geoid`、`t_ppp`、`t_ionex`、`t_stec`、`t_tle`。
- 数值回归测试：`regression_rnx2rtkp_single`、`regression_rnx2rtkp_kinematic`。

### 说明

- 当可选的 `data/geoiddata` 网格文件不存在时，geoid 测试会跳过外部网格文件检查。
- 部分 smoke test 会故意在无输入参数下运行工具；只有进入预期错误路径时才算通过。
- `regression_rnx2rtkp_single` 使用仓库内置 RINEX 示例数据运行 `rnx2rtkp -p 0`，并将生成的 `.pos` 输出与已提交基线对比。
- `regression_rnx2rtkp_kinematic` 使用仓库内置流动站/基准站 RINEX 观测数据运行 `rnx2rtkp -p 2`，覆盖相对定位和模糊度固定路径。
- `estiono` 保留为明确“不支持”的历史草稿命令，因为上游源码未完成。当前维护的电离层/STEC 路径应使用 `geniono` 或 `genstec`。
- legacy VCL GUI 工程依赖 Embarcadero/Borland C++Builder，不属于默认 MSVC CMake 构建。
