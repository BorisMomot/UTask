add_executable(domain_tests
        user_test.cc
)

target_link_libraries(domain_tests
        PRIVATE
        domain_model
        gtest_main
        )

# Automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(domain_tests
        PROPERTIES
        LABELS "domain"
        DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
        240
        )