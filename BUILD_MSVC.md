# MSVC Build Verification / MSVC 编译验证

## English

This workspace was locally verified with Microsoft Visual Studio 2022 Build
Tools:

- `cl.exe`: `C:\Microsoft Visual Studio\2022\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe`
- Environment setup: `C:\Microsoft Visual Studio\2022\VC\Auxiliary\Build\vcvars64.bat`
- CMake used by VS/VSCode: `C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe`
- Language mode: C++17

Verified CMake presets:

- `msvc-debug`
- `msvc-release`

Verified target groups:

- Main command-line applications: `rnx2rtkp`, `convbin`, `pos2kml`,
  `str2str`, `rtkrcv`.
- Auxiliary tools: `rnx2rtcm`, `simobs`, `gencrc`, `genxor`, `genmsk`,
  `geniono`, `genstec`, `gengrid`, `rcvdcb`, `estiono`, `diffeph`,
  `dumpssr`, `convlex`, `dumplex`, `outlexion`, `margelog`.
- Unit tests registered through CTest: `t_matrix`, `t_time`, `t_coord`,
  `t_rinex`, `t_lambda`, `t_atmos`, `t_misc`, `t_preceph`, `t_gloeph`,
  `t_geoid`, `t_ppp`, `t_ionex`, `t_stec`, `t_tle`.
- Numerical regression test registered through CTest:
  `regression_rnx2rtkp_single`.
- Legacy VCL GUI projects are preserved under `legacy_gui_vcl/app` and exposed
  through the optional `rtklib_gui_vcl` target. They require Embarcadero
  C++Builder/BDS and are reported as a clear status target when that toolchain
  is not available.

Regression commands:

```powershell
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe' --preset msvc-debug
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe' --build --preset msvc-debug
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\ctest.exe' --test-dir build\cmake\msvc-debug -C Debug --output-on-failure --interactive-debug-mode 0

& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe' --preset msvc-release
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe' --build --preset msvc-release
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\ctest.exe' --test-dir build\cmake\msvc-release -C Release --output-on-failure --interactive-debug-mode 0
```

Notes:

- `--interactive-debug-mode 0` avoids modal MSVC Debug assertion dialogs during
  automated CTest runs.
- Geoid tests skip external grid-file checks when optional `data/geoiddata`
  files are not present.
- `rnx2rtkp`, `convbin`, `pos2kml`, `geniono`, `rcvdcb`, and `estiono` smoke
  tests intentionally run without input and pass only if the expected error
  path is reached.
- `regression_rnx2rtkp_single` runs `rnx2rtkp -p 0` against
  `test/data/rinex/07590920.05o` and `07590920.05n`, then compares the generated
  `.pos` output with `test/regression/rnx2rtkp_single_07590920.pos`.
- `estiono` is kept as an explicit unsupported historical-draft command because
  the upstream source was incomplete; use `geniono` or `genstec` for maintained
  ionosphere/STEC paths.

## 中文

本工作区已经使用 Microsoft Visual Studio 2022 Build Tools 做过本地验证：

- `cl.exe`：`C:\Microsoft Visual Studio\2022\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe`
- 环境初始化脚本：`C:\Microsoft Visual Studio\2022\VC\Auxiliary\Build\vcvars64.bat`
- VS/VSCode 使用的 CMake：`C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe`
- 语言模式：C++17

已验证的 CMake preset：

- `msvc-debug`
- `msvc-release`

已验证的目标组：

- 主要命令行程序：`rnx2rtkp`、`convbin`、`pos2kml`、`str2str`、`rtkrcv`。
- 辅助工具：`rnx2rtcm`、`simobs`、`gencrc`、`genxor`、`genmsk`、
  `geniono`、`genstec`、`gengrid`、`rcvdcb`、`estiono`、`diffeph`、
  `dumpssr`、`convlex`、`dumplex`、`outlexion`、`margelog`。
- 注册到 CTest 的单元测试：`t_matrix`、`t_time`、`t_coord`、`t_rinex`、
  `t_lambda`、`t_atmos`、`t_misc`、`t_preceph`、`t_gloeph`、`t_geoid`、
  `t_ppp`、`t_ionex`、`t_stec`、`t_tle`。
- 注册到 CTest 的数值回归测试：`regression_rnx2rtkp_single`。
- legacy VCL GUI 工程保留在 `legacy_gui_vcl/app` 下，并通过可选的
  `rtklib_gui_vcl` 目标暴露。它们需要 Embarcadero C++Builder/BDS；当当前环境
  没有该工具链时，构建会给出明确状态提示。

回归命令：

```powershell
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe' --preset msvc-debug
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe' --build --preset msvc-debug
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\ctest.exe' --test-dir build\cmake\msvc-debug -C Debug --output-on-failure --interactive-debug-mode 0

& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe' --preset msvc-release
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe' --build --preset msvc-release
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\ctest.exe' --test-dir build\cmake\msvc-release -C Release --output-on-failure --interactive-debug-mode 0
```

说明：

- `--interactive-debug-mode 0` 可以避免自动化 CTest 中弹出 MSVC Debug 断言对话框。
- 当可选的 `data/geoiddata` 文件不存在时，geoid 测试会跳过外部网格文件检查。
- `rnx2rtkp`、`convbin`、`pos2kml`、`geniono`、`rcvdcb`、`estiono` 的 smoke
  test 会故意在无输入参数下运行；只有进入预期错误路径时才算通过。
- `regression_rnx2rtkp_single` 会用 `test/data/rinex/07590920.05o` 和
  `07590920.05n` 运行 `rnx2rtkp -p 0`，再将生成的 `.pos` 输出与
  `test/regression/rnx2rtkp_single_07590920.pos` 对比。
- `estiono` 保留为明确的“不支持历史草稿”命令，因为上游源码并未完成；当前维护的
  电离层/STEC 路径请使用 `geniono` 或 `genstec`。
