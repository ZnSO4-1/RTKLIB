cmake_minimum_required(VERSION 3.20)

project(RTKLIBCppMigration
    VERSION 2.4.2
    DESCRIPTION "Downstream C++ migration workspace derived from RTKLIB"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
find_package(Threads)

set(RTKLIB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(RTKLIB_RCV_DIR "${RTKLIB_SRC_DIR}/rcv")

set(RTKLIB_COMMON
    src/rtkcmn.cpp
    src/preceph.cpp
)

set(RTKLIB_RINEX
    src/rinex.cpp
)

set(RTKLIB_RTCM
    src/rtcm.cpp
    src/rtcm2.cpp
    src/rtcm3.cpp
    src/rtcm3e.cpp
)

set(RTKLIB_RCV_SOURCES
    "${RTKLIB_RCV_DIR}/novatel.cpp"
    "${RTKLIB_RCV_DIR}/ublox.cpp"
    "${RTKLIB_RCV_DIR}/ss2.cpp"
    "${RTKLIB_RCV_DIR}/crescent.cpp"
    "${RTKLIB_RCV_DIR}/skytraq.cpp"
    "${RTKLIB_RCV_DIR}/gw10.cpp"
    "${RTKLIB_RCV_DIR}/javad.cpp"
    "${RTKLIB_RCV_DIR}/nvs.cpp"
    "${RTKLIB_RCV_DIR}/binex.cpp"
    "${RTKLIB_RCV_DIR}/rt17.cpp"
)

set(RTKLIB_POSITIONING
    src/rtkpos.cpp
    src/pntpos.cpp
    src/ppp.cpp
    src/ppp_ar.cpp
    src/lambda.cpp
)

set(RTKLIB_NAV
    src/ephemeris.cpp
    src/sbas.cpp
    src/ionex.cpp
    src/qzslex.cpp
    src/tle.cpp
    src/stec.cpp
)

function(rtklib_configure_target target)
    target_include_directories("${target}" PRIVATE "${RTKLIB_SRC_DIR}")

    if(MSVC)
        target_compile_options("${target}" PRIVATE /W3 /utf-8)
        target_compile_definitions("${target}" PRIVATE
            WIN32
            _CRT_SECURE_NO_WARNINGS
            _WINSOCK_DEPRECATED_NO_WARNINGS
        )
    else()
        target_compile_options("${target}" PRIVATE
            -Wall
            -Wno-unused-but-set-variable
        )
    endif()

    if(WIN32)
        target_link_libraries("${target}" PRIVATE ws2_32 winmm)
    elseif(Threads_FOUND)
        target_link_libraries("${target}" PRIVATE Threads::Threads m)
    else()
        target_link_libraries("${target}" PRIVATE m)
    endif()
endfunction()

function(rtklib_add_executable target)
    add_executable("${target}" ${ARGN})
    rtklib_configure_target("${target}")
endfunction()

function(rtklib_add_cli_smoke_test target)
    if(BUILD_TESTING)
        add_test(NAME "smoke_${target}" COMMAND "${target}" ${ARGN})
        set_tests_properties("smoke_${target}" PROPERTIES WILL_FAIL TRUE)
    endif()
endfunction()

function(rtklib_add_unit_test target)
    rtklib_add_executable("${target}" ${ARGN})
    target_compile_definitions("${target}" PRIVATE TRACE ENAGLO ENAQZS ENAGAL NFREQ=3)
    if(BUILD_TESTING)
        add_test(NAME "${target}" COMMAND "${target}")
        set_tests_properties("${target}" PROPERTIES
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/test/utest"
        )
    endif()
endfunction()

add_custom_target(rtklib_cli)
add_custom_target(rtklib_utils)
add_custom_target(rtklib_unit_tests)
add_custom_target(rtklib_gui_vcl)

option(RTKLIB_ENABLE_VCL_BUILD "Try to build legacy Embarcadero C++Builder VCL GUI projects / 尝试构建 legacy Embarcadero C++Builder VCL 图形界面工程" OFF)

set(RTKLIB_VCL_PROJECTS
    legacy_gui_vcl/app/rtkconv/rtkconv.cbproj
    legacy_gui_vcl/app/rtkget/rtkget.cbproj
    legacy_gui_vcl/app/rtklaunch/rtklaunch.cbproj
    legacy_gui_vcl/app/rtknavi/rtknavi.cbproj
    legacy_gui_vcl/app/rtknavi_mkl/rtknavi_mkl.cbproj
    legacy_gui_vcl/app/rtkplot/rtkplot.cbproj
    legacy_gui_vcl/app/rtkpost/rtkpost.cbproj
    legacy_gui_vcl/app/rtkpost_mkl/rtkpost_mkl.cbproj
    legacy_gui_vcl/app/srctblbrows/srctblbrows.cbproj
    legacy_gui_vcl/app/strsvr/strsvr.cbproj
)

find_program(RTKLIB_BDS_MSBUILD
    NAMES MSBuild.exe msbuild.exe
    HINTS "$ENV{BDS}/bin" "$ENV{BDS}\\bin"
)

if(RTKLIB_ENABLE_VCL_BUILD AND RTKLIB_BDS_MSBUILD)
    foreach(vcl_project IN LISTS RTKLIB_VCL_PROJECTS)
        get_filename_component(vcl_name "${vcl_project}" NAME_WE)
        add_custom_target("vcl_${vcl_name}"
            COMMAND "${RTKLIB_BDS_MSBUILD}" "${CMAKE_CURRENT_SOURCE_DIR}/${vcl_project}" /p:Config=Release /p:Platform=Win32
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            COMMENT "Building VCL project ${vcl_project} / 构建 VCL 工程 ${vcl_project}"
            VERBATIM
        )
        add_dependencies(rtklib_gui_vcl "vcl_${vcl_name}")
    endforeach()
else()
    add_custom_target(rtklib_gui_vcl_status
        COMMAND ${CMAKE_COMMAND} -E echo "Legacy VCL GUI projects have been moved to legacy_gui_vcl/app and are not default algorithm targets."
        COMMAND ${CMAKE_COMMAND} -E echo "They require Embarcadero C++Builder and are not portable MSVC CMake targets."
        COMMAND ${CMAKE_COMMAND} -E echo "Set RTKLIB_ENABLE_VCL_BUILD=ON with BDS/MSBuild available to build them."
        COMMAND ${CMAKE_COMMAND} -E echo "legacy VCL 图形界面工程已移动到 legacy_gui_vcl/app，不属于默认算法目标。"
        COMMAND ${CMAKE_COMMAND} -E echo "它们依赖 Embarcadero C++Builder；普通 MSVC CMake 环境无法直接构建。"
        COMMAND ${CMAKE_COMMAND} -E echo "如需构建，请安装 C++Builder，设置 BDS/MSBuild，并启用 RTKLIB_ENABLE_VCL_BUILD=ON。"
        VERBATIM
    )
    add_dependencies(rtklib_gui_vcl rtklib_gui_vcl_status)
endif()

# Main command-line applications / 主命令行程序
rtklib_add_executable(rnx2rtkp
    app/rnx2rtkp/rnx2rtkp.cpp
    ${RTKLIB_COMMON}
    ${RTKLIB_RINEX}
    ${RTKLIB_RTCM}
    ${RTKLIB_POSITIONING}
    src/postpos.cpp
    src/solution.cpp
    src/geoid.cpp
    src/options.cpp
    src/ephemeris.cpp
    src/sbas.cpp
    src/ionex.cpp
    src/qzslex.cpp
    src/stec.cpp
)
target_compile_definitions(rnx2rtkp PRIVATE TRACE ENAGLO ENAQZS ENAGAL NFREQ=3)
add_dependencies(rtklib_cli rnx2rtkp)

rtklib_add_executable(convbin
    app/convbin/convbin.cpp
    src/rtkcmn.cpp
    ${RTKLIB_RINEX}
    ${RTKLIB_RTCM}
    src/sbas.cpp
    src/preceph.cpp
    src/rcvraw.cpp
    src/convrnx.cpp
    src/pntpos.cpp
    src/ephemeris.cpp
    src/ionex.cpp
    src/qzslex.cpp
    ${RTKLIB_RCV_SOURCES}
)
target_compile_definitions(convbin PRIVATE TRACE ENAGLO ENAQZS ENAGAL ENACMP NFREQ=6 NEXOBS=3)
add_dependencies(rtklib_cli convbin)

rtklib_add_executable(pos2kml
    app/pos2kml/pos2kml.cpp
    src/convkml.cpp
    src/solution.cpp
    src/geoid.cpp
    src/rtkcmn.cpp
    src/preceph.cpp
)
target_compile_definitions(pos2kml PRIVATE TRACE)
add_dependencies(rtklib_cli pos2kml)

rtklib_add_executable(str2str
    app/str2str/str2str.cpp
    src/stream.cpp
    src/streamsvr.cpp
    src/rtkcmn.cpp
    src/solution.cpp
    src/sbas.cpp
    src/geoid.cpp
    src/rcvraw.cpp
    ${RTKLIB_RTCM}
    src/preceph.cpp
    ${RTKLIB_RCV_SOURCES}
)
target_compile_definitions(str2str PRIVATE TRACE ENAGLO ENAQZS ENAGAL ENACMP NFREQ=3 NEXOBS=3)
add_dependencies(rtklib_cli str2str)

rtklib_add_executable(rtkrcv
    app/rtkrcv/rtkrcv.cpp
    app/rtkrcv/vt.cpp
    src/rtkcmn.cpp
    src/rtksvr.cpp
    src/rtkpos.cpp
    src/geoid.cpp
    src/solution.cpp
    src/lambda.cpp
    src/sbas.cpp
    src/stream.cpp
    src/rcvraw.cpp
    ${RTKLIB_RTCM}
    src/preceph.cpp
    src/options.cpp
    src/pntpos.cpp
    src/ppp.cpp
    src/ppp_ar.cpp
    src/ephemeris.cpp
    src/rinex.cpp
    src/ionex.cpp
    src/qzslex.cpp
    src/stec.cpp
    ${RTKLIB_RCV_SOURCES}
)
target_include_directories(rtkrcv PRIVATE app/rtkrcv)
target_compile_definitions(rtkrcv PRIVATE TRACE ENAGLO ENAQZS ENACMP NFREQ=3)
add_dependencies(rtklib_cli rtkrcv)

# Utility programs / 辅助工具
rtklib_add_executable(rnx2rtcm
    util/rnx2rtcm/rnx2rtcm.cpp
    src/rtkcmn.cpp
    src/rinex.cpp
    ${RTKLIB_RTCM}
)
target_compile_definitions(rnx2rtcm PRIVATE TRACE ENAGLO ENAGAL ENAQZS NFREQ=3 NEXOBS=3)
add_dependencies(rtklib_utils rnx2rtcm)

rtklib_add_executable(simobs
    util/simobs/simobs.cpp
    src/rinex.cpp
    src/rtkcmn.cpp
    src/ephemeris.cpp
    src/preceph.cpp
    src/sbas.cpp
    src/ionex.cpp
    src/qzslex.cpp
    ${RTKLIB_RTCM}
)
target_compile_definitions(simobs PRIVATE TRACE ENAGLO ENAGAL ENAQZS NFREQ=4 MAXOBS=128)
add_dependencies(rtklib_utils simobs)

rtklib_add_executable(gencrc util/gencrc/gencrc.cpp)
rtklib_add_executable(genxor util/gencrc/genxor.cpp)
rtklib_add_executable(genmsk util/gencrc/genmsk.cpp)
add_dependencies(rtklib_utils gencrc genxor genmsk)

rtklib_add_executable(genstec
    util/geniono/genstec.cpp
    ${RTKLIB_COMMON}
    ${RTKLIB_RINEX}
    src/ephemeris.cpp
    src/sbas.cpp
    src/pntpos.cpp
    src/ionex.cpp
    src/qzslex.cpp
    ${RTKLIB_RTCM}
)
target_compile_definitions(genstec PRIVATE TRACE ENAGLO ENAQZS NFREQ=3)
add_dependencies(rtklib_utils genstec)

rtklib_add_executable(geniono
    util/geniono/geniono.cpp
    ${RTKLIB_COMMON}
    ${RTKLIB_RINEX}
    src/ephemeris.cpp
    src/sbas.cpp
    src/pntpos.cpp
    src/ionex.cpp
    src/qzslex.cpp
    ${RTKLIB_RTCM}
)
target_compile_definitions(geniono PRIVATE TRACE ENAGLO ENAQZS NFREQ=3)
add_dependencies(rtklib_utils geniono)

rtklib_add_executable(rcvdcb
    util/geniono/rcvdcb.cpp
    ${RTKLIB_COMMON}
    ${RTKLIB_RINEX}
    src/ephemeris.cpp
    src/sbas.cpp
    src/pntpos.cpp
    src/ionex.cpp
    src/qzslex.cpp
    ${RTKLIB_RTCM}
)
target_compile_definitions(rcvdcb PRIVATE TRACE ENAGLO ENAQZS NFREQ=3)
add_dependencies(rtklib_utils rcvdcb)

rtklib_add_executable(estiono
    util/geniono/estiono.cpp
    src/rtkcmn.cpp
    src/preceph.cpp
)
target_compile_definitions(estiono PRIVATE TRACE ENAGLO ENAQZS NFREQ=3)
add_dependencies(rtklib_utils estiono)

rtklib_add_executable(gengrid
    util/geniono/gengrid.cpp
    ${RTKLIB_COMMON}
    src/stec.cpp
)
target_compile_definitions(gengrid PRIVATE TRACE ENAGLO ENAQZS NFREQ=3)
add_dependencies(rtklib_utils gengrid)

rtklib_add_executable(diffeph
    util/testeph/diffeph.cpp
    ${RTKLIB_COMMON}
    ${RTKLIB_RINEX}
    src/ephemeris.cpp
    src/sbas.cpp
    src/ionex.cpp
    src/pntpos.cpp
    src/ppp.cpp
    src/ppp_ar.cpp
    src/lambda.cpp
    src/qzslex.cpp
    src/stec.cpp
    ${RTKLIB_RTCM}
)
target_compile_definitions(diffeph PRIVATE TRACE ENAQZS ENAGLO EXTLEX NFREQ=3)
add_dependencies(rtklib_utils diffeph)

rtklib_add_executable(testeph_dumpssr
    util/testeph/dumpssr.cpp
    ${RTKLIB_COMMON}
    src/rtcm.cpp
    src/rtcm2.cpp
    src/rtcm3.cpp
    src/rtcm3e.cpp
)
target_compile_definitions(testeph_dumpssr PRIVATE TRACE ENAQZS ENAGLO EXTLEX NFREQ=3)
set_target_properties(testeph_dumpssr PROPERTIES OUTPUT_NAME dumpssr)
add_dependencies(rtklib_utils testeph_dumpssr)

rtklib_add_executable(convlex
    util/testlex/convlex.cpp
    ${RTKLIB_COMMON}
    src/qzslex.cpp
    ${RTKLIB_RTCM}
)
target_compile_definitions(convlex PRIVATE TRACE ENAQZS ENAGLO NFREQ=3)
add_dependencies(rtklib_utils convlex)

rtklib_add_executable(dumplex
    util/testlex/dumplex.cpp
    ${RTKLIB_COMMON}
    src/qzslex.cpp
    ${RTKLIB_RTCM}
)
target_compile_definitions(dumplex PRIVATE TRACE ENAQZS ENAGLO NFREQ=3)
add_dependencies(rtklib_utils dumplex)

rtklib_add_executable(testlex_dumpssr
    util/testlex/dumpssr.cpp
    ${RTKLIB_COMMON}
    src/rtcm.cpp
    src/rtcm2.cpp
    src/rtcm3.cpp
    src/rtcm3e.cpp
)
target_compile_definitions(testlex_dumpssr PRIVATE TRACE ENAQZS ENAGLO NFREQ=3)
set_target_properties(testlex_dumpssr PROPERTIES OUTPUT_NAME testlex_dumpssr)
add_dependencies(rtklib_utils testlex_dumpssr)

rtklib_add_executable(outlexion
    util/testlex/outlexion.cpp
    ${RTKLIB_COMMON}
    src/qzslex.cpp
    ${RTKLIB_RTCM}
)
target_compile_definitions(outlexion PRIVATE TRACE ENAQZS ENAGLO NFREQ=3)
add_dependencies(rtklib_utils outlexion)

rtklib_add_executable(margelog
    util/logfile/margelog.cpp
    src/rtkcmn.cpp
)
target_compile_definitions(margelog PRIVATE TRACE NFREQ=3)
add_dependencies(rtklib_utils margelog)

# Unit tests from test/utest/makefile / 来自 test/utest/makefile 的单元测试
rtklib_add_unit_test(t_matrix
    test/utest/t_matrix.cpp
    src/rtkcmn.cpp
    src/preceph.cpp
)
rtklib_add_unit_test(t_time
    test/utest/t_time.cpp
    src/rtkcmn.cpp
    src/preceph.cpp
)
rtklib_add_unit_test(t_coord
    test/utest/t_coord.cpp
    src/rtkcmn.cpp
    src/geoid.cpp
    src/preceph.cpp
)
rtklib_add_unit_test(t_rinex
    test/utest/t_rinex.cpp
    src/rtkcmn.cpp
    src/rinex.cpp
    src/preceph.cpp
)
rtklib_add_unit_test(t_lambda
    test/utest/t_lambda.cpp
    src/rtkcmn.cpp
    src/lambda.cpp
    src/preceph.cpp
)
rtklib_add_unit_test(t_atmos
    test/utest/t_atmos.cpp
    src/rtkcmn.cpp
    src/preceph.cpp
)
rtklib_add_unit_test(t_misc
    test/utest/t_misc.cpp
    src/rtkcmn.cpp
    src/preceph.cpp
)
rtklib_add_unit_test(t_preceph
    test/utest/t_preceph.cpp
    src/rtkcmn.cpp
    src/preceph.cpp
    src/rinex.cpp
    src/ephemeris.cpp
    src/sbas.cpp
    src/qzslex.cpp
    ${RTKLIB_RTCM}
)
rtklib_add_unit_test(t_gloeph
    test/utest/t_gloeph.cpp
    src/rtkcmn.cpp
    src/rinex.cpp
    src/ephemeris.cpp
    src/sbas.cpp
    src/preceph.cpp
    src/qzslex.cpp
    ${RTKLIB_RTCM}
)
rtklib_add_unit_test(t_geoid
    test/utest/t_geoid.cpp
    src/rtkcmn.cpp
    src/preceph.cpp
    src/geoid.cpp
)
rtklib_add_unit_test(t_ppp
    test/utest/t_ppp.cpp
    src/rtkcmn.cpp
    src/ephemeris.cpp
    src/preceph.cpp
    src/sbas.cpp
    src/ionex.cpp
    src/pntpos.cpp
    src/ppp.cpp
    src/ppp_ar.cpp
    src/stec.cpp
    src/lambda.cpp
    src/qzslex.cpp
    ${RTKLIB_RTCM}
)
rtklib_add_unit_test(t_ionex
    test/utest/t_ionex.cpp
    src/rtkcmn.cpp
    src/preceph.cpp
    src/ionex.cpp
)
rtklib_add_unit_test(t_stec
    test/utest/t_stec.cpp
    src/rtkcmn.cpp
    src/preceph.cpp
    src/stec.cpp
)
rtklib_add_unit_test(t_tle
    test/utest/t_tle.cpp
    src/rtkcmn.cpp
    src/rinex.cpp
    src/ephemeris.cpp
    src/sbas.cpp
    src/preceph.cpp
    src/tle.cpp
    src/qzslex.cpp
    ${RTKLIB_RTCM}
)
add_dependencies(rtklib_unit_tests
    t_matrix t_time t_coord t_rinex t_lambda t_atmos t_misc t_preceph
    t_gloeph t_geoid t_ppp t_ionex t_stec t_tle
)

rtklib_add_cli_smoke_test(rnx2rtkp)
rtklib_add_cli_smoke_test(convbin)
rtklib_add_cli_smoke_test(pos2kml)
rtklib_add_cli_smoke_test(str2str -h)
rtklib_add_cli_smoke_test(geniono)
rtklib_add_cli_smoke_test(rcvdcb)
rtklib_add_cli_smoke_test(estiono)
set_tests_properties(smoke_str2str PROPERTIES WILL_FAIL FALSE)

if(BUILD_TESTING)
    add_test(NAME regression_rnx2rtkp_single
        COMMAND "${CMAKE_COMMAND}"
            -D "RNX2RTKP=$<TARGET_FILE:rnx2rtkp>"
            -D "SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
            -D "OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/regression"
            -D "BASELINE_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test/regression/rnx2rtkp_single_07590920.pos"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/test/regression/rnx2rtkp_single.cmake"
    )
    add_test(NAME regression_rnx2rtkp_kinematic
        COMMAND "${CMAKE_COMMAND}"
            -D "RNX2RTKP=$<TARGET_FILE:rnx2rtkp>"
            -D "SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
            -D "OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/regression"
            -D "BASELINE_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test/regression/rnx2rtkp_kinematic_07590920_30400920.pos"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/test/regression/rnx2rtkp_kinematic.cmake"
    )
    add_test(NAME regression_rnx2rtkp_ppp_static
        COMMAND "${CMAKE_COMMAND}"
            -D "RNX2RTKP=$<TARGET_FILE:rnx2rtkp>"
            -D "SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
            -D "OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/regression"
            -D "BASELINE_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test/regression/rnx2rtkp_ppp_static_07590920.pos"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/test/regression/rnx2rtkp_ppp_static.cmake"
    )
    add_test(NAME regression_rnx2rtkp_ppp_kinematic
        COMMAND "${CMAKE_COMMAND}"
            -D "RNX2RTKP=$<TARGET_FILE:rnx2rtkp>"
            -D "SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
            -D "OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/regression"
            -D "BASELINE_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test/regression/rnx2rtkp_ppp_kinematic_07590920.pos"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/test/regression/rnx2rtkp_ppp_kinematic.cmake"
    )
endif()
