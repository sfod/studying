set(SOURCES
    tree
)

add_executable(boost_coroutine_tree ${SOURCES})
target_link_libraries(boost_coroutine_tree -lboost_context -lboost_coroutine)
