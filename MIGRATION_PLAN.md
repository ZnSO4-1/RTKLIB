# RTKLIB C++ Migration Plan / RTKLIB C++ 迁移计划

## English

This repository is derived from RTKLIB 2.4.2 p13. The migration has renamed
tracked C source files to C++ source files, updated build references, and added
CMake regression coverage for the portable command-line path.

### Licensing and publication

The upstream README states that RTKLIB is distributed under the BSD 2-clause
license with additional upstream clauses. Redistribution and modification are
allowed as long as the license terms, copyright notices, and applicable
third-party notices are retained.

Before publishing a downstream GitHub repository:

- Keep `LICENSE`, `NOTICE`, and the original `readme.txt`.
- Keep original copyright headers in source files.
- Document downstream changes in this file or in a changelog.
- Review third-party binary or library files before distributing binaries.

This note is an engineering summary, not legal advice.

### C++ migration status

Completed:

- Renamed tracked `.c` source files to `.cpp`.
- Updated GCC makefiles and project files to reference `.cpp` sources.
- Added CMake presets and VSCode tasks.
- Added MSVC Debug/Release builds for main CLI targets, utility targets, and
  CTest unit tests.
- Added a first `rnx2rtkp` numerical regression baseline for single-point
  positioning with bundled RINEX sample data.
- Added a Windows/MSVC GitHub Actions workflow for Debug and Release builds.
- Restored the missing `src/stec.cpp` implementation used by STEC-related tests
  and tools.
- Fixed Windows `expath()` handling for forward-slash paths.
- Added a minimal STEC sample file for regression coverage.
- Added CMake build coverage for `geniono`, `rcvdcb`, and an explicit
  unsupported `estiono` placeholder so the historical draft no longer breaks
  default utility builds.
- Moved the original Windows VCL GUI applications to `legacy_gui_vcl/app` so
  the default tree stays focused on algorithm and command-line development.
- Added a `rtklib_gui_vcl` CMake target that can call Embarcadero
  C++Builder/BDS MSBuild when available, and otherwise emits a clear status
  message instead of failing inside the MSVC build.

Still required:

- Decide whether the public API should keep C linkage or move to native C++
  linkage.
- Add modern C++ wrappers only after the compatibility build is stable.
- Continue bilingual documentation/comment work incrementally.
- Expand algorithm regression with more representative GNSS datasets; the first
  baseline currently covers one `rnx2rtkp` single-point case.
- Build the legacy VCL GUI applications on a machine that has Embarcadero
  C++Builder installed only if GUI compatibility becomes a release goal.

### Bilingual documentation/comment policy

The safest approach is incremental:

- Keep original upstream technical comments intact for traceability.
- Add Chinese translations next to high-value comments, public APIs,
  command-line help, configuration files, and user documentation first.
- Avoid mass machine-translation of algorithm comments without review.
- Treat bilingual changes as documentation changes and review them separately
  from algorithm changes.

## 中文

本仓库派生自 RTKLIB 2.4.2 p13。当前迁移已经将已跟踪的 C 源文件重命名为
C++ 源文件，更新了构建引用，并为可移植的命令行路径补充了 CMake 回归覆盖。

### 许可与发布

上游 README 写明 RTKLIB 按 BSD 2-clause license 以及上游额外条款发布。只要
保留许可证条款、版权声明以及适用的第三方声明，就允许再发布和修改。

发布到你自己的 GitHub 仓库前：

- 保留 `LICENSE`、`NOTICE` 和原始 `readme.txt`。
- 保留源文件中的原始版权头。
- 在本文档或变更日志中记录下游修改。
- 如果发布二进制文件，先核查相关第三方二进制或库文件的许可。

本说明是工程层面的总结，不构成法律意见。

### C++ 迁移状态

已完成：

- 将已跟踪的 `.c` 源文件重命名为 `.cpp`。
- 更新 GCC makefile 和工程文件，使其引用 `.cpp` 源文件。
- 添加 CMake presets 和 VSCode tasks。
- 为主要 CLI 目标、辅助工具和 CTest 单元测试添加 MSVC Debug/Release 构建。
- 添加第一组 `rnx2rtkp` 单点定位数值回归基线，使用仓库内置 RINEX 样例数据。
- 添加 Windows/MSVC GitHub Actions 工作流，覆盖 Debug 和 Release 构建。
- 补回 STEC 相关测试和工具依赖的缺失实现 `src/stec.cpp`。
- 修复 Windows 下 `expath()` 对正斜杠路径的处理。
- 添加最小 STEC 样例文件，用于回归测试。
- 将 `geniono`、`rcvdcb` 纳入 CMake 构建，并把上游未完成的历史草稿
  `estiono` 明确改为“不支持”占位命令，避免它继续破坏默认工具构建。
- 将原始 Windows VCL GUI 应用移动到 `legacy_gui_vcl/app`，让默认目录树聚焦
  算法和命令行开发。
- 添加 `rtklib_gui_vcl` CMake 目标：如果存在 Embarcadero C++Builder/BDS
  MSBuild，则可尝试调用 VCL 工程；如果当前机器没有该工具链，则输出明确状态
  提示，而不是在 MSVC 构建里隐式失败。

仍需继续：

- 决定公共 API 是继续保留 C 链接，还是迁移到原生 C++ 链接。
- 等兼容构建稳定后，再添加现代 C++ 封装。
- 继续按模块推进中英双语文档和注释。
- 继续扩展算法回归数据集；当前第一组基线覆盖一个 `rnx2rtkp` 单点定位案例。
- 只有当 GUI 兼容性成为发布目标时，才需要在安装了 Embarcadero C++Builder 的
  机器上构建 legacy VCL GUI 应用并记录该工具链相关的验证结果。

### 中英双语文档/注释策略

最稳妥的方式是分阶段推进：

- 保留上游原始技术注释，方便追踪历史来源。
- 优先为高价值注释、公共 API、命令行帮助、配置文件和用户文档补充中文翻译。
- 不对算法注释做未经审核的大规模机器翻译。
- 将双语化变更作为文档变更单独审查，不和算法行为修改混在一起。
