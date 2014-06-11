set(SOURCES
    tcp_client
    main_tcp_client
)

add_executable(boost_asio_tcp_client ${SOURCES})
target_link_libraries(boost_asio_tcp_client -lboost_system)
