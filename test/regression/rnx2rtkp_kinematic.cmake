# rnx2rtkp relative-kinematic regression test / rnx2rtkp 相对动态定位回归测试

foreach(required_var IN ITEMS RNX2RTKP SOURCE_DIR OUTPUT_DIR BASELINE_FILE)
    if(NOT DEFINED ${required_var})
        message(FATAL_ERROR "missing required variable: ${required_var}")
    endif()
endforeach()

file(MAKE_DIRECTORY "${OUTPUT_DIR}")
set(output_file "${OUTPUT_DIR}/rnx2rtkp_kinematic_07590920_30400920.pos")
file(REMOVE "${output_file}")

execute_process(
    COMMAND "${RNX2RTKP}" -p 2 -o "${output_file}"
            test/data/rinex/07590920.05o
            test/data/rinex/30400920.05o
            test/data/rinex/07590920.05n
    WORKING_DIRECTORY "${SOURCE_DIR}"
    RESULT_VARIABLE result
)

if(NOT result EQUAL 0)
    message(FATAL_ERROR "rnx2rtkp kinematic regression command failed: ${result}")
endif()

file(READ "${BASELINE_FILE}" expected)
file(READ "${output_file}" actual)

string(REPLACE "\r\n" "\n" expected "${expected}")
string(REPLACE "\r\n" "\n" actual "${actual}")
string(REPLACE "\\" "/" expected "${expected}")
string(REPLACE "\\" "/" actual "${actual}")

if(NOT expected STREQUAL actual)
    message(FATAL_ERROR
        "rnx2rtkp relative-kinematic regression output differs from baseline\n"
        "Expected: ${BASELINE_FILE}\n"
        "Actual:   ${output_file}"
    )
endif()
