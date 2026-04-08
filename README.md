# RTKLIB C++ Migration / RTKLIB C++ 迁移版

## English

This repository is a downstream workspace derived from RTKLIB 2.4.2 p13. The
current goal is to prepare the codebase for further modification,
optimization, and open source publication in a new GitHub repository.

Current focus:

- Preserve upstream RTKLIB license terms and attribution.
- Keep all migrated C sources as C++ sources.
- Provide a CMake/VSCode workflow for local MSVC builds.
- Cover portable command-line applications, auxiliary tools, and unit tests
  with CTest regression checks.
- Run Windows/MSVC CI through GitHub Actions.
- Add bilingual Chinese/English documentation incrementally.

Important directories:

- `src`: core RTKLIB positioning library.
- `src/rcv`: receiver raw-data decoders.
- `app`: command-line applications kept in the default algorithm-focused tree.
- `legacy_gui_vcl`: original Windows VCL GUI applications moved out of the
  default build path.
- `app/rnx2rtkp`, `app/rtkrcv`, `app/convbin`, `app/str2str`, `app/pos2kml`:
  main command-line applications.
- `test`: unit tests and test data.
- `util`: auxiliary tools.
- `doc`: upstream manual and release notes.
- `data`: sample data.

Licensing:

RTKLIB is distributed under the BSD 2-clause license with additional upstream
clauses described in `LICENSE` and the original `readme.txt`. Downstream
redistribution should retain the original copyright notice, license terms, and
applicable third-party notices. This engineering summary is not legal advice.

Build and regression:

Use the MSVC presets from PowerShell or VSCode:

```powershell
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe' --preset msvc-debug
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe' --build --preset msvc-debug
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\ctest.exe' --test-dir build\cmake\msvc-debug -C Debug --output-on-failure --interactive-debug-mode 0
```

VSCode can run the default build task with `Ctrl+Shift+B`.

GitHub Actions:

The workflow in `.github/workflows/windows-msvc.yml` builds and tests both
`msvc-debug` and `msvc-release`.

VCL GUI applications are preserved under `legacy_gui_vcl/app`. They are not part
of the default algorithm-focused build. If Embarcadero C++Builder/BDS is
installed, they are exposed through the optional `rtklib_gui_vcl` CMake target.

## 中文

本仓库是基于 RTKLIB 2.4.2 p13 派生的下游工作区。当前目标是在该仓库基础上
继续修改和优化，并为后续发布到你自己的 GitHub 开源仓库做准备。

当前重点：

- 保留上游 RTKLIB 的许可证条款和署名信息。
- 将已迁移的 C 源码保持为 C++ 源码。
- 提供可在本机 MSVC 下使用的 CMake/VSCode 构建流程。
- 用 CTest 覆盖可移植的命令行程序、辅助工具和单元测试。
- 通过 GitHub Actions 运行 Windows/MSVC CI。
- 逐步补充中英双语文档。

重要目录：

- `src`：RTKLIB 核心定位库。
- `src/rcv`：接收机原始数据解码模块。
- `app`：默认算法主线中的命令行应用程序。
- `legacy_gui_vcl`：从默认构建路径中移出的原始 Windows VCL GUI 应用。
- `app/rnx2rtkp`、`app/rtkrcv`、`app/convbin`、`app/str2str`、`app/pos2kml`：
  主要命令行程序。
- `test`：单元测试和测试数据。
- `util`：辅助工具。
- `doc`：上游手册和发布说明。
- `data`：示例数据。

许可说明：

RTKLIB 按 BSD 2-clause license 以及上游额外条款发布，具体见 `LICENSE` 和原始
`readme.txt`。下游再发布时应保留原始版权声明、许可证条款以及适用的第三方声明。
本说明是工程层面的总结，不构成法律意见。

构建和回归：

可以在 PowerShell 或 VSCode 中使用 MSVC preset：

```powershell
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe' --preset msvc-debug
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe' --build --preset msvc-debug
& 'C:\Microsoft Visual Studio\2022\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\ctest.exe' --test-dir build\cmake\msvc-debug -C Debug --output-on-failure --interactive-debug-mode 0
```

在 VSCode 中可以按 `Ctrl+Shift+B` 运行默认构建任务。

GitHub Actions：

`.github/workflows/windows-msvc.yml` 工作流会构建并测试 `msvc-debug` 和
`msvc-release`。

VCL GUI 应用保留在 `legacy_gui_vcl/app` 下，不属于默认算法主线构建。如果安装了
Embarcadero C++Builder/BDS，可通过可选的 `rtklib_gui_vcl` CMake 目标调用。
