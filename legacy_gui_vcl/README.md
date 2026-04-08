# Legacy GUI/VCL Components

## English

This directory preserves the original RTKLIB Windows GUI applications and their
shared VCL resources.

They were moved out of the main `app` tree because this fork is focused on
algorithm development, command-line tools, CMake builds, and automated
regression tests.

Contents:

- `app/appcmn`: shared VCL dialogs and GUI helper code.
- `app/icon`: icons and bitmap resources used by GUI programs.
- `app/rtknavi`, `app/rtkpost`, `app/rtkplot`, `app/rtkconv`, `app/strsvr`,
  `app/rtkget`, `app/rtklaunch`, `app/srctblbrows`: original Windows GUI
  applications.
- `app/rtknavi_mkl`, `app/rtkpost_mkl`: historical MKL variants.
- `app/rtklib_winapp.groupproj` and related batch files: original Windows GUI
  project group and helper scripts.

These projects require Embarcadero/Borland C++Builder and VCL. They are not
portable MSVC CMake targets and are not part of the default build. If
C++Builder is installed, CMake can expose the optional `rtklib_gui_vcl` target
with `RTKLIB_ENABLE_VCL_BUILD=ON`.

## 中文

本目录保留原始 RTKLIB Windows GUI 应用及其共享 VCL 资源。

这些内容已从主 `app` 目录中移出，因为本分支聚焦算法开发、命令行工具、CMake 构建和自动化回归测试。

目录内容：

- `app/appcmn`：共享 VCL 对话框和 GUI 辅助代码。
- `app/icon`：GUI 程序使用的图标和位图资源。
- `app/rtknavi`、`app/rtkpost`、`app/rtkplot`、`app/rtkconv`、`app/strsvr`、`app/rtkget`、`app/rtklaunch`、`app/srctblbrows`：原始 Windows GUI 应用。
- `app/rtknavi_mkl`、`app/rtkpost_mkl`：历史 MKL 版本。
- `app/rtklib_winapp.groupproj` 及相关批处理文件：原始 Windows GUI 工程组和辅助脚本。

这些工程依赖 Embarcadero/Borland C++Builder 和 VCL。它们不是可移植的 MSVC CMake 目标，也不属于默认构建。如果安装了 C++Builder，可以通过 `RTKLIB_ENABLE_VCL_BUILD=ON` 使用 CMake 暴露的可选 `rtklib_gui_vcl` 目标。
