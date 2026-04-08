# Migration and Development Roadmap

## English

This fork starts from RTKLIB 2.4.2 p13 and tracks the work needed to maintain an
algorithm-focused C++ baseline.

### Completed

- Renamed tracked `.c` source files to `.cpp`.
- Updated build references in makefiles and project files.
- Added CMake presets, VSCode tasks, and Windows/MSVC GitHub Actions.
- Added MSVC Debug/Release coverage for main CLI targets, utility targets, and
  CTest unit tests.
- Added a first `rnx2rtkp` numerical regression baseline using bundled RINEX
  sample data.
- Restored the missing `src/stec.cpp` implementation required by STEC-related
  tests and tools.
- Fixed Windows path expansion for forward-slash paths.
- Added CMake coverage for `geniono`, `rcvdcb`, and the explicit unsupported
  `estiono` command.
- Moved original Windows VCL GUI applications to `legacy_gui_vcl/app` so the
  default tree remains focused on algorithms and command-line tools.

### Next Work

- Expand numerical regression coverage with more RTK, PPP, static, kinematic,
  and multi-constellation datasets.
- Decide whether the public API should continue to preserve C linkage or move
  toward a native C++ API.
- Add modern C++ wrappers only after the compatibility layer is stable.
- Continue bilingual documentation/comment work incrementally, prioritizing
  public APIs, command-line help, configuration files, and algorithm entry
  points.
- Add non-Windows CMake coverage if Linux/macOS support becomes a target.
- Build legacy VCL GUI applications only on machines with Embarcadero
  C++Builder when GUI compatibility is intentionally supported.

### Documentation Policy

- Preserve upstream technical comments and copyright headers for traceability.
- Add Chinese/English explanations to high-value public documentation first.
- Avoid broad machine translation of algorithm comments without review.
- Keep documentation-only changes separate from algorithm behavior changes
  whenever possible.

### Licensing

RTKLIB is distributed under upstream license terms retained in `LICENSE`,
`NOTICE`, and the original `readme.txt`. Downstream redistribution should keep
copyright notices, license terms, and applicable third-party notices.

## 中文

本分支基于 RTKLIB 2.4.2 p13，用于维护一个以算法和命令行为主的 C++ 开发基线。

### 已完成

- 将受 Git 跟踪的 `.c` 源文件重命名为 `.cpp`。
- 更新 makefile 和工程文件中的源码引用。
- 添加 CMake presets、VSCode tasks 和 Windows/MSVC GitHub Actions。
- 为主要 CLI 目标、辅助工具和 CTest 单元测试加入 MSVC Debug/Release 覆盖。
- 使用仓库内置 RINEX 示例数据添加第一组 `rnx2rtkp` 数值回归基线。
- 补回 STEC 相关测试和工具依赖的 `src/stec.cpp`。
- 修复 Windows 下正斜杠路径展开问题。
- 将 `geniono`、`rcvdcb` 和明确“不支持”的 `estiono` 命令纳入 CMake 覆盖。
- 将原始 Windows VCL GUI 应用移到 `legacy_gui_vcl/app`，让默认目录树聚焦算法和命令行工具。

### 后续工作

- 扩展数值回归覆盖，加入更多 RTK、PPP、静态、动态和多星座数据集。
- 决定公共 API 是继续保持 C 链接，还是逐步转向原生 C++ API。
- 在兼容层稳定后再添加现代 C++ 封装。
- 持续推进中英双语文档和注释，优先处理公共 API、命令行帮助、配置文件和算法入口。
- 如果 Linux/macOS 成为支持目标，再补充非 Windows CMake 覆盖。
- 只有在明确需要 GUI 兼容时，才在安装 Embarcadero C++Builder 的机器上构建 legacy VCL GUI 应用。

### 文档策略

- 保留上游技术注释和版权头，便于追踪来源。
- 优先为高价值公开文档补充中英双语说明。
- 避免未经审查的大规模算法注释机器翻译。
- 尽量将纯文档改动与算法行为改动分开提交。

### 许可

RTKLIB 的上游许可条款保留在 `LICENSE`、`NOTICE` 和原始 `readme.txt` 中。再发布时应保留版权声明、许可条款以及适用的第三方声明。
